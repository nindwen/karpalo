#include <ncurses.h>
#include <stdlib.h>
#include "levgen.h"
#include "controls.h"
#include <time.h>

int main(int argc, char **argv)
{    
	int hardness;
	if(argc==2)
	{
		hardness=atoi(argv[1]);
	}
	else 
	{
		hardness = 4;
	}
	int size = 50; //atoi(getenv("LINES"));

	initscr(); /* Start curses mode  */
	srand (time(NULL));
	curs_set(0); /* Makes the cursor invisible */
	keypad(stdscr, TRUE);
	int lol,x,y=0;
	noecho();


	struct thing heebo;
	heebo.icon="@";
	heebo.x=random()%size;
	heebo.y=random()%size;

	struct thing vihu;
	vihu.icon="Q";
	vihu.x=random()%size;
	vihu.y=random()%size;

	clear();
	mvprintw(0,0,"You are @.\nYou find yourself in a dark, cold dungeon.\nYou have no memory of this place.\nYou sense something evil. Run!");
	mvprintw(heebo.y,heebo.x,"%s",heebo.icon);
	mvprintw(vihu.y,vihu.x,"%s",vihu.icon);
	refresh();
	getch();

	struct tile kartta[size][size];
	levgen(size,kartta, hardness);

	kartta[heebo.y][heebo.x].solid=0;
	movet(&heebo,0,0,size,kartta);

	kartta[vihu.y][vihu.x].solid=0;
	movet(&vihu,0,0,size,kartta);
	int i,j;

	int ch;


	while((ch = getch()) != KEY_F(1))
	 {	

		for(i=0;i<size;i++)
		{
			for(j=0;j<size;j++)
			{
				mvprintw(j,i,"%s",kartta[j][i].icon);
			}
		}

		if(ch== KEY_DOWN)
		{
			movet(&heebo,1,0,size,kartta);
		}
			
		if(ch== KEY_UP)
		{
			movet(&heebo,-1,0,size,kartta);
		}

		if(ch== KEY_RIGHT)
		{
			movet(&heebo,0,1,size,kartta);
		}

		if(ch== KEY_LEFT)
		{
			movet(&heebo,0,-1,size,kartta);
		}

		if(thinkt(&vihu,size,kartta,&heebo)==42 || (vihu.y==heebo.y && vihu.x==heebo.x))
		{
			clear();
			mvprintw(0,0,"The Mysterious Q is currently consuming your soul.\nGame over.");
			refresh();
			getch();
			break;
		}


		refresh();
	}
	endwin();

	return 0;
}

