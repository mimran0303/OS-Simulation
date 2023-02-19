#pragma once

#include "Definition.h"
#include "Command.h"
#include "Process.h"

class CPU
{
private:
	ReadyQueue* Queue;
	

public:
	Process* MyProcess = NULL;
	CPU(ReadyQueue* queue)
	{
		Queue = queue;
	}

	void DoWork()
	{
		if (MyProcess == NULL && Queue->size() >= 1)
		{
			MyProcess = Queue->pop();
			MyProcess->Status = Running;
			return;
		}

		if (MyProcess == NULL)
			return;
		
		MyProcess->DoWork();

		if (MyProcess->IsTimerExpired())
		{
			MyProcess->Status = Running;
			MyProcess->Report = true;
			MyProcess = NULL;
		}

		//cout << " CPU DOING WORK " << endl;
	}

	bool ProcessActive()
	{
		if (MyProcess == NULL)
			return false;
		else
			return true;
	}
};

