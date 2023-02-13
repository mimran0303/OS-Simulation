#pragma once

#include "Definition.h"
#include "Command.h"
#include "SSD.h"
#include "CPU.h"
#include "LOCK.h"
#include "UserConsole.h"

extern const int LOCK_COUNT; //here we say that there are 64 locks (0-63)

typedef vector<CPU*> CPUVector;

class Hardware
{
public:

	CPUVector* CPUS;
	SSD *Ssd;
	UserConsole *UC;
	Lock *Locks[LOCK_COUNT];

	Hardware()
	{
	}

	void Initialize(SSDQueue* SSDQ, LockQueue* lockQs[])
	{
		CPUS = new CPUVector;
		Ssd = new SSD(SSDQ);
		UC = new UserConsole();

		for (int j = 0;j < LOCK_COUNT;j++)
		{
			Locks[j] = new Lock(lockQs[j]);
		}
	}

	void DoWork()
	{
		//cout << "Hardware doing work " << endl;

		for (int i = 0;i < CPUS->size();i++)
		{
			CPU* cpu = CPUS->at(i);
			cpu->DoWork();
		}

		Ssd->DoWork();
		UC->DoWork();

		for (int j = 0;j < LOCK_COUNT;j++) //loop here locates the specified
		{
			Locks[j]->DoWork();
		}
	}
};

