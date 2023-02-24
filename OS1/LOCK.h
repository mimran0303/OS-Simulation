#pragma once

#include "Command.h"
#include "Definition.h"

class Lock
{
private:

	LockQueue* Queue;
	Process* CurrentProcess = NULL;

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
		return (CurrentProcess != NULL);
	}

	bool IsUnLocked()
	{
		return (CurrentProcess == NULL);
	}

	void BringProcessFromQueueAndLockIt()//like ssd DoWord
	{
		CurrentProcess = Queue->front();
		Queue->pop();
		CurrentProcess->Report = true;
	}

	void Unlock()//will be unlocked by process that locked in first place
	{
		if (IsUnLocked())
			return;
		CurrentProcess->Status = Ready;
		CurrentProcess->Report = true;
		CurrentProcess = NULL;
	}
};

