#include "ObserverTarget.h"
#include "ObserverAgent.h"
#include <iostream>

ObserverTargetA::ObserverTargetA()
{
	m_pObserverEventRegister = std::make_shared<ObserverEventRegister<ObserverTargetA>>(
		this,
		ObserverTargetA::AddObserverEvent,
		ObserverTargetA::RemoveObserverEvent);
}

void ObserverTargetA::AddObserverEvent(ObserverTargetA* pThis)
{
	g_pObserverAgent->AddObserver<ObserverTargetA>(ObserverEventName::Event1, pThis, ObserverTargetA::OnObserverEvent_Event1);
	g_pObserverAgent->AddObserver<ObserverTargetA>(ObserverEventName::Event2, pThis, ObserverTargetA::OnObserverEvent_Event2);
	g_pObserverAgent->AddObserver<ObserverTargetA>(ObserverEventName::Event3, pThis, ObserverTargetA::OnObserverEvent_Event3);
}

void ObserverTargetA::RemoveObserverEvent(ObserverTargetA* pThis)
{
	g_pObserverAgent->RemoveObserver<ObserverTargetA>(ObserverEventName::Event1, pThis);
	g_pObserverAgent->RemoveObserver<ObserverTargetA>(ObserverEventName::Event2, pThis);
	g_pObserverAgent->RemoveObserver<ObserverTargetA>(ObserverEventName::Event3, pThis);
}

void ObserverTargetA::OnObserverEvent_Event1(std::shared_ptr<ObserverBase> pObserver, int param1, float param2, double param3)
{
	if (pObserver == nullptr)
		return;

	std::shared_ptr<Observer<ObserverTargetA>> pObserverTargetA = ObserverUtil::Cast<Observer<ObserverTargetA>>(pObserver);
	if (pObserverTargetA == nullptr)
		return;

	ObserverTargetA* pThis = pObserverTargetA->GetObserver();
	if (pThis == nullptr)
		return;

	std::cout << pThis << std::endl;
	std::cout << "ObserverTargetA::OnObserverEvent_Event1 " << param1 << " " << param2 << " " << param3 << std::endl;
}

void ObserverTargetA::OnObserverEvent_Event2(std::shared_ptr<ObserverBase> pObserver, int param1, int param2)
{
	if (pObserver == nullptr)
		return;

	std::shared_ptr<Observer<ObserverTargetA>> pObserverTargetA = ObserverUtil::Cast<Observer<ObserverTargetA>>(pObserver);
	if (pObserverTargetA == nullptr)
		return;

	ObserverTargetA* pThis = pObserverTargetA->GetObserver();
	if (pThis == nullptr)
		return;

	std::cout << pThis << std::endl;
	std::cout << "ObserverTargetA::OnObserverEvent_Event2 " << param1 << " " << param2 << std::endl;
}

void ObserverTargetA::OnObserverEvent_Event3(std::shared_ptr<ObserverBase> pObserver, double param1)
{
	if (pObserver == nullptr)
		return;

	std::shared_ptr<Observer<ObserverTargetA>> pObserverTargetA = ObserverUtil::Cast<Observer<ObserverTargetA>>(pObserver);
	if (pObserverTargetA == nullptr)
		return;

	ObserverTargetA* pThis = pObserverTargetA->GetObserver();
	if (pThis == nullptr)
		return;

	std::cout << pThis << std::endl;
	std::cout << "ObserverTargetA::OnObserverEvent_Event3 " << param1 << std::endl;
}

ObserverTargetB::ObserverTargetB()
{
	m_pObserverEventRegister = std::make_shared<ObserverEventRegister<ObserverTargetB>>(
		this,
		ObserverTargetB::AddObserverEvent,
		ObserverTargetB::RemoveObserverEvent);
}

void ObserverTargetB::AddObserverEvent(ObserverTargetB* pThis)
{
	g_pObserverAgent->AddObserver<ObserverTargetB>(ObserverEventName::Event1, pThis, ObserverTargetB::OnObserverEvent_Event1);
	g_pObserverAgent->AddObserver<ObserverTargetB>(ObserverEventName::Event2, pThis, ObserverTargetB::OnObserverEvent_Event2);
}

void ObserverTargetB::RemoveObserverEvent(ObserverTargetB* pThis)
{
	g_pObserverAgent->RemoveObserver<ObserverTargetB>(ObserverEventName::Event1, pThis);
	g_pObserverAgent->RemoveObserver<ObserverTargetB>(ObserverEventName::Event2, pThis);
}

void ObserverTargetB::OnObserverEvent_Event1(std::shared_ptr<ObserverBase> pObserver, int param1, float param2, double param3)
{
	if (pObserver == nullptr)
		return;

	std::shared_ptr<Observer<ObserverTargetB>> pObserverTarget = ObserverUtil::Cast<Observer<ObserverTargetB>>(pObserver);
	if (pObserverTarget == nullptr)
		return;

	ObserverTargetB* pThis = pObserverTarget->GetObserver();
	if (pThis == nullptr)
		return;

	std::cout << pThis << std::endl;
	std::cout << "ObserverTargetB::OnObserverEvent_Event1 " << param1 << " " << param2 << " " << param3 << std::endl;
}

void ObserverTargetB::OnObserverEvent_Event2(std::shared_ptr<ObserverBase> pObserver, int param1, int param2)
{
	if (pObserver == nullptr)
		return;

	std::shared_ptr<Observer<ObserverTargetB>> pObserverTarget = ObserverUtil::Cast<Observer<ObserverTargetB>>(pObserver);
	if (pObserverTarget == nullptr)
		return;

	ObserverTargetB* pThis = pObserverTarget->GetObserver();
	if (pThis == nullptr)
		return;

	std::cout << pThis << std::endl;
	std::cout << "ObserverTargetB::OnObserverEvent_Event2 " << param1 << " " << param2 << std::endl;
}

ObserverTargetC::ObserverTargetC()
{
	m_pObserverEventRegister = std::make_shared<ObserverEventRegister<ObserverTargetC>>(
		this,
		ObserverTargetC::AddObserverEvent,
		ObserverTargetC::RemoveObserverEvent);
}

void ObserverTargetC::AddObserverEvent(ObserverTargetC* pThis)
{
	g_pObserverAgent->AddObserver<ObserverTargetC>(ObserverEventName::Event1, pThis, ObserverTargetC::OnObserverEvent_Event1);
}

void ObserverTargetC::RemoveObserverEvent(ObserverTargetC* pThis)
{
	g_pObserverAgent->RemoveObserver<ObserverTargetC>(ObserverEventName::Event1, pThis);
}

void ObserverTargetC::OnObserverEvent_Event1(std::shared_ptr<ObserverBase> pObserver, int param1, float param2, double param3)
{
	if (pObserver == nullptr)
		return;

	std::shared_ptr<Observer<ObserverTargetC>> pObserverTarget = ObserverUtil::Cast<Observer<ObserverTargetC>>(pObserver);
	if (pObserverTarget == nullptr)
		return;

	ObserverTargetC* pThis = pObserverTarget->GetObserver();
	if (pThis == nullptr)
		return;

	std::cout << pThis << std::endl;
	std::cout << "ObserverTargetC::OnObserverEvent_Event1 " << param1 << " " << param2 << " " << param3 << std::endl;
}