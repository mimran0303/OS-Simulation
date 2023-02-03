#pragma once
enum Event
{
	START, END, CPU, SSD, NCORES, LOCK, UNLOCK
};

const char* ToString(Event e)
{
	switch (e)
	{
	case START:
		return "START";
	case END:
		return "END";
	case CPU:
		return "CPU";
	case SSD:
		return "SSD";
	case NCORES:
		return"NCORES";
	case LOCK:
		return "LOCK";
	case UNLOCK:
		return "UNLOCK";
	}
}
