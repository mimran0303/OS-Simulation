#pragma once

#include<iostream>
#include<queue>
#include"Process.h"
#include"Command.h"
#include"Hardware.h"

using namespace std;

class OperatingSystem
{
public: 
	

	ReadyQueue *ReadyQ;
	SSDQueue *SSDQ;
	LockQueue *LockQ[LOCK_COUNT];
	ProcessVector *ProcessList;

	int cpu_amount=0;
	OperatingSystem()
	{		
		ProcessList = new ProcessVector;
		ReadyQ = new ReadyQueue();
		SSDQ = new SSDQueue();

		for (int j = 0;j < LOCK_COUNT;j++)
		{
			LockQ[j] = new LockQueue();
		}
	}

	void DoWork()
	{
		cout << " OS DOING WORK " << endl;

		for (int i = 0;i < ProcessList->size();i++)
		{
			Process* p = ProcessList->at(i);
			ExecuteCommand(p);
		}

		for (int j = 0;j < LOCK_COUNT; j++)
		{
			//LockQ[j]->DoWork();
		}


	}

	void ExecuteCommand(Process* process)
	{
		if (process->Current() == NULL)
		{
			cout << "WARNING: No command to execute" << endl;
			return;
		}
		else if (process ->Current()->event == EVT_START) //new process created after every start
		{
			cout << "New Process " << ToString(process->Current()->event) << endl;
			process->Status = Running;
		}
		else if (process->Current()->event == EVT_CPU)//process goes to RQ
		{
			process->Status = Waiting;
			ReadyQ->push(process);
			cout << "Process added to ReadyQ" << endl;
		}
		else if (process->Current()->event == EVT_SSD)//goes to ssd queue IF more than one process trying to acecess SSD
		{
			process->Status = Waiting;
			SSDQ->push(process);
			cout << "Process added to SSDQ" << endl;
		}
		else if (process->Current()->event == EVT_LOCK)//lock specified by process is in locked state
		{
			process->Status = Waiting; //PROCESS DOESNT GO HERE
			LockQ[0]->push(process);
			cout << "Process added to LockQ " << endl;
		}	
		else if (process->Current()->event == EVT_UNLOCK)//lock specified by process is in unlocked state
		{
			//PROCESS DOESNT GO HERE
			//we will dequeue if necessary
		}
		else if (process->Current()->event == EVT_OUTPUT)//goes to user immediately
		{
		}
		
		else if (process->Current()->event == EVT_END)//process terminates
		{
			process->Status = Terminate;
		}

	}
};

