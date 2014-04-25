#include "controls.h"
#include <ncurses.h>
#include "levgen.h"
#include "data.h"

int movet(struct thing *t, int y, int x, int ls, struct tile level[ls][ls])
{
	if(!level[t->y+y][t->x+x].solid)
	{
		//mvprintw(t->y,t->x,"%s",level[t->y][t->x].icon);
		t->y=t->y+y;
		t->x=t->x+x;
		//mvprintw(t->y,t->x,"%s",t->icon); 
	}
	mvprintw(t->y,t->x,"%s",t->icon);
}

int thinkt(struct thing *t, int ls, struct tile level[ls][ls], struct thing *heebo)
{

	//Add the starting square (or node) to the open list. 

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

	struct node *current;
	current = &nodemap[t->y][t->x];
	listCreat(&open,current);

	current->y=cy;
	current->x=cx;

	current->G=0;
	setF(current,heebo);

	while(1)
	{
		//Look for the lowest F cost square on the open list
		current=listLowest(&open);	
		if(current==NULL)
		{
			break;
		}
		cy=current->y;
		cx=current->x;
		
		int ty,tx;
		int atLeatOneFound=0;

		//Switch it to the closed list. 
		listRemove(&open,current);
		listAdd(&closed,current);

		//For each of the 8 squares adjacent to this current square …
		int i;
		for(i=0;i<4;i++)
		{
			switch(i)
			{
				case 0:
					ty=-1;
					tx=0;
					break;
				case 1:
					ty=1;
					tx=0;
					break;
				case 2:
					ty=0;
					tx=-1;
					break;
				case 3:
					ty=0;
					tx=1;
					break;
			}
			if(cy+ty<=0 || cx+tx <=0) break;
			if(cy+ty>=ls || cx+tx >=ls) break;
			//If it is not walkable or if it is on the closed list, ignore it  
			if(level[cy+ty][cx+tx].solid==0 && !listIsOn(&closed,&nodemap[cy+ty][cx+tx]))
			{
				//If it isn’t on the open list, add it to the open list
				if(!listIsOn(&open,current))
					{
						//Make the current square the parent of this square. . 
						listAdd(&open, &nodemap[cy+ty][cx+tx]);
						nodemap[cy+ty][cx+tx].parent=current;
						nodemap[cy+ty][cx+tx].y=cy+ty;
						nodemap[cy+ty][cx+tx].x=cx+tx;
						
						//Record the F, G, and H costs of the square
						setF(&nodemap[cy+ty][cx+tx],heebo);
						atLeatOneFound=1;
						}
				else
				{
					//If it is on the open list already, check to see if this path to that square is better, using G cost as the measure
					if(nodemap[cy+ty][cx+tx].G < current->G+1)
					{
						//If so, change the parent of the square to the current square, and recalculate the G and F scores of the square
						nodemap[cy+ty][cx+tx].parent=current;
						setF(&nodemap[cy+ty][cx+tx],heebo);
					}
				}
			}
		}

		//Stop when you:

		//Add the target square to the closed list, in which case the path has been found
		if(current->y==heebo->y && current->x==heebo->x)
		{
			break;
		}

		//Fail to find the target square, and the open list is empty. In this case, there is no path.    
		if(!atLeatOneFound && closed.first==NULL)
		{
			break;
		}
	}
	struct node *temp=closed.last;
	int atStart=1;
	while(1)
	{
		//mvprintw(temp->y,temp->x,"x");
		if(temp->parent->parent != NULL )
		{
			if((temp->parent->parent->y==t->y && temp->parent->parent->x==t->x) && atStart)
			{
				return 42;
			}
		}
		if(temp->parent->y==t->y && temp->parent->x==t->x)
		{
			movet(t,temp->y - t->y,temp->x - t->x ,ls,level);
			break;
		}
		atStart=0;
		temp=temp->parent;
	}
}

