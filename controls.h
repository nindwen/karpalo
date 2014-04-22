#ifndef _CONTROLS
#define _CONTROLS

#include "levgen.h"
#include "data.h"

struct thing
{
	char *icon;
	int x;
	int y;
};

int movet(struct thing *t, int y, int x, int ls, struct tile level[ls][ls]);
int thinkt(struct thing *t, int ls, struct tile level[ls][ls],struct thing *heebo);
int setF(struct node *node, struct thing *heebo);

#endif


