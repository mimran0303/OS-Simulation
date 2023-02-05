#pragma once
enum Event
{
	EVENT_START, EVENT_END, EVENT_CPU, EVENT_SSD, EVENT_NCORES, EVENT_LOCK, EVENT_UNLOCK
};

const char* ToString(Event e)
{
	switch (e)
	{
	case EVENT_START:
		return "START";
	case EVENT_END:
		return "END";
	case EVENT_CPU:
		return "CPU";
	case EVENT_SSD:
		return "SSD";
	case EVENT_NCORES:
		return"NCORES";
	case EVENT_LOCK:
		return "LOCK";
	case EVENT_UNLOCK:
		return "UNLOCK";
	}
}
