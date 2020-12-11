#pragma once

#include "message_queue_bus_dispatcher.h"


class GlobalManager final
{
private:
	GlobalManager()
		:
		md { MessageDispatcher::getInstance() }
	{
	
	}
public:
	GlobalManager( const GlobalManager& fs ) = delete;
	GlobalManager& operator=( const GlobalManager& fs ) = delete;

	static GlobalManager& getInstance()
	{
		static GlobalManager instance{};
		return instance;
	}

	// Global Message Dispatcher
	MessageDispatcher& md;
};


#define getGM GlobalManager::getInstance()