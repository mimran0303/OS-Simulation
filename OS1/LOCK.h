#pragma once

#include "Command.h"
#include "Definition.h"

class Lock
{
private:

	LockQueue* Queue;

public:

	bool isLocked = false;

	Lock(LockQueue* queue)
	{
		Queue = queue;
	}

	void DoWork()
	{
		//cout << "Lock Status: " << isLocked << endl;
	}
};

