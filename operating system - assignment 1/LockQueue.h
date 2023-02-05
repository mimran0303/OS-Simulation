#pragma once
#include<queue>
#include"Process.h"
class LockQueue
{
private:
	queue<Process*>* LockQ = new queue<Process*>();

public:
	void DoWork()
	{
		cout << " LOCK QUEUE DOING WORK " << endl;
	}
};

