#pragma once

#include "Event.h"

class Command
{
public:
	Event event;
	int time;

	Command()
	{
	};

	Command(Event _event, int _time)
	{
		event = _event;
		time = _time;

	};
};
