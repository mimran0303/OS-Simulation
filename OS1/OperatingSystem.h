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

			if (p->CurrentCommand() == NULL)
				BeforeNextCommand(p);
			else if (p->CurrentCommand()->event == EVT_START)
				if (!p->IsTimerExpired())
					p->DoWork();
				else
					BeforeNextCommand(p);
			else if (p->Status == Ready)
				BeforeNextCommand(p);
		}
	}

	void BeforeNextCommand(Process* process)
	{
		if (process->CurrentCommand() == NULL)
		{

		}
		else if (process->CurrentCommand()->event == EVT_START)
		{
			// Additional implementation of EVT_START is in main() that creates a new process
			process->Status = Blocked;
			cout << "Process " << process->Pid << " starts at time " << process->CurrentCommand()->num << " ms" << endl;
			cout << "Process Table" << endl;
			for (int i = 0; i < ProcessList->size();i++)
			{
				cout << "Process " << process->Pid << " " << ToString(process->Status) << endl;
			}
			cout << endl;
		}

		ScheduleNextCommand(process);
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
		process->Report = true;

		//ISSUES:
		//multiple start summary tables because we add process to CPU multiple times
		//status shouldnt be blocked in start summary it should be running or ready
		//status in end summary should be terminated or blocked

		if (process->CurrentCommand()->event == EVT_START) 
		{
			// Additional implementation of EVT_START is in main() that creates a new process
			process->Status = Blocked;
			//cout << "Process: " << process->Pid << ", Started" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_CPU)//process goes to RQ
		{
			ReadyQ->push(process);
			process->Status = Blocked;
			//cout << "Process: " << process->Pid <<", Added to ReadyQ" << endl;
			//Process 0 starts at time 10 ms
#if COMMENTED
				
#endif
		}
		else if (process->CurrentCommand()->event == EVT_SSD)//goes to ssd queue IF more than one process trying to acecess SSD
		{
			SSDQ->push(process);
			process->Status = Blocked;
			//cout << "Process: " << process->Pid << ", Added to SSDQ" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_LOCK)//lock specified by process is in locked state
		{
			int num = process->CurrentCommand()->num;
			LockQ[num]->push(process);
			process->Status = Blocked; 
			//cout << "Process: " << process->Pid << ", Acquiered LockQ " << num << endl;
		}	
		else if (process->CurrentCommand()->event == EVT_UNLOCK)//lock specified by process is in unlocked state
		{
			int num = process->CurrentCommand()->num;
			HW->Locks[num]->Unlock();
			//cout << "Process: " << process->Pid << ", Released Lock " << num << endl;
		}
		else if (process->CurrentCommand()->event == EVT_OUTPUT)//goes to user immediately
		{
			HW->UC->ProcessList->push_back(process);
			process->Status = Running;
			//cout << "Process: " << process->Pid << ", At UserConsole" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_END)//process terminates
		{
			process->Status = Terminated;
			cout << "Process " << process->Pid << " terminates at time " << process->CurrentCommand()->num << " ms" << endl;
			cout << "Process Table" << endl;
			for (int i =0; i < ProcessList->size();i++)
			{
				cout << "Process " << process->Pid << " " << ToString(process->Status) << endl;
			}
			cout << endl;
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

