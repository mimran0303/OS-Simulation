#pragma once

#include "Command.h"

class Lock
{
public:
	bool isLocked = false;

	void DoWork()
	{
		//cout << "Lock Status: " << isLocked << endl;
	}
};

