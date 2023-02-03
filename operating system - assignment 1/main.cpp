#include <iostream>
#include<queue>
#include<string>
#include<vector>
#include <Windows.h>
#include "Process.h"

using namespace std;

int main()
{
	Process p1;

	while (true)
	{
		p1.DoWork();
		Sleep(1000);
		
	}
}

//int main_Print()
//{
//	Process test;
//	test.Print();
//	cout << ToString(CPU) << " " << ToString(SSD) << endl;
//
//	enum Event c = CPU;
//	enum Event s = SSD;
//}