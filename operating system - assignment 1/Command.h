#pragma once

#include "Event.h"

class Command
{
public:

	Event event;
	int time;

	Command()
	{
		event = EVT_START;
		time = 0;
	};

	Command(Event _event, int _time)
	{
		event = _event;
		time = _time;

	};
};
