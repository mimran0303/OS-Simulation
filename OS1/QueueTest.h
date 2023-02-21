#pragma once

#include <iostream>
#include<queue>
#include"Process.h"
#include"Command.h"
#include"Hardware.h"
#include<string>
#include<vector>
#include "Process.h"

int test_fqueue()
{
	cout << "Process: ";
	ReadyQueue* Ready = new ReadyQueue();
	for (int i = 0; i < 5; i++)
	{
		Process* p = new Process(i);
		Ready->push(p);
		cout << p->Pid << " ";
	}
	cout << endl;
	
	cout<<"in the ready queue we have "<< Ready->size() << " number of processes" << endl;
	cout << endl;
	cout << "we popped process" << endl;
	cout << endl;
	Ready->pop();
	Ready->pop();
	cout << "in the ready queue we have " << Ready->size() << " number of processes" << endl;
	cout << "Process: ";
	for (int i = 0; i < Ready->size(); i++)
	{
		Process* p = Ready->at(i);
		cout << p->Pid << " ";
	}
	return 0;
}
