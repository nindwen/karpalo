#include <ncurses.h>
#include "levgen.h"
#include <stdlib.h>

int levgen(int size, struct tile level[size][size])
{

	int i,j;

	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			if(random()%5!=1)
			{
				level[i][j].icon=" ";
				level[i][j].solid=0;
			}
			else
			{
				level[i][j].icon="#";
				level[i][j].solid=1;
			}
		}
	}
	for(i=0;i<100;i++)
	{
		for(j=0;j<100;j++)
		{
			mvprintw(j,i,"%s",level[j][i].icon);
		}
	}
}


