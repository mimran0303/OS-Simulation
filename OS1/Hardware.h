#pragma once

#include "Definition.h"
#include "Command.h"
#include "SSD.h"
#include "CPU.h"
#include "LOCK.h"
#include "UserConsole.h"
#include "OperatingSystem.h"

extern const int LOCK_COUNT;

typedef vector<CPU*> CPUVector;

class Hardware
{
public:

	CPUVector* CPUS;
	SSD *Ssd;
	UserConsole *UC;
	Lock *Locks[LOCK_COUNT];

	Hardware(OperatingSystem* os)
	{
		CPUS = new CPUVector;
		Ssd = new SSD(os->SSDQ);
		UC = new UserConsole();

		for (int j = 0;j < LOCK_COUNT;j++)
		{
			Locks[j] = new Lock(os->LockQ[j]);
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

		for (int j = 0;j < LOCK_COUNT;j++)
		{
			Locks[j]->DoWork();
		}
	}
};

