#pragma once

#include "Command.h"
#include "SSD.h"
#include "CPU.h"
#include "LOCK.h"
#include "UserConsole.h"

const static int LOCK_COUNT = 2;
typedef vector<CPU*> CPUVector;

class Hardware
{
public:

	SSD *Ssd;
	CPU *Cpu;
	UserConsole *UC;
	Lock *Locks[LOCK_COUNT];
	CPUVector *CPUS;

	Hardware()
	{
		CPUS = new CPUVector;
		Ssd = new SSD();
		Cpu = new CPU();
		UC = new UserConsole();

		for (int j = 0;j < LOCK_COUNT;j++)
		{
			Locks[j] = new Lock();
		}
	}

	void DoWork()
	{
		cout << " HARDWARE DOING WORK " << endl;
		Ssd->DoWork();
		Cpu->DoWork();
		UC->DoWork();

		for (int j = 0;j < LOCK_COUNT;j++)
		{
			Locks[j]->DoWork();
		}
		for (int i = 0;i < CPUS->size();i++)
		{
			CPU* cpu = CPUS->at(i);
			cpu->DoWork();
		}
	}
};

