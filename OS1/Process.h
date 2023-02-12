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
	int c = 0;
	int amount;

	long Timer = 0;
	long TotalTime = 0;

	Status Status = Idle;
	Command* Current()
	{
		if (c >= 0 && c < CommandList->size())
			return CommandList->at(c);
		else
			return NULL;
	}

	void NextCommand()
	{
		c++;
	}

	void Reset()
	{
		Timer = 0;
	}

	void DoWork()
	{
		Timer++;
		TotalTime++;
	}

	void Print()
	{
		for (auto c : *CommandList)
		{
			cout << "event:" << c->event << " time:" << c->num << endl;
		}
	}
};

