#pragma once

#include "Command.h"
#include "Definition.h"

class Lock
{
private:

	LockQueue* Queue;
	Process* MyProcess = NULL;

public:

	bool isLocked = false;

	Lock(LockQueue* queue)
	{
		Queue = queue;
	}

	void DoWork()
	{
		//if target lock is locked
		// the target lock queue is locked
		// until the lock is unlocked
		//cout << "Lock Status: " << isLocked << endl;
	}
};

