#pragma once

#include <iostream>
#include <queue>
#include "UserConsole.h"
#include "Process.h"
#include "Command.h"
#include "Hardware.h"

using namespace std;

class OperatingSystem
{
public: 
	
	Hardware* HW;
	ReadyQueue *ReadyQ;
	SSDQueue *SSDQ;
	LockQueue *LockQ[LOCK_COUNT];
	ProcessVector *ProcessList;
	ProcessVector* DeadProcessList;

	Process* process0;

	OperatingSystem(Hardware* _hw)
	{		
		HW = _hw;
		ProcessList = new ProcessVector;
		DeadProcessList = new ProcessVector;
		ReadyQ = new ReadyQueue();
		SSDQ = new SSDQueue();

		for (int j = 0;j < LOCK_COUNT;j++)
		{
			LockQ[j] = new LockQueue();
		}
	}

	void NewProcessWork()
	{
		for (int i = 0;i < ProcessList->size();i++)
		{
			Process* p = ProcessList->at(i);
			if (p->Status == New)
				p->DoWork();
		}
	}

	void DoWork()
	{
		NewProcessWork();
		RemoveTerminatedProcesses();

		for (int i = 0;i < ProcessList->size();i++)
		{
			Process* p = ProcessList->at(i);
			if (p->IsTimerExpired())
				NextCommand(p);
		}
	}

	void NextCommand(Process* process)
	{
		BeforeNextCommand(process);
		ScheduleNextCommand(process);
		AfterNextCommand(process);
	}

	void BeforeNextCommand(Process* process)
	{
		if (process->CurrentCommand() == NULL)
		{

		}
		else if (process->CurrentCommand()->event == EVT_START)
		{
			// Additional implementation of EVT_START is in main() that creates a new process
			process->Status = Ready;
			
			cout << "Process " << process->Pid << " starts at time " << process->CurrentCommand()->num << " ms" << endl;
			Report();
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

		process->Report = true;

		if (process->CurrentCommand()->event == EVT_START) 
		{
			process->MaxTimer = process->CurrentCommand()->num;
			process->ResetTimer();

			if (DEBUG) cout << "Process: " << process->Pid << ", Started" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_CPU)
		{
			process->MaxTimer = process->CurrentCommand()->num;
			process->ResetTimer();

			ReadyQ->push(process);
			process->Status = Ready;

			if (DEBUG) cout << "Process: " << process->Pid <<", Added to ReadyQ" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_SSD)
		{
			process->MaxTimer = process->CurrentCommand()->num;
			process->ResetTimer();

			SSDQ->push(process);
			process->Status = Blocked;

			if (DEBUG) cout << "Process: " << process->Pid << ", Added to SSDQ" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_LOCK)
		{
			process->MaxTimer = 0;
			process->ResetTimer();
			
			int num = process->CurrentCommand()->num;
			LockQ[num]->push(process);
			process->Status = Blocked; 

			if (DEBUG) cout << "Process: " << process->Pid << ", Acquiered LockQ " << num << endl;
		}	
		else if (process->CurrentCommand()->event == EVT_UNLOCK)
		{
			process->MaxTimer = 0;
			process->ResetTimer();

			int num = process->CurrentCommand()->num;
			HW->Locks[num]->Unlock();
			process->Status = Ready;

			if (DEBUG) cout << "Process: " << process->Pid << ", Released Lock " << num << endl;
		}
		else if (process->CurrentCommand()->event == EVT_OUTPUT)
		{
			process->MaxTimer = process->CurrentCommand()->num;
			process->ResetTimer();

			HW->UC->ProcessList->push_back(process);
			process->Status = Blocked;

			if (DEBUG) cout << "Process: " << process->Pid << ", At UserConsole" << endl;
		}
		else if (process->CurrentCommand()->event == EVT_END)
		{
			process->MaxTimer = process->CurrentCommand()->num;
			process->ResetTimer();

			process->Status = Terminated;
			if (DEBUG) cout << "Process " << process->Pid << " terminates at time " << process->TotalTime << " ms" << endl;
			Report();
		}
	}

	void AfterNextCommand(Process* process)
	{
	}

	void RemoveTerminatedProcesses()
	{
		vector<Process*>* newList = new vector<Process*>();
		for (int i = 0; i < ProcessList->size();i++)
		{
			Process* p = ProcessList->at(i);
			if (p->Status != Terminated)
			{
				newList->push_back(p);
			}
			else
			{
				DeadProcessList->push_back(p);
			}
		}
		delete ProcessList;
		ProcessList = newList;
	}

	void Report()
	{

		if (ReadyQ->size() >= 1)
		{
			int BusyCores = 0;
			for (int i = 0; i < HW->CPUS->size();i++)//count of processes within CPU 
			{
				CPU* cpu = HW->CPUS->at(i);
				if (cpu->ProcessActive())
				{
					BusyCores++;
				}
			}
			cout << "Current number of busy cores: " << BusyCores << endl;
			for (int i = 0;i < ReadyQ->size(); i++)
				cout << "Ready Queue contains process " << ReadyQ->at(i)->Pid << endl;
		}

		if (ReadyQ->empty())
		{
			int BusyCores = 0;
			for (int i = 0; i < HW->CPUS->size();i++)//count of processes within CPU 
			{
				CPU* cpu = HW->CPUS->at(i);
				if (cpu->ProcessActive())
				{
					BusyCores++;
				}
			}
			cout << "Current number of busy cores: " << BusyCores << endl;
			cout << "Ready Queue is empty" << endl;
		}

		cout << "Process Table:" << endl;
		for (auto process : *ProcessList)
		{
			if (process->Status != New)
			{
				cout << "Process " << process->Pid << " " << ToString(process->Status) << endl;
			}
		}
		cout << endl;
	}
};

