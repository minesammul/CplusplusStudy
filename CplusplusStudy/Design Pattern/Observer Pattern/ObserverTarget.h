#pragma once

#include <memory>

class ObserverEventRegisterBase;
class ObserverBase;

class ObserverTargetA
{
private:
	std::shared_ptr<ObserverEventRegisterBase> m_pObserverEventRegister;

public:
	ObserverTargetA();

public:
	static void AddObserverEvent(ObserverTargetA* pThis);
	static void RemoveObserverEvent(ObserverTargetA* pThis);
	static void OnObserverEvent_Event1(std::shared_ptr<ObserverBase> pObserver, int param1, float param2, double param3);
	static void OnObserverEvent_Event2(std::shared_ptr<ObserverBase> pObserver, int param1, int param2);
	static void OnObserverEvent_Event3(std::shared_ptr<ObserverBase> pObserver, double param1);
};

class ObserverTargetB
{
private:
	std::shared_ptr<ObserverEventRegisterBase> m_pObserverEventRegister;

public:
	ObserverTargetB();

public:
	static void AddObserverEvent(ObserverTargetB* pThis);
	static void RemoveObserverEvent(ObserverTargetB* pThis);
	static void OnObserverEvent_Event1(std::shared_ptr<ObserverBase> pObserver, int param1, float param2, double param3);
	static void OnObserverEvent_Event2(std::shared_ptr<ObserverBase> pObserver, int param1, int param2);
};

class ObserverTargetC
{
private:
	std::shared_ptr<ObserverEventRegisterBase> m_pObserverEventRegister;

public:
	ObserverTargetC();

public:
	static void AddObserverEvent(ObserverTargetC* pThis);
	static void RemoveObserverEvent(ObserverTargetC* pThis);
	static void OnObserverEvent_Event1(std::shared_ptr<ObserverBase> pObserver, int param1, float param2, double param3);
};

