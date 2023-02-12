#pragma once

#include<iostream>
#include<queue>
#include"Process.h"
#include"Command.h"
#include"Hardware.h"

using namespace std;

typedef queue<Process*> LockQueue;
typedef queue<Process*> ReadyQueue;
typedef queue<Process*> SSDQueue;
typedef vector<Process*> ProcessVector;

extern const int LOCK_COUNT;

int ms=0;

class OperatingSystem
{
public: 
	bool lock = true;
	bool unlocked = false;

	ReadyQueue *ReadyQ;
	SSDQueue *SSDQ;
	LockQueue *LockQ[4];
	ProcessVector *ProcessList;

	int cpu_amount=0;
	OperatingSystem()
	{		
		ProcessList = new ProcessVector;
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

		for (int j = 0;j < LOCK_COUNT; j++)
		{
			//LockQ[j]->DoWork();
		}

		for (int i = 0;i < ProcessList->size();i++)
		{
			Process* p = ProcessList->at(i);
			p->DoWork();
		}
	}

	void Process_Handler(Process* process)
	{
		if (process->Current() == NULL)
		{
			cout << "WARNING: No command to execute" << endl;
			return;
		}
		else if (process ->Current()->event == EVT_START) //new process created after every start
		{
			process->Status = Running;
			ms += ms;
		}
		else if (process->Current()->event == EVT_CPU)//process goes to RQ
		{
		
			process->Status = Waiting;
			ReadyQ->push(process);
			ms += ms;
		}
		else if (process->Current()->event == EVT_LOCK)//lock specified by process is in locked state
		{
			//process->Status = Waiting; //PROCESS DOESNT GO HERE
			LockQ[0]->push(process);
		}
	
		else if (process->Current()->event == EVT_SSD)//goes to ssd queue IF more than one process trying to acecess SSD
		{
			process->Status = Waiting;
			SSDQ->push(process);
			ms += ms;
		}
		else if (process->Current()->event == EVT_OUTPUT)//goes to user immediately
		{
			ms += ms;
		}
		else if (process->Current()->event == EVT_UNLOCK)//lock specified by process is in unlocked state
		{
			//PROCESS DOESNT GO HERE
		}
		else if (process->Current()->event == EVT_END)//process terminates
		{
			process->Status = Terminate;
		}

	}
};

