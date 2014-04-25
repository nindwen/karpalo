#include <ncurses.h>
#include "levgen.h"
#include "controls.h"

int main()
{    
	initscr(); /* Start curses mode  */
	curs_set(0); /* Makes the cursor invisible */
	keypad(stdscr, TRUE);
	int lol,x,y=0;
	noecho();

	struct thing heebo;
	heebo.icon="@";
	heebo.x=40;
	heebo.y=4;

	struct thing vihu;
	vihu.icon="Q";
	vihu.x=10;
	vihu.y=10;


	struct tile kartta[100][100];
	levgen(100,kartta);
	int i,j;

	int ch;
	while((ch = getch()) != KEY_F(1))
	 {	

		/*
		for(i=0;i<100;i++)
		{
			for(j=0;j<100;j++)
			{
				mvprintw(j,i,"%s",kartta[j][i].icon);
			}
		}*/

		if(ch== KEY_DOWN)
		{
			movet(&heebo,1,0,100,kartta);
		}
			
		if(ch== KEY_UP)
		{
			movet(&heebo,-1,0,100,kartta);
		}

		if(ch== KEY_RIGHT)
		{
			movet(&heebo,0,1,100,kartta);
		}

		if(ch== KEY_LEFT)
		{
			movet(&heebo,0,-1,100,kartta);
		}

		thinkt(&vihu,100,kartta,&heebo);


		refresh();
	}
	endwin();

	return 0;
}

