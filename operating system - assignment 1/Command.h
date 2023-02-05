#pragma once

#include "Event.h"

class Command
{
public:
	Event event;
	int time;
	int value;
	Command()
	{
	};
	Command(int i)
	{
		value = i;
	}
	Command(Event _event, int _time)
	{
		event = _event;
		time = _time;

	};
};
