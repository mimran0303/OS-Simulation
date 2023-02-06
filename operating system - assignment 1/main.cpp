#include <iostream>
#include<string>
#include "TestEnum.h"
#include"Event.h"
#include "TestProcess.h"
#include"Hardware.h"
#include"OperatingSystem.h"
using namespace std;

int main()
{
	OperatingSystem* os = new OperatingSystem();
	Hardware* hw = new Hardware;
	Process* p = new Process;
	Command* c = new Command;

	string instruction;
	getline(cin, instruction);
	cout << "Line: " << instruction << endl;
	cout << endl;
	Command* inst = new Command(instruction);
	inst->_Split(instruction);



	while (true)
	{
		//os->DoWork();
		//hw->DoWork();
		//Sleep(1000);
		//cout << "----------------------------" << endl;
	}
}

/*	
	----------------
		TESTS
	----------------
	test_process();
	test_enum();
*/

/*	-------------
		NOTES
	--------------

Example of output when there is only one process :

EX: when process  starts
process 0 starts at t=number ms
current number of busy cores: number
Ready queue is empty
process 0 is running

EX: when process terminates
process 0 terminated at t=number ms
Current number of busy cores: 0
Ready queue is empty
process 0 is TERMINATED

*/