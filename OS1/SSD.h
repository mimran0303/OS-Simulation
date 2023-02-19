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
		}

		if (MyProcess == NULL)
			return;

		MyProcess->DoWork();

		if (MyProcess->IsTimerExpired())
		{
			MyProcess->Status = Ready;
			MyProcess->Report = true;
			MyProcess = NULL;
		}
	}
};

