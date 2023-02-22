#pragma once

#include<string.h>
#include <queue>
#include <vector>
#include "Process.h"

using namespace std;

class fqueue
{
private:
	vector<Process*>* data = new vector<Process*>();

public:
	fqueue() {
	}

	void push(Process* p)
	{
		data->push_back(p);
	}

	Process* pop() 
	{
		if (data->size() > 0)
		{
			Process* p = data->at(data->size() - 1);
			data->erase(data->begin());
			return p;
		}
		else 
		{
			return NULL;
		}
	}

	Process* at(int i)
	{
		return data->at(i);
	}

	int size() 
	{
		return data->size();
	}

	bool empty()
	{
		return data->empty();
	}

	~fqueue() {
		delete data;
	}
};

typedef queue<Process*> LockQueue;
typedef fqueue ReadyQueue;
typedef queue<Process*> SSDQueue;
typedef vector<Process*> ProcessVector;

const static int LOCK_COUNT = 2;

int StringCompare(const char* string1, const char* string2)
{
#ifdef WINDOWS
	return _strcmpi(string1, string2);
#else 
	return strcasecmp(string1, string2);
#endif
}
char* StringDuplicate(const char* s)
{
#ifdef WINDOWS
	return _strdup(s);
#else
	return strdup(s);
#endif
}
const static bool DEBUG = false;