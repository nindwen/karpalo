#include <ncurses.h>
#include "levgen.h"
#include <stdlib.h>

int levgen(int size, struct tile level[size][size], int hardness)
{

	int i,j;

	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			if(random()% hardness != 1)
			{
				level[i][j].icon=" ";
				level[i][j].solid=0;
			}
			else
			{
				level[i][j].icon="#";
				level[i][j].solid=1;
			}
			if((i==0 || j == 0) || (i==size-1 || j==size-1))
			{
				level[i][j].icon="#";
				level[i][j].solid=1;
			}
		}
	}
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			mvprintw(j,i,"%s",level[j][i].icon);
		}
	}
}


