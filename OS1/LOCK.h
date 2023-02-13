#pragma once

#include "Command.h"
#include "Definition.h"

class Lock
{
private:

	LockQueue* Queue;
	Process* MyProcess = NULL;

public:

	Lock(LockQueue* queue)
	{
		Queue = queue;
	}

	void DoWork() //we want this to simply say whether this lock/queue is in an unlocked or locked state
	{
		if (IsLockActive())
			return; //do nothing and leave the method
		else if (!Queue->empty())
			BringProcessFromQueueAndLockIt();

		//cout << "Lock Status: " << IsLockActive() << endl;
	}

	bool IsLockActive()
	{
		return (MyProcess != NULL);
	}

	bool IsUnLocked()
	{
		return (MyProcess == NULL);
	}

	void BringProcessFromQueueAndLockIt()//like ssd DoWord
	{
		MyProcess = Queue->front();
		Queue->pop();
		MyProcess->Status = Ready;
	}

	void Unlock()//will be unlocked by process that locked in first place
	{
		if (IsUnLocked())
			return;
		MyProcess->Status = Ready;
		MyProcess = NULL;
	}
};

