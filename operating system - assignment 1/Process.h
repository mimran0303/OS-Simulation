#pragma once

#include <iostream>
#include<string>
#include<vector>
#include "Command.h"

using namespace std;

class Process
{
public:

	static const char* Current_Command;

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
	void DoWork()
	{

	}

	void Print()
	{
		for (auto c : *instructions)
		{
			cout << "event:" << c->event << " time:" << c->time << endl;
		}
	}
};

