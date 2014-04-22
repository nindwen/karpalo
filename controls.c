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
	open.last=NULL;
	struct list closed;
	closed.first=NULL;
	closed.last=NULL;
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

		listRemove(&open,current);
		listAdd(&closed,current);

		for(ty=-1;ty<2;ty=ty+2)
		{
			for(tx=-1;tx<2;tx=tx+2)
			{
				if(cy+ty<=0 || cx+tx <=0) break;
				if(level[cy+ty][cx+tx].solid==0 && !listIsOn(&closed,&nodemap[cy+ty][cx+tx]))
				{
					if(!listIsOn(&open,current))
						{
							listAdd(&open, &nodemap[cy+ty][cx+tx]);
							nodemap[cy+ty][cx+tx].parent=current;
							nodemap[cy+ty][cx+tx].y=cy+ty;
							nodemap[cy+ty][cx+tx].x=cx+tx;

							setF(&nodemap[cy+ty][cx+tx],heebo);
							atLeatOneFound=1;
						}
					else
					{
						if(nodemap[cy+ty][cx+tx].G < current->G+1)
						{
							nodemap[cy+ty][cx+tx].parent=current;
							setF(&nodemap[cy+ty][cx+tx],heebo);
						}
					}
				}
			}
		}


		if(current->y==heebo->y && current->x==heebo->x)
		{
			break;
		}

		if(!atLeatOneFound)
		{
			break;
		}
	}
	struct node *temp=closed.last;
	while(1)
	{
		if(temp->parent->y==t->y && temp->parent->x==t->x)
		{
			movet(t,temp->y -t->y,temp->x - t->x ,ls, level);
			break;
		}
		temp=temp->parent;
	}
}

