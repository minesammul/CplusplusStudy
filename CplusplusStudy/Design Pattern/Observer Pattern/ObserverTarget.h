#pragma once

#include <memory>
#include <string>

class EventRegisterBase;

class ObserverTargetA
{
private:
	std::shared_ptr<EventRegisterBase> m_pEventRegister;

public:
	ObserverTargetA();

public:
	void PlayEventA(int a, int b, int c);
	void PlayEventB(std::string a);
};

class ObserverTargetB
{
private:
	std::shared_ptr<EventRegisterBase> m_pEventRegister;

public:
	ObserverTargetB();

public:
	void PlayEventA(int a, int b, int c);
	void PlayEventB(std::string a);
};

class ObserverTargetC
{
private:
	std::shared_ptr<EventRegisterBase> m_pEventRegister;

public:
	ObserverTargetC();

public:
	void PlayEventA(int a, int b, int c);
	void PlayEventB(std::string a);
};

