#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <initializer_list>
#include <iostream>

class EventBase;
class EventBroadCaster;

template<typename T> class EventB;
template<typename T> class EventA;

#define g_pEventBroadCaster EventBroadCaster::GetInstance()

template<typename... ParamType>
using EventCallBack = void(*)(EventBase*, ParamType...);

using ObserverPtr = void*;
using EventFuncPtr = void*;

class EVENT_TYPE
{
public:
	enum : int
	{
		EVENT_TYPE_A = 0,
		EVENT_TYPE_B = 1,
		EVENT_TYPE_MAX
	};

public:
	template<typename T>
	static std::shared_ptr<EventBase> MakeEvent(int eventType, T* pObserver)
	{
		std::shared_ptr<EventBase> pResult = nullptr;
		switch (eventType)
		{
		case EVENT_TYPE_A:
		{
			pResult = std::make_shared<EventA<T>>(pObserver);
		}break;
		case EVENT_TYPE_B:
		{
			pResult = std::make_shared<EventB<T>>(pObserver);
		}break;
		default:
			break;
		}

		return pResult;
	}
};


class EventBroadCaster
{
private:
	std::vector<std::map<EventBase*, std::map<ObserverPtr, EventFuncPtr>>> m_Event;


private:
	EventBroadCaster()
	{
		m_Event.resize(EVENT_TYPE::EVENT_TYPE_MAX);
	}

public:
	template<typename T, typename ObserverType>
	void Register(int eventType, T* pEvent, ObserverType* pObserver, EventFuncPtr pFunc)
	{
		if (m_Event.size() <= (unsigned int)eventType)
			return;
		std::map<EventBase*, std::map<ObserverPtr, EventFuncPtr>>& eventMap = m_Event[eventType];
		std::map<ObserverPtr, EventFuncPtr>& observerMap = eventMap[pEvent];
		observerMap[pObserver] = pFunc;
	}

	template<typename T, typename ObserverType>
	void UnRegister(int eventType, T* pEvent, ObserverType* pObserver)
	{
		if (m_Event.size() <= (unsigned int)eventType)
			return;

		std::map<EventBase*, std::map<ObserverPtr, EventFuncPtr>>& eventMap = m_Event[eventType];
		std::map<EventBase*, std::map<ObserverPtr, EventFuncPtr>>::iterator eventIter = eventMap.find(pEvent);
		if (eventIter == eventMap.end())
			return;

		std::map<ObserverPtr, EventFuncPtr>& observerMap = eventIter->second;
		std::map<ObserverPtr, EventFuncPtr>::iterator observerIter = observerMap.find(pObserver);
		if (observerIter == observerMap.end())
			return;

		observerMap.erase(pObserver);
	}

	template<typename... ParamType>
	void BroadCast(int eventType, ParamType... params)
	{
		if (m_Event.size() <= (unsigned int)eventType)
			return;

		std::map<EventBase*, std::map<ObserverPtr, EventFuncPtr>>::iterator eventIter;
		for (eventIter = m_Event[eventType].begin(); eventIter != m_Event[eventType].end(); ++eventIter)
		{
			std::map<ObserverPtr, EventFuncPtr>::iterator observerIter;
			for (observerIter = eventIter->second.begin(); observerIter != eventIter->second.end(); ++observerIter)
			{
				EventCallBack<ParamType...> callBack = static_cast<EventCallBack<ParamType...>>(observerIter->second);
				if (callBack == nullptr)
					continue;

				callBack(eventIter->first, params...);
			}
		}
	}

	void GetDataCount(int& eventTypeCount, int& eventCount, int& observerCount)
	{
		for (int index = 0; index < m_Event.size(); index++)
		{
			eventTypeCount += 1;
			std::map<EventBase*, std::map<ObserverPtr, EventFuncPtr>>::iterator eventIter;
			for (eventIter = m_Event[index].begin(); eventIter != m_Event[index].end(); ++eventIter)
			{
				eventCount += 1;
				std::map<ObserverPtr, EventFuncPtr>::iterator observerIter;
				for (observerIter = eventIter->second.begin(); observerIter != eventIter->second.end(); ++observerIter)
				{
					observerCount += 1;
				}
			}
		}
	}

	static EventBroadCaster* GetInstance()
	{
		static EventBroadCaster instance;
		return &instance;
	}
};

class EventBase
{
public:
	virtual ~EventBase() {}
};


template<typename T>
class EventA : public EventBase
{
private:
	T* m_pObserver;

public:
	EventA(T* pObserver) :
		m_pObserver(pObserver)
	{
		g_pEventBroadCaster->Register<EventA<T>, T>(EVENT_TYPE::EVENT_TYPE_A ,this, m_pObserver, EventA<T>::PlayEvent);
	}

	~EventA()
	{
		if (g_pEventBroadCaster != nullptr)
			g_pEventBroadCaster->UnRegister<EventA<T>, T>(EVENT_TYPE::EVENT_TYPE_A, this, m_pObserver);
	}

	T* GetObserver()
	{
		return m_pObserver;
	}

	static void PlayEvent(EventBase* pEvent, int a, int b, int c)
	{
		EventA<T>* pEventA = static_cast<EventA<T>*>(pEvent);
		if (pEventA == nullptr)
			return;

		if (pEventA->m_pObserver == nullptr)
			return;

		pEventA->m_pObserver->PlayEventA(a, b, c);
	}
};

template<typename T>
class EventB : public EventBase
{
private:
	T* m_pObserver;

public:
	EventB(T* pObserver) :
		m_pObserver(pObserver)
	{
		g_pEventBroadCaster->Register<EventB<T>, T>(EVENT_TYPE::EVENT_TYPE_B, this, m_pObserver, EventB<T>::PlayEvent);
	}

	~EventB()
	{
		if (g_pEventBroadCaster != nullptr)
			g_pEventBroadCaster->UnRegister<EventB<T>, T>(EVENT_TYPE::EVENT_TYPE_B, this, m_pObserver);
	}

	T* GetObserver()
	{
		return m_pObserver;
	}

	static void PlayEvent(EventBase* pEvent, std::string a)
	{
		EventB<T>* pEventA = static_cast<EventB<T>*>(pEvent);
		if (pEventA == nullptr)
			return;

		if (pEventA->m_pObserver == nullptr)
			return;

		pEventA->m_pObserver->PlayEventB(a);
	}
};

class EventRegisterBase
{
public:
	virtual ~EventRegisterBase() {}
};

template<typename T>
class EventRegister : public EventRegisterBase
{
private:
	// 생성과 소멸만 관리하고 아무것도 할 수 없는 변수다.
	std::vector<std::shared_ptr<EventBase>> m_pRegistedEvent;

public:
	template<typename... ParamType>
	EventRegister(T* pObserver, ParamType... params)
	{
		std::initializer_list<int> paramList = { params... };
		for (std::initializer_list<int>::iterator iter = paramList.begin(); iter != paramList.end(); ++iter)
		{
			std::shared_ptr<EventBase> pNewEvent = EVENT_TYPE::MakeEvent<T>(*iter, pObserver);
			if (pNewEvent == nullptr)
				continue;

			m_pRegistedEvent.push_back(std::move(pNewEvent));
		}
	}
};

