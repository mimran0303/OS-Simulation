#pragma once
#include <vector>
#include "Command.h"
#include"Process.h"

class UserConsole
{
public:
	vector<Process*>* ProcessList;

	UserConsole()
	{
		ProcessList = new vector<Process*>();
	}
	void DoWork()
	{
		//cout << " USER CONSOLE DOING WORK " << endl;
		for (int i = 0;i < ProcessList->size();i++)
		{
			Process* p = ProcessList->at(i);
			SingleProcessDoWork(p);
		}

		CleanUp();
	}
	void SingleProcessDoWork(Process* myprocess)
	{
		if (myprocess == NULL)
			return;

		myprocess->DoWork();

		if (myprocess->IsTimerExpired())
		{
			myprocess->Status = Ready;
			myprocess->Report = true;
		}
	}

	void CleanUp()
	{
		vector<Process*>* newList = new vector<Process*>();
		for (int i = 0; i < ProcessList->size();i++)
		{
			Process* p = ProcessList->at(i);
			if (p->Status != Ready)
			{
				newList->push_back(p);
			}
		}

		delete ProcessList;
		ProcessList = newList;
	}
};

