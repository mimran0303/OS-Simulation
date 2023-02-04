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

	while (true)
	{
		p1->DoWork();
		Sleep(1000);
		if (p1->Status == Finish)
			break;
	}

	return 0;
}
