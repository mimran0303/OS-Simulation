#pragma once

#include<iostream>
#include<queue>
#include"Process.h"
#include"Command.h"

using namespace std;

typedef queue<Process*> LockQueue;
typedef queue<Process*> ReadyQueue;
typedef queue<Process*> SSDQueue;

class OperatingSystem
{
public:

	ReadyQueue *ReadyQ;
	SSDQueue *SSDQ;
	LockQueue *LockQ[4];

	OperatingSystem()
	{		
		ReadyQ = new ReadyQueue();
		SSDQ = new SSDQueue();

		for (int j = 0;j < 4;j++)
		{
			LockQ[j] = new LockQueue();
		}
	}

	void DoWork()
	{
		cout << " OS DOING WORK " << endl;
		// ReadyQ->DoWork();
		// SSDQ->DoWork();

		for (int j = 0;j < 4;j++)
		{
			// LockQ[j]->DoWork();
		}
	}
	void Process_Handler(Process* process)
	{
		if (process->Current() == NULL)
		{
			cout << "WARNING: No command to execute" << endl;
			return;
		}

		if (process->Current()->event == EVT_NCORES)
		{

		}
		else if (process ->Current()->event == EVT_START)
		{
			process->Status = Running;
		}
		else if (process->Current()->event == EVT_CPU)
		{
			process->Status = Waiting;
			ReadyQ->push(process);
		}
		else if (process->Current()->event == EVT_LOCK)
		{
			process->Status = Waiting;
			LockQ[0]->push(process);
		}
	
		else if (process->Current()->event == EVT_SSD)
		{
			process->Status = Waiting;
			SSDQ->push(process);
		}
		else if (process->Current()->event == EVT_UNLOCK)
		{

		}
		else if (process->Current()->event == EVT_END)
		{
			process->Status = Terminate;
		}
		
		
	}
};

