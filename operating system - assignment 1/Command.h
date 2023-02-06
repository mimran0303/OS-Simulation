#pragma once
#include<vector>
#include "Event.h"
#include"Process.h"

using namespace std;

class Command
{
public:

	string ev;
	Event event;

	int time;
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

	Command(string _ev, int _time)
	{
		_ev = ev;
		time = _time;
		if (_ev == "START")//adds to time and amount of processes
		{
			event = EVT_START;
		}
		if (_ev == "CPU")
		{
			event = EVT_CPU;
		}
		if (_ev == "SSD")
		{
			event = EVT_SSD;
		}
		if (_ev == "USER")
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
			split = strtok(NULL, " ");
		}
		return result;
	}
};
