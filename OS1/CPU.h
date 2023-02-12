#pragma once

#include "Definition.h"
#include "Command.h"
#include "Process.h"

class CPU
{
private:
	ReadyQueue* Queue;

public:
	CPU(ReadyQueue* queue)
	{
		Queue = queue;
	}

	void DoWork()
	{
		cout << " CPU DOING WORK " << endl;
	}
};

