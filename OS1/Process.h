#pragma once

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "Command.h"

using namespace std;

enum Status
{
	Ready, // When ready to go to next state
	Blocked, // Waiting in Queue for resource such as SSD, LOCk or UserConsole
	Running, // On CPU, SSD, User Console
	Terminated // Program finsihed nothing to run
};

string ToString(Status s)
{
	switch (s)
	{
	case Ready:
		return "Ready";
	case Blocked:
		return "Blocked";
	case Running:
		return "Running";
	case Terminated:
		return "Terminated";
	}
}

class Process
{
public:

	int Pid;

	vector<Command*>* CommandList = new vector<Command*>() ;//commands added to
	int c = 0;
	int amount;

	long MaxTimer = 0;
	long Timer = 0; //starting time is specifies by START
	long TotalTime = 0;

	Status Status = Ready;

	bool Report = false;

	Process(int pid)
	{
		Pid = pid;
	}

	Command* CurrentCommand()
	{
		if (c >= 0 && c < CommandList->size())
			return CommandList->at(c);
		else
			return NULL;
	}

	void MoveToNextCommand()
	{
		c++;
	}

	bool IsTimerExpired()
	{
		return Timer >= MaxTimer;
	}

	void SetTimer(long max)
	{
		MaxTimer = max;
		ResetTimer();
	}

	void ResetTimer()
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

void ReportProcessStatus(Process* p, bool force = false)
{
	if (p->Report || force)
	{
		cout << "Process: " << p->Pid << ", "
			<< "Command: " << ToString(p->CurrentCommand()->event) << ", "
			<< "Status: " << ToString(p->Status) << ", "
			<< "Timer: " << p->Timer << ", "
			<< "Total Time: " << p->TotalTime << ", "
			<< endl;
		p->Report = false;
	}
}
