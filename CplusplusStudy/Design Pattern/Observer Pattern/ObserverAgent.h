#pragma once

#include <map>
#include <string>
#include <memory>
#include <functional>

class ObserverBase;

template<typename... ParamType>
using ObserverEventCallBack = void(*)(std::shared_ptr<ObserverBase> pObserver, ParamType... params);

template<typename ObserverType>
using ObserverAddCallBack = void(*)(ObserverType* pObserver);

template<typename ObserverType>
using ObserverRemoveCallBack = void(*)(ObserverType* pObserver);


using ObserverFuncPtr = void*;
using ObserverPtr = void*;

// 옵저버의 등록 및 해제를 한다.
class ObserverEventRegisterBase
{
public:
	ObserverEventRegisterBase() {}
	virtual ~ObserverEventRegisterBase() {}
};

template<typename T>
class ObserverEventRegister : public ObserverEventRegisterBase
{
private:
	T* m_pObserver;
	ObserverAddCallBack<T> m_pAddCallBack;
	ObserverRemoveCallBack<T> m_pRemoveCallBack;

public:
	ObserverEventRegister(T* pObserver, ObserverAddCallBack<T> pAddCallBack, ObserverRemoveCallBack<T> pRemoveCallBack) :
		m_pObserver(pObserver),
		m_pAddCallBack(pAddCallBack),
		m_pRemoveCallBack(pRemoveCallBack)
	{
		m_pAddCallBack(m_pObserver);
	}

	~ObserverEventRegister()
	{
		m_pRemoveCallBack(m_pObserver);
	}
};

// 옵저버를 관리
class ObserverBase
{
public:
	virtual ~ObserverBase() {}

public:
	bool IsA(ObserverBase* pObserver)
	{
		if (pObserver == nullptr)
			return false;

		if (GetTypeHash() == pObserver->GetTypeHash())
			return true;

		return false;
	}

	virtual std::size_t GetTypeHash() = 0;
};

template<typename T>
class Observer : public ObserverBase
{
private:
	T* m_pObserver;

public:
	Observer(T* pObserver):
		m_pObserver(pObserver)
	{}

	T* GetObserver()
	{
		return m_pObserver;
	}

	virtual std::size_t GetTypeHash()
	{
		static std::size_t hashValue = std::hash<Observer<T>*>{}(GetStaticClass());
		return hashValue;
	}

	static Observer<T>* GetStaticClass()
	{
		static Observer<T> instance(nullptr);
		return &instance;
	}
};

// 옵저버의 이벤트를 관리
class ObserverEventPack
{
private:
	std::map<ObserverFuncPtr, std::map<ObserverPtr, std::shared_ptr<ObserverBase>>> m_ObserverFuncMap;

public:
	template<typename ObserverType, typename... ParamType>
	void Add(ObserverType* pObserver, ObserverEventCallBack<ParamType...> callBack)
	{
		std::map<ObserverPtr, std::shared_ptr<ObserverBase>>& findObserverMap = m_ObserverFuncMap[callBack];
		auto iter = findObserverMap.find(pObserver);
		if (iter != findObserverMap.end())
			return;

		std::shared_ptr<Observer<ObserverType>> newObserver = std::make_shared<Observer<ObserverType>>(pObserver);
		findObserverMap.insert({ pObserver , newObserver });
	}

	template<typename ObserverType>
	void Remove(ObserverType* pObserver)
	{
		std::map<ObserverFuncPtr, std::map<ObserverPtr, std::shared_ptr<ObserverBase>>>::iterator iter;
		for (iter = m_ObserverFuncMap.begin(); iter != m_ObserverFuncMap.end(); ++iter)
		{
			auto findObserverIter = iter->second.find(pObserver);
			if (findObserverIter == iter->second.end())
				continue;

			iter->second.erase(pObserver);
		}
	}

	template<typename... ParamType>
	void Broadcasting(ParamType... params)
	{
		std::map<ObserverFuncPtr, std::map<ObserverPtr, std::shared_ptr<ObserverBase>>>::iterator funcIter;
		for (funcIter = m_ObserverFuncMap.begin(); funcIter != m_ObserverFuncMap.end(); ++funcIter)
		{
			std::map<ObserverPtr, std::shared_ptr<ObserverBase>>::iterator observerIter;
			for (observerIter = funcIter->second.begin(); observerIter != funcIter->second.end(); ++observerIter)
			{
				ObserverEventCallBack<ParamType...> callBack = static_cast<ObserverEventCallBack<ParamType...>>(funcIter->first);
				if (callBack == nullptr)
					continue;
				callBack(observerIter->second, params...);
			}
		}
	}
};

// 옵저버 패턴을 실제로 사용하는 인터페이스
class ObserverAgent
{
private:
	std::map<std::string, ObserverEventPack> m_ObserverEventMap;

public:
	template<typename ObserverType, typename... ParamType>
	void AddObserver(const std::string eventString, ObserverType* pObserver, ObserverEventCallBack<ParamType...> callBack)
	{
		ObserverEventPack& findEventPack = m_ObserverEventMap[eventString];
		findEventPack.Add<ObserverType>(pObserver, callBack);
	}

	template<typename ObserverType>
	void RemoveObserver(const std::string eventString, ObserverType* pObserver)
	{
		auto iter = m_ObserverEventMap.find(eventString);
		if (iter == m_ObserverEventMap.end())
			return;

		iter->second.Remove<ObserverType>(pObserver);
	}

	template<typename... ParamType>
	void DispatchObserver(const std::string eventName, ParamType... params)
	{
		auto iter = m_ObserverEventMap.find(eventName);
		if (iter == m_ObserverEventMap.end())
			return;

		iter->second.Broadcasting(params...);
	}

	static ObserverAgent* GetStaticClass()
	{
		static ObserverAgent instance;
		return &instance;
	}
};

#define g_pObserverAgent ObserverAgent::GetStaticClass()

namespace ObserverEventName
{
	static const std::string Event1 = "Event1";
	static const std::string Event2 = "Event2";
	static const std::string Event3 = "Event3";
}

namespace ObserverUtil
{
	template<typename T>
	std::shared_ptr<T> Cast(std::shared_ptr<ObserverBase> pObserver)
	{
		if (pObserver == nullptr)
			return nullptr;

		if (pObserver->IsA(T::GetStaticClass()) == false)
			return nullptr;

		return std::static_pointer_cast<T>(pObserver);
	}
}