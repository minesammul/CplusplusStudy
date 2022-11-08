
#pragma once
#include <iostream>
#include "Design Pattern/Observer Pattern/ObserverAgent.h"
#include "Design Pattern/Observer Pattern/ObserverTarget.h"

int main()
{
	{
		{
			int eventTypeCount = 0, eventCount = 0, observerCount = 0;
			g_pEventBroadCaster->GetDataCount(eventTypeCount, eventCount, observerCount);
			std::cout <<"eventTypeCount:" << eventTypeCount << " eventCount:" << eventCount << " observerCount:" << observerCount << std::endl;
		}

		ObserverTargetA a;

		{
			int eventTypeCount = 0, eventCount = 0, observerCount = 0;
			g_pEventBroadCaster->GetDataCount(eventTypeCount, eventCount, observerCount);
			std::cout << "eventTypeCount:" << eventTypeCount << " eventCount:" << eventCount << " observerCount:" << observerCount << std::endl;
		}

		g_pEventBroadCaster->BroadCast(EVENT_TYPE::EVENT_TYPE_A, 1, 2, 3);
		g_pEventBroadCaster->BroadCast(EVENT_TYPE::EVENT_TYPE_B, std::string("EVENT_TYPE_B"));
		std::cout << std::endl;
	}

	{
		ObserverTargetB b;
		g_pEventBroadCaster->BroadCast(EVENT_TYPE::EVENT_TYPE_A, 1, 2, 3);
		g_pEventBroadCaster->BroadCast(EVENT_TYPE::EVENT_TYPE_B, std::string("EVENT_TYPE_B"));
		std::cout << std::endl;
	}

	{
		ObserverTargetC c;
		g_pEventBroadCaster->BroadCast(EVENT_TYPE::EVENT_TYPE_A, 1, 2, 3);
		g_pEventBroadCaster->BroadCast(EVENT_TYPE::EVENT_TYPE_B, std::string("EVENT_TYPE_B"));
		std::cout << std::endl;
	}

	{
		ObserverTargetA a;
		ObserverTargetB b, b1, b2;
		ObserverTargetC c;
		g_pEventBroadCaster->BroadCast(EVENT_TYPE::EVENT_TYPE_A, 1, 2, 3);
		g_pEventBroadCaster->BroadCast(EVENT_TYPE::EVENT_TYPE_B, std::string("EVENT_TYPE_B"));
		std::cout << std::endl;
	}
}

