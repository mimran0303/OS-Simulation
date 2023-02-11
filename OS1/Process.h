#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <vector>

#include "Command.h"

using namespace std;

enum Status
{
	Idle, // When nothing to di
	Waiting, // Waiting in Queue for resource such as SSD, LOCk or UserConsole
	Running, // On CPU, SSD, User Console
	Terminate // Program finsihed nothing to run
};

class Process
{
public:
	queue<Command*> ReadyQ;
	queue<Command*> SSDQ;
	queue<Command*> LockQ;

	vector<Command*>* CommandList = new vector<Command*>() ;//commands added to
	int i = 0;
	int amount;

	long Timer = 0;

	Status Status = Idle;
	Command* Current()
	{
		if (i >= 0 && i < CommandList->size())
			return CommandList->at(i);
		else
			return NULL;
	}

	void NextCommand()
	{
		i++;
	}

	void Reset()
	{
		Timer = 0;
	}

#if HARDCODED
	Process()
	{
		Commands->push_back(new Command(EVT_NCORES, 2));
		Commands->push_back(new Command(EVT_START, 10));
		Commands->push_back(new Command(EVT_CPU, 10));
		Commands->push_back(new Command(EVT_LOCK, 0));
		Commands->push_back(new Command(EVT_SSD, 20));
		Commands->push_back(new Command(EVT_OUTPUT, 20));
		Commands->push_back(new Command(EVT_UNLOCK, 0));
		Commands->push_back(new Command(EVT_END, 0));
	}
#endif

	void DoWork()
	{
		if (Current() == NULL)
		{
			cout << "WARNING: No command to execute" << endl;
			return;
		}

		Status = Running;

		cout << "process do work " << ToString(Current()->event) << endl;

		if (Current()->event == EVT_NCORES)//we need to
		{

		}
		else if (Current()->event == EVT_START)
		{

		}
		else if (Current()->event == EVT_CPU)
		{
			ReadyQ.push(Current());
			cout << "In the Queue we have: " << ToString(ReadyQ.front()->event) << endl;
		}
		else if (Current()->event == EVT_LOCK)
		{
			LockQ.push(Current());
			cout << "In the Queue we have: " << ToString(LockQ.front()->event) << endl;
		}
		else if (Current()->event == EVT_SSD)
		{
			SSDQ.push(Current());
			cout << "In the Queue we have: " << ToString(SSDQ.front()->event) << endl;
		}
		else if (Current()->event == EVT_UNLOCK)
		{
			
		}
		else if (Current()->event == EVT_END)
		{
			Status = Terminate;
		}
		Timer++;
		i++;
	}

	void Print()
	{
		for (auto c : *CommandList)
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
