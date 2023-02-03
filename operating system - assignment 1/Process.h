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

	vector<Command*>* List = new vector<Command*>();
	
	int i = 0;
	Command* Current()
	{
		if (i >= 0 && i < List->size())
			return List->at(i);
		else
			return NULL;
	}

	Process()
	{
		List->push_back(new Command(NCORES, 2));
		List->push_back(new Command(START, 10));
		List->push_back(new Command(CPU, 10));
		List->push_back(new Command(LOCK, 0));
		List->push_back(new Command(SSD, 20));
		List->push_back(new Command(UNLOCK, 0));
		List->push_back(new Command(END, 0));
	}

	void DoWork()
	{
		if (Current() == NULL)
		{
			cout << "WARNING: No command to execute" << endl;
			return;
		}

		cout << "process do work " << ToString(Current()->event) << endl;

		if (Current()->event == NCORES)
		{

		}
		else if (Current()->event == START)
		{

		}
		else if (Current()->event == CPU)
		{

		}
		else if (Current()->event == LOCK)
		{

		}
		else if (Current()->event == SSD)
		{

		}
		else if (Current()->event == UNLOCK)
		{

		}
		else if (Current()->event == END)
		{

		}

		i++;
	}

	void Print()
	{
		for (auto c : *List)
		{
			cout << "event:" << c->event << " time:" << c->time << endl;
		}
	}
};

//
// ----- Developer Examples and Notes -----
//
int t = 0;
bool in_use_ssd = false;

void ProcessExample()
{
	if (t == 0)
	{
		in_use_ssd = true;
	}
	if (t <= 5)
	{
		cout << "I am here " << t << " seconds" << endl;
	}

	if (7 > t && t > 5) //t becomes stuck at 6
	{
		cout << "done!" << endl;
		in_use_ssd = false;
	}
	if (t == 15)
	{
		t = 0;
	}
	t++;
}
