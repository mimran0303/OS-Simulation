#pragma once
#include<vector>
#include "Event.h"
#include"Process.h"

using namespace std;

class Command
{
public:

	// Event and Time are required values for object
	Event event;
	int time;

	// Following can be manipulated or changes later
	string ev;
	int i;
	int _amount;


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

	Command(string _param_ev /* CPU */, int _param_time)
	{
		ev = _param_ev;
		time = _param_time;

		if (_stricmp(_param_ev.c_str(), "START")==0)
		{
			event = EVT_START;
		}
		if (_stricmp(_param_ev.c_str(), "CPU") == 0)
		{
			event = EVT_CPU;
		}
		if (_stricmp(_param_ev.c_str(), "SSD") == 0)
		{
			event = EVT_SSD;
		}
		if (_stricmp(_param_ev.c_str(), "USER") == 0)
		{
			event = EVT_OUTPUT;
		}
	}

	/*
	Command(string _event, int amount)
	{
		_amount = amount;
		_event = event;

		if (_event == "NCORES") //doesnt have time, number indicates how many cpus
		{
			event = EVT_NCORES;
			cin >> amount;
		}
		
	}
	Command(string _event, int _i)
	{
		_i = i;
		_event = event;

		if (_event == "LOCK")//doesnt have time, int indicates which lock out of 64
		{
			event = EVT_LOCK;
		}
		if (_event == "UNLOCK")//doesnt have time int indicates which lock out of 64
		{
			event = EVT_UNLOCK;
		}
	}
	*/

	Command(string _event)
	{
		/*void Split(string instruct)
		{
			char* split = strtok(instruct, " ");
			cout << split << endl;
		}*/

		/*
			result[] = string split using strtok

			Example:
				END will split into { "END" }
					result[0] => "END"
				NCORE 2 will split into { "NCORE", "2" }
					result[0] => "NCORE"
					result[1] => "2"
				SLEEP 20 will split into { "SLEEP", "20" }
		*/
		_event = event;
		if (_event == "END")//doesnt have time, and no amount
		{
			event = EVT_END;
		}
	}

	vector<string>* _Split(string& instruct) //input originally char instruct[]
	{
		vector<string>* result = new vector<string>();
		char* split = strtok(_strdup(instruct.c_str()), " ");
		while (split != NULL)
		{
			cout << split << endl;
			result->push_back(split);
			split = strtok(NULL, " ");
		} 
		return result;
	}
};



