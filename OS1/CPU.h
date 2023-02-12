#pragma once

#include "Definition.h"
#include "Command.h"
#include "Process.h"

class CPU
{
private:
	ReadyQueue* Queue;
	Process* MyProcess = NULL;

public:
	CPU(ReadyQueue* queue)
	{
		Queue = queue;
	}

	void DoWork()
	{
		if (MyProcess == NULL && Queue->size() >= 1)
		{
			MyProcess = Queue->front();
			Queue->pop();
			MyProcess->Status = Running;
			return;
		}

		if (MyProcess == NULL)
			return;
		
		if (MyProcess->Status == Running)
		{
			MyProcess->DoWork();
		}

		if (MyProcess->IsTimerExpired())
		{
			MyProcess->Status = Ready;
			MyProcess = NULL;
		}

		//cout << " CPU DOING WORK " << endl;
	}
};

