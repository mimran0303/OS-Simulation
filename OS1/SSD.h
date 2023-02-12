#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Definition.h"
#include "Command.h"
#include "Process.h"
#include "Event.h"

class SSD
{
private:

	SSDQueue* Queue;
	Process* MyProcess = NULL;

public:

	SSD(SSDQueue* queue)
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

		cout << " SSD DOING WORK " << endl;

	}
};

