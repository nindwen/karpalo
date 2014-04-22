#ifndef _CONTROLS
#define _CONTROLS

#include "levgen.h"

struct thing
{
	char *icon;
	int x;
	int y;
};

int movet(struct thing *t, int y, int x, int ls, struct tile level[ls][ls]);

#endif


