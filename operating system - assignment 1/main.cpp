#include <iostream>
#include<string>
#include "TestEnum.h"
#include "TestProcess.h"
#include"Hardware.h"
#include"OperatingSystem.h"
using namespace std;

int main()
{
	OperatingSystem* OpSys = new OperatingSystem();
	// OpSy->;
	Hardware* HW = new Hardware;
	//HW->_Hardware();
	//test_process();
	// test_enum();

	while (true)
	{
		OpSys->DoWork();
		HW->DoWork();
		Sleep(1000);
		cout << "----------------------------" << endl;
		cout << endl;
	}
}

//Example of output when there is only one process:

//EX: when process  starts
//process 0 starts at t=number ms
//current number of busy cores: number
//Ready queue is empty
//process 0 is running

//EX: when process terminates
//process 0 terminated at t=number ms
//Current number of busy cores: 0
//Ready queue is empty
//process 0 is TERMINATED/