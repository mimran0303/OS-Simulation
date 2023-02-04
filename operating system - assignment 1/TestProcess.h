#pragma once

#include <iostream>
#include<queue>
#include<string>
#include<vector>
#include <Windows.h>
#include "Process.h"

int test_process()
{
	Process p1;

	while (true)
	{
		p1.DoWork();
		Sleep(1000);

	}
}
