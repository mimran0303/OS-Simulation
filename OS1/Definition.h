#pragma once

#include <queue>
#include "Process.h"

typedef queue<Process*> LockQueue;
typedef queue<Process*> ReadyQueue;
typedef queue<Process*> SSDQueue;
typedef vector<Process*> ProcessVector;

const static int LOCK_COUNT = 2;
