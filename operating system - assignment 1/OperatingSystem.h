#pragma once
#include<iostream>
#include<queue>
#include"Command.h"
#include "ReadyQueue.h"
#include "SSDQueue.h"
#include "LockQueue.h"
using namespace std;

class OperatingSystem
{
public:

	ReadyQueue *ReadyQ;
	SSDQueue *SSDQ;
	LockQueue *LockQ[4];

	OperatingSystem()
	{		
		ReadyQ = new ReadyQueue();
		SSDQ = new SSDQueue();

		for (int j = 0;j < 4;j++)
		{
			LockQ[j] = new LockQueue();
		}
	}

	void DoWork()
	{
		cout << " OS DOING WORK " << endl;
		ReadyQ->DoWork();
		SSDQ->DoWork();

		for (int j = 0;j < 4;j++)
		{
			LockQ[j]->DoWork();
		}
	}
};

