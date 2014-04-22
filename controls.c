#include "controls.h"
#include <ncurses.h>
#include "levgen.h"

int movet(struct thing *t, int y, int x, int ls, struct tile level[ls][ls])
{
	if(!level[t->y+y][t->x+x].solid)
	{
		mvprintw(t->y,t->x,"%s",level[t->y][t->x].icon);
		t->y=t->y+y;
		t->x=t->x+x;
		mvprintw(t->y,t->x,"%s",t->icon); 
	}
}
