#include <iostream>
#include<string>
#include "TestEnum.h"
#include"Event.h"
#include "TestProcess.h"
#include"Hardware.h"
#include"OperatingSystem.h"

using namespace std;

vector<string>* SplitAddToCommand(string& instruct);

int main()
{
	OperatingSystem* os = new OperatingSystem();
	Hardware* hw = new Hardware;
	Process* p = new Process;
	Command* c = new Command;

	
	while (true)
	{
		string line;
		cout << "enter line" << endl;
		getline(cin, line);
		if (line.empty())
		{
			break;
		}
		SplitAddToCommand(line);
	}
}

vector<string>* SplitAddToCommand(string& instruct) //input originally char instruct[]
{
	Process* process = new Process();
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
		//take out element from vector
		Command* one = new Command(result->at(0));
		process->Commands->push_back(one);//add to vector in process.h

	}
	else if (result->size() == 2)
	{
		cout << "only 2 items" << endl;
		int time = stoi(result->at(1));
		Command* two = new Command(result->at(0), time);
		process->Commands->push_back(two);
	}
	return result;
}

