#pragma once

#include <iostream>
#include<queue>
#include<string>
#include<vector>
#include "Process.h"

int test_process()
{
	Process* p1 = new Process(0);
	//p1->DoWork();
	while (true)
	{
		p1->DoWork();
		Sleep(1000);
		if (p1->EnumStatus == EVT_LOCK)
		{
			// if ()
			{

			}
		}
		if (p1->EnumStatus == Terminated)
			break;
	}

	return 0;
}
