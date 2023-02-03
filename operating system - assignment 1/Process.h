#pragma once

#include <iostream>
#include<string>
#include<vector>

using namespace std;

enum Event 
{ 
	START, END, CPU, SSD, NCORES, LOCK, UNLOCK
};

const char* Event(Event e)
{
	switch (e) 
	{
	case START:
		return "START";
	case END:
		return "END";
	case CPU:
		return "CPU";
	case SSD:
			return "SSD";
	case NCORES:
		return"NCORES";
	case LOCK:
		return "LOCK";
	case UNLOCK:
		return "UNLOCK";
	}
}
class Command //command is object
{
public:
	Event event;
	int time;

	Command(Event _event, int _time)
	{
		event = _event;
		time = _time;

	};
	Command()
	{};

};

class Process
{
public:
	vector<Command*>* instructions = new vector<Command*>();
	//Command instruct("CPU", 10);

	Process()
	{
		instructions->push_back(new Command(NCORES, 2));
		instructions->push_back(new Command(START, 10));
		instructions->push_back(new Command(CPU, 10));
		instructions->push_back(new Command(LOCK, 0));
		instructions->push_back(new Command(SSD, 20));
		instructions->push_back(new Command(UNLOCK, 0));
		instructions->push_back(new Command(END, 0));
	}

	void Print()
	{
		for (auto c : *instructions)
		{
			cout << "event:" << c->event << " time:" << c->time << endl;
		}
	}
};

