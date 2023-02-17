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
	
	Hardware* HW;
	ReadyQueue *ReadyQ;
	SSDQueue *SSDQ;
	LockQueue *LockQ[LOCK_COUNT];
	ProcessVector *ProcessList;

	int cpu_amount=0;

	OperatingSystem(Hardware* _hw)
	{		
		HW = _hw;
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
		//cout << " OS DOING WORK " << endl;

		CleanUp(); //remove terminated processes from process list

		for (int i = 0;i < ProcessList->size();i++)
		{
			Process* p = ProcessList->at(i);

			// If event is start, then wait for number of 
			// sseconds before executing next command
			if (p->CurrentCommand() != NULL && p->CurrentCommand()->event == EVT_START)
			{
				if (!p->IsTimerExpired())
				{
					p->DoWork();
					continue;
				}
				else
				{
					p->Status = Ready;
					// ReportProcessStatus(p, true);
					//p->Report = true;
					// p->Status = Ready;
					//ScheduleNextCommand(p);
				}
			}
			if (p->Status == Ready)
			{
				ScheduleNextCommand(p);
				p->Report = true;
			}
			/*
			if (p->CurrentCommand()->event == EVT_START && p->Status == Blocked)
			{
				if (!p->IsTimerExpired())
					p->DoWork();
				else 
				{
					p->Status = Ready;
					p->Report = true;
				}
			}
			*/
		}
	}

	void ScheduleNextCommand(Process* process)
	{
		process->MoveToNextCommand();		
		if (process->CurrentCommand() == NULL)
		{
			cout << "WARNING: No command to execute" << endl;
			return;
		}

		process->MaxTimer = process->CurrentCommand()->num;
		process->ResetTimer();

#if !PLACEHOLDER_ONLY
		if (process->CurrentCommand()->event == EVT_START) 
		{
			// Additional implementation of EVT_START is in main() that creates a new process
			process->Status = Blocked;
		}
#endif
		else if (process->CurrentCommand()->event == EVT_CPU)//process goes to RQ
		{
			ReadyQ->push(process);
			process->Status = Blocked;
			cout << "Process " << process->Pid <<" added to ReadyQ" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_SSD)//goes to ssd queue IF more than one process trying to acecess SSD
		{
			SSDQ->push(process);
			process->Status = Blocked;
			cout << "Process " << process->Pid << " added to SSDQ" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_LOCK)//lock specified by process is in locked state
		{
			int num = process->CurrentCommand()->num;
			LockQ[num]->push(process);
			process->Status = Blocked; 
			cout << "Process " << process->Pid << " acquiered LockQ " << num << endl;
		}	
		else if (process->CurrentCommand()->event == EVT_UNLOCK)//lock specified by process is in unlocked state
		{
			int num = process->CurrentCommand()->num;
			HW->Locks[num]->Unlock();
			cout << "Process " << process->Pid << " released Lock " << num << endl;
		}
		else if (process->CurrentCommand()->event == EVT_OUTPUT)//goes to user immediately
		{
			HW->UC->ProcessList->push_back(process);
			process->Status = Running;
			cout << "Process " << process->Pid << " at UserConsole" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_END)//process terminates
		{
			process->Status = Terminated;
		}
	}

	void CleanUp()
	{
		vector<Process*>* newList = new vector<Process*>();
		for (int i = 0; i < ProcessList->size();i++)
		{
			Process* p = ProcessList->at(i);
			if (p->Status != Terminated)
			{
				newList->push_back(p);
			}
		}
		delete ProcessList;
		ProcessList = newList;
	}
};

