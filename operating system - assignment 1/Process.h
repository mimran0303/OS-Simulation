#pragma once

#include <iostream>
#include<string>
#include <queue>
#include<vector>
#include "Command.h"

using namespace std;

enum Status
{
	Idle,
	Waiting,
	Running,
	Busy,
	Finish
};

class Process
{
public:
	queue<Command*> ReadyQ;
	queue<Command*> SSDQ;
	queue<Command*> LockQ;

	static const char* Current_Command;
	long Timer = 0;
	vector<Command*>* List = new vector<Command*>();
	
	Status Status = Idle;

	int i = 0;
	int _e;
	Process(int e)
	{
		_e = e;
	}

	Command* Current()
	{
		if (i >= 0 && i < List->size())
			return List->at(i);
		else
			return NULL;
	}
	void Next_Command()
	{
		i++;
	}
	void Reset()
	{
		Timer = 0;
	}
	Process()
	{
		List->push_back(new Command(EVENT_NCORES, 2));
		List->push_back(new Command(EVENT_START, 10));
		List->push_back(new Command(EVENT_CPU, 10));
		List->push_back(new Command(EVENT_LOCK, 0));
		List->push_back(new Command(EVENT_SSD, 20));
		List->push_back(new Command(EVENT_UNLOCK, 0));
		List->push_back(new Command(EVENT_END, 0));
	}

	void DoWork()
	{
		if (Current() == NULL)
		{
			cout << "WARNING: No command to execute" << endl;
			return;
		}

		Status = Running;

		cout << "process do work " << ToString(Current()->event) << endl;

		if (Current()->event == EVENT_NCORES)
		{

		}
		else if (Current()->event == EVENT_START)
		{

		}
		else if (Current()->event == EVENT_CPU)
		{
			ReadyQ.push(Current());
			cout << "In the Queue we have: " << ToString(ReadyQ.front()->event) << endl;
		}
		else if (Current()->event == EVENT_LOCK)
		{
			LockQ.push(Current());
			cout << "In the Queue we have: " << ToString(LockQ.front()->event) << endl;
		}
		else if (Current()->event == EVENT_SSD)
		{
			SSDQ.push(Current());
			cout << "In the Queue we have: " << ToString(SSDQ.front()->event) << endl;
		}
		else if (Current()->event == EVENT_UNLOCK)
		{
			
		}
		else if (Current()->event == EVENT_END)
		{
			Status = Finish;
		}
		Timer++;
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
