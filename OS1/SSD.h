#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Definition.h"
#include "Command.h"
#include "Process.h"
#include "Event.h"

class SSD
{
private:

	SSDQueue* Queue;

public:

	SSD(SSDQueue* queue)
	{
		Queue = queue;
	}

	void DoWork()
	{
		cout << " SSD DOING WORK " << endl;
	}
};

