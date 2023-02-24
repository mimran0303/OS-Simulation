#pragma once

#include "Definition.h"
#include "Command.h"
#include "Process.h"

class CPU
{
private:
	ReadyQueue* Queue;
	

public:
	Process* CurrentProcess = NULL;
	CPU(ReadyQueue* queue)
	{
		Queue = queue;
	}

	void DoWork()
	{
		if (CurrentProcess == NULL && Queue->size() >= 1)
		{
			CurrentProcess = Queue->pop();
			CurrentProcess->Status = Running;
			return;
		}

		if (CurrentProcess == NULL)
			return;
		
		CurrentProcess->DoWork();

		if (CurrentProcess->IsTimerExpired())
		{
			CurrentProcess->Status = Running;
			CurrentProcess->Report = true;
			CurrentProcess = NULL;
		}

		//cout << " CPU DOING WORK " << endl;
	}

	bool ProcessActive()
	{
		if (CurrentProcess == NULL)
			return false;
		else
			return true;
	}
};

