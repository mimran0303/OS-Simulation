
#pragma once

#define TEST_1 0
#define TEST_2 0

#include <iostream>
#include <string>
#include "Definition.h"
#include "TestEnum.h"
#include"QueueTest.h"
#include "Event.h"
#include "Hardware.h"
#include "OperatingSystem.h"
#include "CPU.h"
#if TEST_1

CPU* cpu1 = new CPU(OS->ReadyQ);
CPU* cpu2 = new CPU(OS->ReadyQ);
HW->CPUS->push_back(cpu1);
HW->CPUS->push_back(cpu2);

int pid = 0;

Process* p0 = new Process(pid++);
OS->ProcessList->push_back(p0);
p0->CommandList->push_back(new Command(EVT_START, 10));
p0->CommandList->push_back(new Command(EVT_CPU, 200));
p0->CommandList->push_back(new Command(EVT_SSD, 300));
p0->CommandList->push_back(new Command(EVT_CPU, 250));
p0->CommandList->push_back(new Command(EVT_END)); //760

Process* p1 = new Process(pid++);
OS->ProcessList->push_back(p1);
p1->CommandList->push_back(new Command(EVT_START, 50));
p1->CommandList->push_back(new Command(EVT_CPU, 200));
p1->CommandList->push_back(new Command(EVT_SSD, 300));
p1->CommandList->push_back(new Command(EVT_CPU, 100));
p1->CommandList->push_back(new Command(EVT_END)); //650

#elif TEST_2

CPU* cpu1 = new CPU(OS->ReadyQ);
CPU* cpu2 = new CPU(OS->ReadyQ);
HW->CPUS->push_back(cpu1);
HW->CPUS->push_back(cpu2);

int pid = 0;

Process* p0 = new Process(pid++);
OS->ProcessList->push_back(p0);
p0->CommandList->push_back(new Command(EVT_START, 10));
p0->CommandList->push_back(new Command(EVT_CPU, 200));
p0->CommandList->push_back(new Command(EVT_SSD, 300));
p0->CommandList->push_back(new Command(EVT_CPU, 100));
p0->CommandList->push_back(new Command(EVT_LOCK, 0));
p0->CommandList->push_back(new Command(EVT_CPU, 100));
p0->CommandList->push_back(new Command(EVT_UNLOCK, 0));
p0->CommandList->push_back(new Command(EVT_CPU, 200));
p0->CommandList->push_back(new Command(EVT_END)); //910

Process* p1 = new Process(pid++);
OS->ProcessList->push_back(p1);
p1->CommandList->push_back(new Command(EVT_START, 50));
p1->CommandList->push_back(new Command(EVT_CPU, 200));
p1->CommandList->push_back(new Command(EVT_SSD, 300));
p1->CommandList->push_back(new Command(EVT_CPU, 100));
p1->CommandList->push_back(new Command(EVT_END)); //650

#endif