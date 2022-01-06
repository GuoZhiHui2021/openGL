#pragma once
#include <sys/timeb.h>
static time_t getCurMillitm()
{
	struct timeb t;
	ftime(&t);
	return t.time * 1000 + t.millitm;
}
static time_t getCurTime()
{
	struct timeb t;
	ftime(&t);
	return t.time;
}


