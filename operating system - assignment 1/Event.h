#pragma once

enum Event
{
	EVT_START, EVT_END, EVT_CPU, EVT_SSD, EVT_NCORES, EVT_LOCK, EVT_UNLOCK
};

const char* ToString(Event e)
{
	switch (e)
	{
	case EVT_START:
		return "START";
	case EVT_END:
		return "END";
	case EVT_CPU:
		return "CPU";
	case EVT_SSD:
		return "SSD";
	case EVT_NCORES:
		return"NCORES";
	case EVT_LOCK:
		return "LOCK";
	case EVT_UNLOCK:
		return "UNLOCK";
	}
}
