#pragma once
#include <vector>
#include "Command.h"
#include"Process.h"

class UserConsole
{
public:
	vector<Process*> *ProcessList;

	UserConsole()
	{
		ProcessList = new vector<Process*>();
	}
	void DoWork()
	{
		cout << " USER DOING WORK " << endl;
	}
};

