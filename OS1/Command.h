#pragma once
#include<vector>
#include "Event.h"
#include "Definition.h"
#include"Process.h"

using namespace std;

int StringCompare(const char* string1, const char* string2);

class Command
{
public:

	// Event and Time are required values for object
	Event event;
	int num;

	// Following can be manipulated or changes later
	int i;
	int _amount;


	Command()
	{
		event = EVT_START;
		num = 0;
	};

	Command(Event _event)
	{
		event = _event;
		num = 0;
	}

	Command(Event _event, int _time)
	{
		event = _event;
		num = _time;
	};
	
	Command(string _param_ev /* CPU */, int _param_time)
	{
		num = _param_time;

		if (StringCompare(_param_ev.c_str(), "START")==0) //adds to global time
		{
			event = EVT_START;
		}
		if (StringCompare(_param_ev.c_str(), "CPU") == 0) //adds to global time
		{
			event = EVT_CPU;
		}
		if (StringCompare(_param_ev.c_str(), "SSD") == 0) //adds to global time
		{
			event = EVT_SSD;
		}
		if (StringCompare(_param_ev.c_str(), "OUTPUT") == 0) //adds to global time
		{
			event = EVT_OUTPUT;
		}
		if (StringCompare(_param_ev.c_str(), "NCORES") == 0) //amount of CPU
		{
			event = EVT_NCORES;
		}
		if (StringCompare(_param_ev.c_str(), "LOCK") == 0) //targets a lock
		{
			event = EVT_LOCK;
		}
		if (StringCompare(_param_ev.c_str(), "UNLOCK") == 0)//targets a lock
		{
			event = EVT_UNLOCK;
		}
		if (StringCompare(_param_ev.c_str(), "END") == 0)//doesnt have time, and no amount
		{
			event = EVT_END;
			num = 0;
		}
	}


	Command(string _param_ev)
	{
		if (StringCompare(_param_ev.c_str(), "START") == 0)//doesnt have time, and no amount
		{
			event = EVT_START;
			num = 0;
		}
		if (StringCompare(_param_ev.c_str(), "END") == 0)//doesnt have time, and no amount
		{
			event = EVT_END;
			num = 0;
		}
	}
};



