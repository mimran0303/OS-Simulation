/*
* 
* Student: Mariam Imran
* COSC 3360, Professor Paris
* Due Feb 22, 2023
* 
*/

#include <iostream>
#include <string>
#include "Definition.h"
#include "QueueTest.h"
#include "Event.h"
#include "Hardware.h"
#include "OperatingSystem.h"
#include "CPU.h"
#include "Process.h"

using namespace std;

Command* CreateCommand(string& instruct);
void ReportSystemStatus(OperatingSystem* OS);
char* StringDuplicate(const char* s);

Hardware* HW = new Hardware();
OperatingSystem* OS = new OperatingSystem(HW);

bool IsAlphaNum(string s)
{
	bool result = false;
	for(int i=0; i< s.length(); i++)
	{
		if(isalnum(s.at(i)))
			result = true;
	}
	return result;
}

string names[] = {
"NCORES 1",
"START 1",
"CPU 200",
"SSD 100",
"CPU 200",
"LOCK 1",
"CPU 100",
"UNLOCK 1",
"CPU 100",
"END"
};

int main()
{
	HW->Initialize(OS->SSDQ, OS->LockQ);

	//
	// Stage 1: Create Processes
	//
	Process* p = NULL;
	int pid = 0;

	string line;

	// while (getline(cin, line))
	
	int i = -1;
	while(++i < 10)
	{
		line = names[i];

		if(!IsAlphaNum(line))
			continue;
		
		if(DEBUG) cout << line << endl;

		Command* cmd = CreateCommand(line);
		if (cmd->event == EVT_NCORES)//ncores = # of cpu
		{
			int existingCpuCount = HW->CPUS->size();
			int cpu_amount = cmd->num - existingCpuCount;

			if (DEBUG) cout << "number of CPUS are " << cpu_amount << endl;

			for (int i = 0;i < cpu_amount;i++)
			{
				CPU* cpu = new CPU(OS->ReadyQ);
				HW->CPUS->push_back(cpu);//not sure how to say push NCORES
			}
			continue;
		}

		if (cmd->event == EVT_START)//this signifies new process but 1st line is always START 
		{
			p = new Process(pid++);
			p->SetTimer(cmd->num);
			OS->ProcessList->push_back(p);
		}

		if (p != NULL)
			p->CommandList->push_back(cmd); //line only work if very first command is START
		else
			cout << "Error: No [Start] command defined to create a process " << endl;
	}


	if (DEBUG) cout << "Finished Processing Input. " << endl;

	if (DEBUG) cout << "Starting Operating System....." << endl;

	//
	// Stage 2: Run Commands
	//
	ReportSystemStatus(OS);

	int elapsedtime = 0;

	while (true)
	{
		OS->DoWork();
		HW->DoWork();
		ReportSystemStatus(OS);
		if (OS->ProcessList->size() == 0)
			break;
	}

	cout << "SUMMARY:" << endl;
	//cout << "Total elapsed time : " << elapsedtime << " ms" << endl;

	int TotalProcessRunTime = 0;
	for (int i = 0;i < OS->DeadProcessList->size();i++)
	{
		TotalProcessRunTime = TotalProcessRunTime + OS->DeadProcessList->at(i)->TotalTime;
	}
	cout << "Total Process Run Time time : " << TotalProcessRunTime << " ms" << endl;
}

Command* CreateCommand(string& instruct) //input originally char instruct[]
{
	vector<string>* result = new vector<string>();
	char* split = strtok(StringDuplicate(instruct.c_str()), " ");
	while (split != NULL)
	{
		result->push_back(split);
		split = strtok(NULL, " ");
	}
	if (result->size() == 1)
	{
		Command* one = new Command(result->at(0));
		return one;

	}
	else if (result->size() == 2)
	{
		int time = stoi(result->at(1));
		Command* two = new Command(result->at(0), time);
		return two;
	}
	else
	{
		return NULL;
	}
}

void ReportSystemStatus(OperatingSystem* OS)
{
	for (int i = 0; i < OS->ProcessList->size(); i++)
	{
		Process* p = OS->ProcessList->at(i);
		ReportProcessStatus(p);
	}
}
