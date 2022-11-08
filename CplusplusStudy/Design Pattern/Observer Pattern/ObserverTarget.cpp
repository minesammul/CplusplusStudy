#include "ObserverTarget.h"
#include "ObserverAgent.h"
#include <iostream>
#include <memory>

ObserverTargetA::ObserverTargetA():
	m_pEventRegister(std::make_shared<EventRegister<ObserverTargetA>>(this, EVENT_TYPE::EVENT_TYPE_A, EVENT_TYPE::EVENT_TYPE_B))
{

}

void ObserverTargetA::PlayEventA(int a, int b, int c)
{
	std::cout << "ObserverTargetA::PlayEventA " << a << " " << b << " " << c << " " << std::endl;
}

void ObserverTargetA::PlayEventB(std::string a)
{
	std::cout << "ObserverTargetA::PlayEventB " << a << std::endl;
}

ObserverTargetB::ObserverTargetB():
	m_pEventRegister(std::make_shared<EventRegister<ObserverTargetB>>(this, EVENT_TYPE::EVENT_TYPE_A, EVENT_TYPE::EVENT_TYPE_B))
{

}

void ObserverTargetB::PlayEventA(int a, int b, int c)
{
	std::cout << "ObserverTargetB::PlayEventA " << a << " " << b << " " << c << " " << std::endl;
}

void ObserverTargetB::PlayEventB(std::string a)
{
	std::cout << "ObserverTargetB::PlayEventB " << a << std::endl;
}

ObserverTargetC::ObserverTargetC():
	m_pEventRegister(std::make_shared<EventRegister<ObserverTargetC>>(this, EVENT_TYPE::EVENT_TYPE_A, EVENT_TYPE::EVENT_TYPE_B))
{

}

void ObserverTargetC::PlayEventA(int a, int b, int c)
{
	std::cout << "ObserverTargetC::PlayEventA " << a << " " << b << " " << c << " " << std::endl;
}

void ObserverTargetC::PlayEventB(std::string a)
{
	std::cout << "ObserverTargetC::PlayEventB " << a << std::endl;
}
