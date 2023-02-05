#pragma once
#include<queue>
#include"Process.h"

class SSDQueue
{
private:
	queue<Process*>* SSDQ = new queue<Process*>();

public:
	void DoWork()
	{
		cout << " SSD QUEUE DOING WORK " << endl;
	}
};

