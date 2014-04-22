#include "controls.h"
#include <ncurses.h>
#include "levgen.h"
#include "data.h"

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

int thinkt(struct thing *t, int ls, struct tile level[ls][ls], struct thing *heebo)
{
	struct list open;
	open.first=NULL;
	struct list closed;
	closed.first=NULL;
	struct node nodemap[ls][ls];

	int cx,cy;
	cx=t->x;
	cy=t->y;

	struct node *current = &nodemap[t->y][t->x];
	listCreat(&open,current);

	current->y=cy;
	current->x=cx;

	current->G=0;
	setF(current,heebo);

	while(1)
	{
		current=listLowest(&open);	
		cy=current->y;
		cx=current->x;
		
		int ty,tx;
		int atLeatOneFound=0;

		for(ty=-1;ty<2;ty=ty+2)
		{
			for(tx=-1;tx<2;tx=tx+2)
			{
				if(level[ty][tx].solid==0 && !listIsOn(&closed,&nodemap[ty][tx]))
				{
					if(!listIsOn(&open,current))
						{
							listAdd(&open, &nodemap[ty][tx]);
							nodemap[ty][tx].parent=current;
							nodemap[ty][tx].y=ty;
							nodemap[ty][tx].x=tx;

							setF(&nodemap[ty][tx],heebo);
							atLeatOneFound=1;
						}
					else
					{
						if(nodemap[ty][tx].G < current->G+1)
						{
							nodemap[ty][tx].parent=current;
							setF(&nodemap[ty][tx],heebo);
						}
					}
				}
			}
		}


		listRemove(&open,current);
		listAdd(&closed,current);
		if(current->y==heebo->y && current->x==heebo->x)
		{
			break;
		}

		if(!atLeatOneFound)
		{
			break;
		}
	}
	movet(t,t->y-closed.first->next->y, t->x-closed.first->next->x, ls, level);
	
}

