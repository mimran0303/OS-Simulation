#include <iostream>
#include<string>
#include "TestEnum.h"
#include"Event.h"
#include "TestProcess.h"
#include"Hardware.h"
#include"OperatingSystem.h"
#include "Testing.h"

using namespace std;

int main()
{
	OperatingSystem* os = new OperatingSystem();
	Hardware* hw = new Hardware;
	Process* p = new Process;
	Command* c = new Command;

	string test;
	cout << "enter string" << endl;
	getline(cin, test);
	test_split(test);
	

	//while (true)
	//{
	//	string instruction;
	//	getline(cin, instruction);
	//	if (instruction.empty())
	//		break;
	//	cout << "Line: " << instruction << endl;
	//	cout << endl;
	//	Command* inst = new Command(instruction);
	//	//Command* inst = new Command("CPU", 200);
	//	inst->_Split(instruction);
	//}
	//cout << "finished reading input: " << endl;


	//while (true)
	//{
	//	//os->DoWork();
	//	//hw->DoWork();
	//	//Sleep(1000);
	//	//cout << "----------------------------" << endl;
	//}
	
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

Process 0 starts at time 10 ms
Process Table:
Process 0 is READY.

-- Process 0 requests a core at time 10 ms for 200 ms.
-- Process 0 gets a core at time 10 ms.
-- Process 0 will release a core at time 210 ms.
-- Process 0 releases a core at time 210 ms.

-- Process 0 requests lock 0 at time 210 ms.
-- Process 0 gets lock 0 at time 210 ms.

-- Process 0 requests a core at time 210 ms for 100 ms.
-- Process 0 gets a core at time 210 ms.
-- Process 0 will release a core at time 310 ms.
-- Process 0 releases a core at time 310 ms.

-- Process 0 requests SSD access at time 310 ms for 300 ms.
-- Process 0 is granted access to the SSD at time 310 ms.
-- Process 0 will release the SSD at time 610 ms.
-- Process 0 releases the SSD at time 610 ms.

-- Process 0 requests a core at time 610 ms for 100 ms.
-- Process 0 gets a core at time 610 ms.
-- Process 0 will release a core at time 710 ms.
-- Process 0 releases a core at time 710 ms.

-- Process 0 releases lock 0 at time 710 ms.

-- Process 0 requests a core at time 710 ms for 200 ms.
-- Process 0 gets a core at time 710 ms.
-- Process 0 will release a core at time 910 ms.
-- Process 0 releases a core at time 910 ms.

-- Process 0 starts I/O request at time 910 ms for 500 ms.
-- Process 0 will complete its I/O request at time 1410 ms.
-- Process 0 completes its I/O step at time 1410 ms.

-- Process 0 requests a core at time 1410 ms for 100 ms.
-- Process 0 gets a core at time 1410 ms.
-- Process 0 will release a core at time 1510 ms.
-- Process 0 releases a core at time 1510 ms.

Process 0 terminates at time 1510 ms.
Process Table:
Process 0 is TERMINATED.

SUMMARY:
Total elapsed time: 1510 ms

*/