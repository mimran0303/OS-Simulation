#include <iostream>
#include<string>
#include "TestEnum.h"
#include"Event.h"
#include "TestProcess.h"
#include"Hardware.h"
#include"OperatingSystem.h"

using namespace std;

Command* CreateCommand(string& instruct);

int main()
{
	
	Process* p = NULL;
	OperatingSystem* os = new OperatingSystem();
	Hardware* hw = new Hardware();

	//
	// Stage 1: Create Processes
	//
	while (true)
	{
		string line;
		cout << "enter line" << endl;
		getline(cin, line);
		if (line.empty())
			break;
		Command* cmd = CreateCommand(line);

		if (cmd->event == EVT_NCORES)
		{
			for (int i=0;i<cmd->num;i++)
			{
				CPU* cpu = new CPU;
				hw->CPUS->push_back(cpu);//not sure how to say push NCORES
			}
			continue;
		}
		
		if (cmd->event == EVT_START)//this signifies new process but 1st line is always START 
		{
			p = new Process;
			os->ProcessList->push_back(p);
		}

		p->CommandList->push_back(cmd); //line only work if very first command is START
	}

	//
	// Stage 2: Orchestration - Do Work in Timer
	//
	while (true)
	{
		os->DoWork();
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

