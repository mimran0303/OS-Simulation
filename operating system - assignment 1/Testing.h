#pragma once
#include<vector>
#include "Command.h"

int test_split(string& split)
{
	cout << "--split function testing--" << endl;
	Command* c = new Command();
	vector<string>*sp = c->_Split(split);

	for (auto c : *sp)
	{
		cout << "content of vector: " << c << endl;
	}
	return 0;
}
