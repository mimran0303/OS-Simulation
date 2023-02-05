#pragma once
#include "Command.h"
#include "SSD.h"
#include "CPU.h"
#include "LOCK.h"
#include "UserConsole.h"


class Hardware
{
public:

	SSD *Ssd;
	CPU *Cpu;
	UserConsole *UC;
	LOCK *lock[4];

	Hardware()
	{
		Ssd = new SSD();
		Cpu = new CPU();
		UC = new UserConsole();

		for (int j = 0;j < 4;j++)
		{
			lock[j] = new LOCK();
		}
	}
	void DoWork()
	{
		cout << " HARDWARE DOING WORK " << endl;
		Ssd->DoWork();
		Cpu->DoWork();
		UC->DoWork();

		for (int j = 0;j < 4;j++)
		{
			lock[j]->DoWork();
		}
	}
};

