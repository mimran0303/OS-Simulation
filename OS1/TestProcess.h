#pragma once

#include <iostream>
#include<queue>
#include<string>
#include<vector>
#include <Windows.h>
#include "Process.h"

int test_process()
{
	Process* p1 = new Process();
	//p1->DoWork();
	while (true)
	{
		p1->DoWork();
		Sleep(1000);
		if (p1->Status == EVT_LOCK)
		{
			// if ()
			{

			}
		}
		if (p1->Status == Terminate)
			break;
	}

	return 0;
}
