#pragma once

#include<iostream>
#include<queue>
#include "UserConsole.h"
#include"Process.h"
#include"Command.h"
#include"Hardware.h"

using namespace std;

class OperatingSystem
{
public: 
	
	UserConsole* UC;
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

			if (p->Status==Ready)
			{
				ExecuteNextCommand(p);
			}
		}
	}

	void ExecuteNextCommand(Process* process)
	{
		process->MoveToNextCommand();

		if (process->CurrentCommand() == NULL)
		{
			cout << "WARNING: No command to execute" << endl;
			return;
		}
#if PLACEHOLDER_ONLY 
		else if (process ->CurrentCommand()->event == EVT_START) 
		{
			// Actual implementation of EVT_START is in main() that creates a new process
		}
#endif
		else if (process->CurrentCommand()->event == EVT_CPU)//process goes to RQ
		{
			ReadyQ->push(process);
			process->Status = Blocked;
			cout << "Process added to ReadyQ" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_SSD)//goes to ssd queue IF more than one process trying to acecess SSD
		{
			SSDQ->push(process);
			process->Status = Blocked;
			cout << "Process added to SSDQ" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_LOCK)//lock specified by process is in locked state
		{
			LockQ[0]->push(process);
			process->Status = Blocked; 
			cout << "Process added to LockQ " << endl;
		}	
		else if (process->CurrentCommand()->event == EVT_UNLOCK)//lock specified by process is in unlocked state
		{
			//PROCESS DOESNT GO HERE
			//we will dequeue if necessary
		}
		else if (process->CurrentCommand()->event == EVT_OUTPUT)//goes to user immediately
		{
			UC->ProcessList->push_back(process);
			process->Status = Running;
		}
		else if (process->CurrentCommand()->event == EVT_END)//process terminates
		{
			process->Status = Terminated;
		}
	}
};

