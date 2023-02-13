#include <iostream>
#include <string>
#include "Definition.h"
#include "TestEnum.h"
#include "Event.h"
#include "TestProcess.h"
#include "Hardware.h"
#include "OperatingSystem.h"
#include "CPU.h"

using namespace std;

Command* CreateCommand(string& instruct);
void ReportSystemStatus();

Hardware* HW = new Hardware();
OperatingSystem* OS = new OperatingSystem(HW);

int main()
{
	HW->Initialize(OS->SSDQ, OS->LockQ);

#if PRODUCTION
	//
	// Stage 1: Create Processes
	//
	Process* p = NULL;

	while (true)
	{
		string line;
		cout << "enter line" << endl;
		getline(cin, line);
		if (line.empty())
			break;
		Command* cmd = CreateCommand(line);
		
		if (cmd->event == EVT_NCORES)//ncores = # of cpu
		{
			int existingCpuCount = HW->CPUS->size();
			int cpu_amount = cmd->num - existingCpuCount;
			cout << "number of CPUS are" << cpu_amount << endl;

			for (int i = 0;i < cpu_amount;i++)
			{
				CPU* cpu = new CPU(OS->ReadyQ);
				HW->CPUS->push_back(cpu);//not sure how to say push NCORES
			}
			continue;
		}

		if (cmd->event == EVT_START)//this signifies new process but 1st line is always START 
		{
			p = new Process;
			OS->ProcessList->push_back(p);
		}

		p->CommandList->push_back(cmd); //line only work if very first command is START
	}

#else

	CPU* cpu1 = new CPU(OS->ReadyQ);
	CPU* cpu2 = new CPU(OS->ReadyQ);
	HW->CPUS->push_back(cpu1);
	HW->CPUS->push_back(cpu2);

	Process* p = new Process();
	OS->ProcessList->push_back(p);

	p->CommandList->push_back(new Command(EVT_NCORES, 2));
	p->CommandList->push_back(new Command(EVT_START, 5));
	p->CommandList->push_back(new Command(EVT_CPU, 5));
	p->CommandList->push_back(new Command(EVT_LOCK, 0));
	p->CommandList->push_back(new Command(EVT_SSD, 5));
	p->CommandList->push_back(new Command(EVT_OUTPUT, 5));
	p->CommandList->push_back(new Command(EVT_UNLOCK, 0));
	p->CommandList->push_back(new Command(EVT_END));

#endif

	//
	// Stage 2: Orchestration - Do Work in Timer
	//
	while (true)
	{
		OS->DoWork();
		HW->DoWork();
		ReportSystemStatus();
		if (OS->ProcessList->size() == 0)
			break;
		Sleep(1000);
	}
}

Command* CreateCommand(string& instruct) //input originally char instruct[]
{
	vector<string>* result = new vector<string>();
	char* split = strtok(_strdup(instruct.c_str()), " ");
	while (split != NULL)
	{
		cout << split << endl;
		result->push_back(split);
		split = strtok(NULL, " ");
	}
	for (auto element : *result)
	{
		cout << "content of vector: " << element << endl;
	}
	if (result->size() == 1)
	{
		cout << "only 1 item" << endl;
		Command* one = new Command(result->at(0));
		return one;

	}
	else if (result->size() == 2)
	{
		cout << "only 2 items" << endl;
		int time = stoi(result->at(1));
		Command* two = new Command(result->at(0), time);
		return two;
	}
}

void ReportSystemStatus()
{ 
	cout << "---------------" << endl;
	for (int i = 0; i < OS->ProcessList->size(); i++)
	{
		Process* p = OS->ProcessList->at(i);
		cout << "Process - "
			<< "Command: " << ToString(p->CurrentCommand()->event) << ", "
			<< "Status: " << ToString(p->Status) << ", "
			<< "Timer: " << p->Timer << ", "
			<< "Total Time: " << p->TotalTime << ", "
			<< endl;
	}
	cout << "---------------" << endl;
}
