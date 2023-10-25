#include <stdio.h>
#include <conio.h>
#include<string.h>
#include"curses.h"
#include<Windows.h>
#include <time.h>
#define WIDTH 58
#define HIGHT 29

#define Density1 6 //Concentration1
#define Density2 4 //Concentration2
#define Density3 2 //Concentration3

int gameflag = 0;

typedef struct  People {//player
	int x;
	int y;
	int step;
	int Live_Value;
	int score;

	int level;

}people;
typedef struct Fetid_Air {
	int x;
	int y;

}fetid_Air;
typedef struct Robot {//robot
	int x;
	int y;

	fetid_Air fetid_air1[9];
	fetid_Air fetid_air2[25];
	fetid_Air fetid_air3[49];
}robot;
char mdraw[HIGHT][WIDTH];

void deleteAllDrawFetid_Air(robot  mrobot)
{
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == 0 || j == 0 || i == 2 || j == 2)
			{
				if (mrobot.fetid_air1[i * 3 + j].x >= 0 && mrobot.fetid_air1[i * 3 + j].x < WIDTH-1)
					if (mrobot.fetid_air1[i * 3 + j].y >= 0 && mrobot.fetid_air1[i * 3 + j].y < HIGHT-1)
						mdraw[mrobot.fetid_air1[i * 3 + j].y][mrobot.fetid_air1[i * 3 + j].x] = ' ';

			}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (i == 0 || j == 0 || i == 4 || j == 4)
			{
				if (mrobot.fetid_air2[i * 5 + j].x >= 0 && mrobot.fetid_air2[i * 5 + j].x < WIDTH-1)
					if (mrobot.fetid_air2[i * 5 + j].y >= 0 && mrobot.fetid_air2[i * 5 + j].y < HIGHT-1)
						mdraw[mrobot.fetid_air2[i * 5 + j].y][mrobot.fetid_air2[i * 5 + j].x] = ' ';
			}
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			if (i == 0 || j == 0 || i == 6 || j == 6)
			{
				if (mrobot.fetid_air3[i * 7 + j].x >= 0 && mrobot.fetid_air3[i * 7 + j].x < WIDTH-1)
					if (mrobot.fetid_air3[i * 7 + j].y >= 0 && mrobot.fetid_air3[i * 7 + j].y < HIGHT-1)
						mdraw[mrobot.fetid_air3[i * 7 + j].y][mrobot.fetid_air3[i * 7 + j].x] = ' ';
			}

		
}
void DrawAllFetid_Air(robot  mrobot)
{
	
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == 0 || j == 0 || i == 2 || j == 2)
			{
				if (mrobot.fetid_air1[i * 3 + j].x >= 0 && mrobot.fetid_air1[i * 3 + j].x < WIDTH-1)
					if (mrobot.fetid_air1[i * 3+ j].y >= 0 && mrobot.fetid_air1[i * 3+ j].y < HIGHT-1)
						mdraw[mrobot.fetid_air1[i * 3 + j].y][mrobot.fetid_air1[i * 3 + j].x] = '.';

			}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (i == 0 || j == 0 || i == 4 || j == 4)
			{
				if (mrobot.fetid_air2[i * 5 + j].x >= 0 && mrobot.fetid_air2[i * 5 + j].x < WIDTH-1)
					if (mrobot.fetid_air2[i * 5 + j].y >= 0 && mrobot.fetid_air2[i * 5 + j].y < HIGHT-1)
						mdraw[mrobot.fetid_air2[i * 5 + j].y][mrobot.fetid_air2[i * 5 + j].x] = '.';
			}
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			if (i == 0 || j == 0 || i == 6 || j == 6)
			{
				if (mrobot.fetid_air3[i * 7 + j].x >= 0 && mrobot.fetid_air3[i * 7 + j].x < WIDTH-1)
					if (mrobot.fetid_air3[i * 7 + j].y >= 0 && mrobot.fetid_air3[i * 7 + j].y < HIGHT-1)
						mdraw[mrobot.fetid_air3[i * 7 + j].y][mrobot.fetid_air3[i * 7+ j].x] = '.';
			}
}
int changeLive_Value(int x, int y, int livevalue, robot robot)//Vitality
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i != j)
				if (x == robot.fetid_air1[i * 3 + j].x && y == robot.fetid_air1[i * 3 + j].y)
					livevalue -= Density1;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (i == 0 || j == 0)
				if (x == robot.fetid_air2[i * 5 + j].x && y == robot.fetid_air2[i * 5 + j].y)
					livevalue -= Density2;
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			if (i == 0 || j == 0)
				if (x == robot.fetid_air3[i * 7 + j].x && y == robot.fetid_air3[i * 7 + j].y)
					livevalue -= Density3;



	return livevalue;
}
int PeopleMoveCheck(int x, int y)//check player move 
{
	if (x >= WIDTH - 1 &&
		y == HIGHT / 2)
	{

		return 1;

	}
	 if (x >= WIDTH - 1 &&
		y != HIGHT / 2)
	{
		return 0;
	}

	if (x <= 0)
	{
		return 0;

	}


	if (y <= 0)
	{
		return 0;
	}
	if (y >= HIGHT - 1)
	{

		return 0;

	}

	return 2;
}
people PeopleMove(people mpeople)//play move
{
	mvprintw(0,65,"a:left,d:right,w:up,s:down:");
	
	char ch = _getch();

	//scanf("%c", &ch);
	int tmpx = mpeople.x, tmpy = mpeople.y;
	if (ch == 'a')//move to left
	{
		tmpx--;
	}
	else if (ch == 'd')
	{
		tmpx++;
	}
	else if (ch == 'w')
	{
		tmpy--;
	}
	else if (ch == 's')
	{
		tmpy++;
	}
	if (PeopleMoveCheck(tmpx, tmpy) == 2)
	{
		mdraw[mpeople.y][mpeople.x] = ' ';
		mpeople.x = tmpx;
		mpeople.y = tmpy;
		//Fully filled
		mdraw[mpeople.y][mpeople.x] = '*';

		mpeople.step++;
		return mpeople;
	}
	else if (PeopleMoveCheck(tmpx, tmpy) == 1)
	{

		printf("success\n");
		mpeople.level++;

		return mpeople;

	}
	return mpeople;


}
robot initFetid_Air(robot  mrobot)//Initialize smell position
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == 0 || j == 0 || i == 2 || j == 2)
			{
				mrobot.fetid_air1[i * 3 + j].x = mrobot.x - 1 + i;
				mrobot.fetid_air1[i * 3 + j].y = mrobot.y - 1 + j;
			}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (i == 0 || j == 0 || j == 4 || i == 4)
			{
				mrobot.fetid_air2[i * 5 + j].x = mrobot.x - 2 + i;
				mrobot.fetid_air2[i * 5 + j].y = mrobot.y - 2 + j;
			}
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			if (i == 0 || j == 0 || i == 6 || j == 6)
			{
				mrobot.fetid_air3[i * 7 + j].x = mrobot.x - 3 + i;
				mrobot.fetid_air3[i * 7 + j].y = mrobot.y - 3 + j;
			}
	return mrobot;
}
robot RobotMove(robot mrobot)//robot move
{
	int tmpx = mrobot.x, tmpy = mrobot.y;
	//srand((unsigned int)time(NULL));//set random point
	int direction = rand() % 4 + 0;//Generate random values
	if (direction == 0)//up
		tmpy--;
	else if (direction == 1)//left
		tmpx++;
	else if (direction == 2)//down
		tmpy++;
	else if (direction == 3)//right
		tmpx--;
	if (tmpx <= 0)
	{
		return mrobot;

	}

	if (tmpx >= WIDTH - 2)
	{

		return mrobot;

	}
	if (tmpy <= 0)
	{
		return mrobot;
	}
	if (tmpy >= HIGHT - 2)
	{

		return mrobot;

	}
	deleteAllDrawFetid_Air(mrobot);
	mdraw[mrobot.y][mrobot.x] = ' ';
	mrobot.x = tmpx;
	mrobot.y = tmpy;

	mdraw[mrobot.y][mrobot.x] = '#';
	
	mrobot = initFetid_Air(mrobot);
	DrawAllFetid_Air(mrobot);
	return mrobot;
}
robot initrobot()//Initialize robot
{
	robot mrobot;
	//srand((unsigned int)time(NULL));//set random points


	int initnumx = rand() % 57 + 0;
	int initnumy = rand() % 28 + 0;
	mrobot.x = initnumx;
	mrobot.y = initnumy;
	mdraw[mrobot.y][mrobot.x] = '#';
	mrobot = initFetid_Air(mrobot);

	return mrobot;

}
people initpeople(robot* mrobot, int num)//Initialize player
{
	people mpeople;

	int initnumx, initnumy;
	while (1)
	{
		int flg = 0;
		srand((unsigned int)time(NULL));//set random points

		initnumx = rand() % 57 + 0;
		initnumy = rand() % 28 + 0;
		for (int i = 0; i < num; i++)
		{
			if (mrobot[i].x == initnumx && mrobot[i].y == initnumy)
			{
				flg = 1;
				break;
			}
		}
		if (flg == 0)
		{
			mpeople.x = initnumx;
			mpeople.y = initnumy;
			mdraw[mpeople.y][mpeople.x] = '*';
			break;
		}
	}
	mpeople.Live_Value = 100;//blood values
	mpeople.step = initnumx - 58 - abs(initnumy - HIGHT / 2);


	return mpeople;
}
void initDraw()//Initialize
{
	
	for (int i = 0; i < HIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			if (j == WIDTH - 1 && i != HIGHT / 2)
				mdraw[i][j] = '|';
			else if (i == HIGHT - 1)
				mdraw[i][j] = '-';
			else mdraw[i][j] = ' ';
		}
	
}
void Draw()
{
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(4, COLOR_BLACK, COLOR_RED);
	init_pair(6, COLOR_BLACK, COLOR_YELLOW);
	init_pair(16, COLOR_BLACK, COLOR_BLACK);
	
	char  szrobot[3];
	
	//△ □ ●
	//szBuf[0] = (char)0xA1;
	//szBuf[1] = (char)0xF7;
	//szBuf[2] = (char)0xA1;
	//szBufpeople[0] = (char)0xA2;
	szrobot[0] = (char)0xA1;
	szrobot[1] = (char)0xF9;
	szrobot[2] = (char)'\0';
	//szBufpeople[2] = (char)0xA1;
	//szrobot[7] = (char)0xA2;
	
	
	//system("cls");
	//attrset(COLOR_PAIR(5));
	for (int i = 0; i < HIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			
		        if (mdraw[i][j] == '#')//robot
			{
			       attrset(COLOR_PAIR(5));
			      /// mvprintw(i,j,"%s", szrobot);
			      mvprintw(i,j,"%c", mdraw[i][j]);
		               refresh();
			}
			 else  if (mdraw[i][j] == '|')
			{
				attrset(COLOR_PAIR(1));
				mvprintw(i,j,"%c", mdraw[i][j]);
				refresh();
			}
			 else  if (mdraw[i][j] == '-')
			{
				attrset(COLOR_PAIR(1));
				mvprintw(i,j,"%c", mdraw[i][j]);
				refresh();
			}
			 else  if (mdraw[i][j] == '.')
			{
				attrset(COLOR_PAIR(5));
			        mvprintw(i,j,"%c", mdraw[i][j]);
			        refresh();
			}
			else

			{
			   attrset(COLOR_PAIR(16));
			   mvprintw(i,j," ");//b
				refresh();
			}
		}
	  printf("\n");
	}
}

void menuscreen(){
    initscr();
    noecho();
    cbreak();
    
    // get screen size
    int yMax, xMax;
    getmaxyx (stdscr, yMax, xMax); // assigns max values of std screen to yMax and xMax

    // creates window in middle of screen with height 6 and width 48
    WINDOW * menu = newwin(6, 48, (yMax/2) - 3, (xMax/2) - 24);
    box(menu, 0, 0); // puts box around window

    refresh();
    wrefresh(menu);

    //enables arrow keys for window
    keypad(menu, true);

    // array holding menu options
    char choices[3][12] = {"Start Game", "Test", "Exit"};
    int choice;
    int highlight = 0;

    while(1)
    {
        for (int i=0; i<3; i++) //prints menu
        {
            if (i == highlight) //starts highlighting first menu option
                wattron   (menu, A_REVERSE); //enables A_REVERSE for menu window
                mvwprintw (menu, i+1, 1, choices[i]); //prints menu options inside top and left border of menu window
                wattroff  (menu, A_REVERSE); //disables A_REVERSE for window
        }
        choice = wgetch(menu); //assigns integer value of users keypress as int choice

        switch(choice) // processes result of pressing specific keys
        {
            case KEY_UP: //up arrow key pressed  
                highlight--;
                if (highlight == -1) //top of menu    
                    highlight = 0;
                break;
            case KEY_LEFT: //up arrow key pressed  
                highlight--;
                if (highlight == -1) //top of menu    
                    highlight = 0;
                break;

            case KEY_DOWN: //down arrow key pressed
                highlight++;
                if (highlight == 3) //bottom of menu  
                    highlight = 2;
                break;
            case KEY_RIGHT:
                highlight++;
                if (highlight == 3) //bottom of menu  
                    highlight = 2;
                break;

            default: //other key pressed
                break;
        }
        if (choice == 10) //if enter pressed
        {
            printw("Your choice was: %s", choices[highlight]);
            refresh();
            if (highlight == 2){
                endwin();
                return;
            }
            else if (highlight == 0){
                gameflag = 1;
                clear();
                refresh();
                break;
            }
        }
    }
}

void game(){
	if(gameflag==1){
		initscr();
		people mpeople;
		int rscore = 0;
		robot mrobot[58];
		char szpeople[3];
		szpeople[0] = (char)0xA1;
		szpeople[1] = (char)0xF1;
		szpeople[2] = (char)'\0';
			start_color(); //Initialize colour
			
			init_pair(2, COLOR_BLACK, COLOR_RED);
			init_pair(3,COLOR_BLACK, COLOR_YELLOW);
		
		

		for (int i = 1, j = 6; i <= 5; i++, j += 5)
		{

			initDraw();
			srand((unsigned int)time(NULL));//set random point

			for (int w = 0; w < j; w++)
			{
				mrobot[w] = initrobot();
			}
			mpeople = initpeople(mrobot, j);
			mpeople.level = i;
			int flg = 1;
			while (flg)
			{
				
				
				//getch();
				mpeople = PeopleMove(mpeople);
							Draw();
				//attrset(COLOR_PAIR(3));
				attron(COLOR_PAIR(3));
				mvprintw(mpeople.y, mpeople.x, "*");
				for(int w1=0;w1<j;w1++)
				mvprintw(mrobot[w1].y,mrobot[w1].x, "#");
				refresh();
				//getch();
				//attrset(COLOR_PAIR(2));
				attron(COLOR_PAIR(2));
				mvprintw(2,65,"live:%d%\n", mpeople.Live_Value);
				refresh();
				if (mpeople.level > i && mpeople.level <= 5)
				{
					rscore += mpeople.Live_Value - mpeople.step + 10 * i;
					mvprintw(4,65,"Enter to level :%d\n", mpeople.level);
		
					mvprintw(5, 65, "Current score: %d\n", rscore);
					
					getch();
					break;

				}
				if (mpeople.level > i && mpeople.level >= 5)
				{

					mvprintw(6,65,"successful\n");

					mvprintw(7,65,"Total score：%d", rscore);

					getch();
					
					break;

				}
				for (int w = 0; w < j; w++)
				{
					mpeople.Live_Value = changeLive_Value(mpeople.x, mpeople.y, mpeople.Live_Value, mrobot[w]);
					if (mpeople.Live_Value <= 0)
					{
						rscore += mpeople.Live_Value - mpeople.step;
						mvprintw(8, 60, "GAME OVER!\n");
						mvprintw(9, 60, "TOTAL SCORE: %d", rscore);
						mvprintw(10, 60, "To exit the game, please press g; \n");

						mvprintw(11, 60, "To restart the game, press any other key.\n");


						char ch = getch();
						if (ch == 'g')
						{
							exit(0);

						}
						else {
							i = -1;
							j = 0;
							mpeople.score = 0;
						}
						flg = 0;
						break;
					}
					fflush(stdin);
				}
				for (int w = 0; w < j; w++)
				{
					mrobot[w] = RobotMove(mrobot[w]);
					if ((mpeople.x == mrobot[w].x && mpeople.y == mrobot[w].y)|| 
						(mpeople.x == mrobot[w].x && mpeople.y == mrobot[w].y+1)||
						(mpeople.x == mrobot[w].x && mpeople.y == mrobot[w].y-1)||
						(mpeople.x == mrobot[w].x-1 && mpeople.y == mrobot[w].y)||
						(mpeople.x == mrobot[w].x+1 && mpeople.y == mrobot[w].y)||
						(mpeople.x == mrobot[w].x+1 && mpeople.y == mrobot[w].y+1)||
						(mpeople.x == mrobot[w].x-1 && mpeople.y == mrobot[w].y-1)||
						(mpeople.x == mrobot[w].x + 1 && mpeople.y == mrobot[w].y - 1) ||
						(mpeople.x == mrobot[w].x - 1 && mpeople.y == mrobot[w].y + 1) )
					{
						rscore += mpeople.Live_Value - mpeople.step;
						mvprintw(8, 60, "GAME OVER!\n");
						mvprintw(9, 60, "TOTAL SCORE:%d", rscore);
						mvprintw(10, 60, "To exit the game, please press g; \n");

						mvprintw(11, 60, "To restart the game, press any other key.\n");


						char ch = getch();

						if (ch == 'g')
						{
							exit(0);

						}
						else {
							i = -1;
							j = 0;
							mpeople.score = 0;
						}
						flg = 0;
						break;
					}
					fflush(stdin);
				}
				refresh();
				clear();
			}
		}
	}
}

int main() {
	menuscreen();
	game();
	getch();
	endwin();
	return 0;
}