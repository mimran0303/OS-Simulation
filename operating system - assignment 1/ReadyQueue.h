#pragma once
#include<queue>
#include "Process.h"

class ReadyQueue
{
private:
	queue<Process*>* ReadyQ = new queue<Process*>();

public:
	void DoWork()
	{
		cout << " READY QUEUE DOING WORK " << endl;
	}
};

