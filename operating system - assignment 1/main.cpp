#include <iostream>
#include<queue>
#include<string>
#include<vector>
#include <Windows.h>
#include "Process.h"

using namespace std;
int t = 0;
bool in_use_ssd = false;

void SSD_Work()
{
	//if(in_use_ssd)
}

void Process0()
{
	if (t == 0)
	{
		in_use_ssd = true;
	}
	if (t <= 5)
	{
		cout << "I am here " << t << " seconds" << endl;
	}
	
	if (7 > t && t > 5) //t becomes stuck at 6
	{
		cout << "done!" << endl;
		in_use_ssd = false;
	}
	if (t == 15)
	{
		t = 0;
	}
	t++;

}


int main_timer()
{
	//DoWork();
	while (true)
	{
		Sleep(1000);
		cout << "ssd in use " << in_use_ssd << endl;
		Process0();
	}
}

int main()
{
	Process test;
	test.Print();
	cout << ToString(CPU) << " " << ToString(SSD) << endl;

	enum Event c = CPU;
	enum Event s = SSD;
}