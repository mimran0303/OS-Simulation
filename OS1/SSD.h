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
	Process* CurrentProcess = NULL;

public:

	SSD(SSDQueue* queue)
	{
		Queue = queue;
	}

	void DoWork()
	{
		if (CurrentProcess == NULL && Queue->size() >= 1)
		{
			CurrentProcess = Queue->front();
			Queue->pop();
		}

		if (CurrentProcess == NULL)
			return;

		CurrentProcess->DoWork();

		if (CurrentProcess->IsTimerExpired())
		{
			CurrentProcess->Status = Ready;
			CurrentProcess->Report = true;
			CurrentProcess = NULL;
		}
	}
};

