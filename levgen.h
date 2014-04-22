#ifndef _LEVGEN
#define _LEVGEN

struct tile
{
	char *icon;
	int solid;
};

int levgen(int size, struct tile level[size][size]);

#endif


