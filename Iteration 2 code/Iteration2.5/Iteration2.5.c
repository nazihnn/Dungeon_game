#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

#include "headers/curses.h"
#include "headers/typedefs.h"
#include "headers/fetidair.h"
#include "headers/characters.h"
#include "headers/startmenu.h"

int limitstep = 150;
clock_t start;
int mcount;

int roomwidth[5] = { 40,80,40,80,58 };
int roomheight[5] = { 20,29,20,29,29 };
enum {
	LEFTROOM,
	UPROOM,
	RIGHTROOM,
	DOWNROOM,
	MIDDELROOM,
	KEEPSTATE,
	PEOPLEMOVE,
	SUCCESS
};

int PeopleMoveCheckAtMiddleRoom(int x, int y, int width, int height)   //check move of player in middle room
{
	if (x >= width - 1 &&
		y == height / 2)
	{
		return RIGHTROOM;
	}
	else if (x <= 0 && y == height / 2)
	{
		return LEFTROOM;
	}
	else if (y <= 0 && x == width / 2)
	{
		return UPROOM;
	}
	else if (y >= height - 1 && x == width / 2)
	{
		return DOWNROOM;
	}
	else if (x >= width - 1 && y != height / 2)
	{
		return KEEPSTATE;
	}
	else if (x <= 0 && y != height / 2)
	{
		return KEEPSTATE;
	}
	else if (y <= 0 && x != width / 2)
	{
		return KEEPSTATE;
	}
	else if (y >= height - 1 && x != width / 2)
	{
		return KEEPSTATE;
	}
	return PEOPLEMOVE;
}
int PeopleMoveCheckAtLeftRoom(int x, int y, int width, int height)   //check move of player in left room
{
	if (x >= width - 1 && y == height / 2)
	{
		return MIDDELROOM;

	}
	else if (x >= width - 1 && y != height / 2)
	{
		return KEEPSTATE;
	}
	else if (x <= 0)
	{
		return KEEPSTATE;
	}
	else if (y <= 0)
	{
		return KEEPSTATE;
	}
	else if (y >= height - 1)
	{
		return KEEPSTATE;
	}
	return PEOPLEMOVE;
}
int PeopleMoveCheckAtRightRoom(int x, int y, int width, int height)
{
	if (x <= 0 && y == height / 2)
	{
		return MIDDELROOM;
	}
	else if (x <= 0 && y != height / 2)
	{
		return KEEPSTATE;
	}
	else if (x >= width - 1)
	{
		return KEEPSTATE;
	}
	else if (y <= 0)
	{
		return KEEPSTATE;
	}
	else if (y >= height - 1)
	{
		return KEEPSTATE;
	}
	return PEOPLEMOVE;
}
int PeopleMoveCheckAtUpRoom(int x, int y, int width, int height)
{
	if (x == width / 2 && y == height - 1)
	{
		return MIDDELROOM;
	}
	else if (x != width / 2 && y >= height - 1)
	{
		return KEEPSTATE;
	}
	else if (x >= width - 1)
	{
		return KEEPSTATE;
	}
	else if (x <= 0)
	{
		return KEEPSTATE;
	}
	else if (y <= 0)
	{
		return KEEPSTATE;
	}
	return PEOPLEMOVE;
}
int PeopleMoveCheckAtDownRoom(int x, int y, int width, int height)
{
	if (x == width / 2 && y == 0)
	{
		return MIDDELROOM;
	}
	else if (x != width / 2 && y <= 0)
	{
		return KEEPSTATE;
	}
	else if (x >= width - 1)
	{
		return KEEPSTATE;
	}
	else if (x <= 0)
	{
		return KEEPSTATE;
	}
	else if (y >= height - 1)
	{
		return KEEPSTATE;
	}
	return PEOPLEMOVE;
}
people PeopleMove(people mpeople, int room)   //player move
{
	char ch = _getch();
	mpeople.step++;
	int tmpx = mpeople.x, tmpy = mpeople.y;
	if (ch == 'a')
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
	else if (ch == 'q')
	{
		exit(0);
	}
	if (room == MIDDELROOM)
	{
		int n = PeopleMoveCheckAtMiddleRoom(tmpx, tmpy, roomwidth[MIDDELROOM], roomheight[MIDDELROOM]);
		if (n == PEOPLEMOVE)
		{
			mdraw[mpeople.y][mpeople.x] = ' ';
			mpeople.x = tmpx;
			mpeople.y = tmpy;
			mdraw[mpeople.y][mpeople.x] = '*';
			return mpeople;
		}
		else if (n == KEEPSTATE)
		{
			return mpeople;
		}
		else if (n < MIDDELROOM)
		{
			mdraw[mpeople.y][mpeople.x] = ' ';
			mpeople.x = tmpx;
			mpeople.y = tmpy;
			mdraw[mpeople.y][mpeople.x] = '*';
			mpeople.nowroom = n;
			return mpeople;
		}
	}
	else if (room == LEFTROOM)
	{
		int n = PeopleMoveCheckAtLeftRoom(tmpx, tmpy, roomwidth[LEFTROOM], roomheight[LEFTROOM]);
		if (n == PEOPLEMOVE)
		{
			mdraw[mpeople.y][mpeople.x] = ' ';
			mpeople.x = tmpx;
			mpeople.y = tmpy;
			mdraw[mpeople.y][mpeople.x] = '*';
			return mpeople;
		}
		else if (n == KEEPSTATE)
		{
			return mpeople;
		}
		else
		{
			mpeople.nowroom = n;
			return mpeople;
		}
	}
	else if (room == RIGHTROOM)
	{
		int n = PeopleMoveCheckAtRightRoom(tmpx, tmpy, roomwidth[RIGHTROOM], roomheight[RIGHTROOM]);
		if (n == PEOPLEMOVE)
		{
			mdraw[mpeople.y][mpeople.x] = ' ';
			mpeople.x = tmpx;
			mpeople.y = tmpy;
			mdraw[mpeople.y][mpeople.x] = '*';
			return mpeople;
		}
		else if (n == KEEPSTATE)
		{
			return mpeople;
		}
		else
		{
			mpeople.nowroom = n;
			return mpeople;
		}
	}
	else if (room == UPROOM)
	{
		int n = PeopleMoveCheckAtUpRoom(tmpx, tmpy, roomwidth[UPROOM], roomheight[UPROOM]);
		if (n == PEOPLEMOVE)
		{
			mdraw[mpeople.y][mpeople.x] = ' ';
			mpeople.x = tmpx;
			mpeople.y = tmpy;
			mdraw[mpeople.y][mpeople.x] = '*';
			return mpeople;
		}
		else if (n == KEEPSTATE)
		{
			return mpeople;
		}
		else
		{
			mpeople.nowroom = n;
			return mpeople;
		}
	}
	else if (room == DOWNROOM)
	{
		int n = PeopleMoveCheckAtDownRoom(tmpx, tmpy, roomwidth[DOWNROOM], roomheight[DOWNROOM]);
		if (n == PEOPLEMOVE)
		{
			mdraw[mpeople.y][mpeople.x] = ' ';
			mpeople.x = tmpx;
			mpeople.y = tmpy;
			mdraw[mpeople.y][mpeople.x] = '*';
			return mpeople;
		}
		else if (n == KEEPSTATE)
		{
			return mpeople;
		}
		else
		{
			mpeople.nowroom = n;
			return mpeople;
		}
	}
	return mpeople;
}
robot initFetid_Air(robot  mrobot)   //Initialize smell position
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
robot RobotMove(robot mrobot, int width, int height)	//robot move after player movement
{
	int tmpx = mrobot.x, tmpy = mrobot.y;//set random point
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
	if (tmpx >= width - 2)
	{
		return mrobot;
	}
	if (tmpy <= 0)
	{
		return mrobot;
	}
	if (tmpy >= height - 2)
	{
		return mrobot;
	}
	deleteAllDrawFetid_Air(mrobot, width, height);
	mdraw[mrobot.y][mrobot.x] = ' ';
	mrobot.x = tmpx;
	mrobot.y = tmpy;
	mdraw[mrobot.y][mrobot.x] = '#';
	mrobot = initFetid_Air(mrobot);
	DrawAllFetid_Air(mrobot, width, height);
	return mrobot;
}
robot initrobot(int width, int height)		//Initialize robot psoition when starting a new game
{
	robot mrobot;
	int initnumx, initnumy;
	while (1)
	{
		int flg = 0;
		initnumx = rand() % (width - 1) + 1;
		initnumy = rand() % (height - 1) + 1;
		if (initnumx == width - 1 || initnumx == 0 || initnumy == height - 1 || initnumy == 0)
			flg = 1;
		if (flg == 0)
		{
			mrobot.x = initnumx;
			mrobot.y = initnumy;
			mdraw[mrobot.y][mrobot.x] = '#';
			break;
		}
	}
	mrobot = initFetid_Air(mrobot);
	return mrobot;
}
people initpeople(robot* mrobot, int num, int width, int height)    //Initialize player posiotion when starting a new game
{
	people mpeople;
	int initnumx, initnumy;
	while (1)
	{
		int flg = 0;
		srand((unsigned int)time(NULL));
		initnumx = rand() % (width - 5) + 5;
		initnumy = rand() % (height - 5) + 5;
		for (int i = 0; i < num; i++)
		{
			if (mrobot[i].x == initnumx && mrobot[i].y == initnumy)
			{
				flg = 1;
				break;
			}
		}
		if (initnumx == width - 1 || initnumx == 0 || initnumy == height - 1 || initnumy == 0)
			flg = 1;
		if (flg == 0)
		{
			mpeople.x = initnumx;
			mpeople.y = initnumy;
			mdraw[mpeople.y][mpeople.x] = '*';
			break;
		}
	}
	mpeople.Live_Value = 100;   //blood value
	mpeople.step = 0;
	mpeople.nowroom = MIDDELROOM;
	return mpeople;
}
people changepeople(people mpeople, int preroomid)	//Initialize player position when moving form a room to another
{
	if (preroomid == LEFTROOM && mpeople.nowroom == MIDDELROOM)
	{
		mpeople.x = 1;
		mpeople.y = roomheight[mpeople.nowroom] / 2;
		return mpeople;
	}
	else if (preroomid == RIGHTROOM && mpeople.nowroom == MIDDELROOM)
	{
		mpeople.x = roomwidth[mpeople.nowroom] - 2;
		mpeople.y = roomheight[mpeople.nowroom] / 2;
		return mpeople;
	}
	else if (preroomid == UPROOM && mpeople.nowroom == MIDDELROOM)
	{
		mpeople.x = roomwidth[mpeople.nowroom] / 2;
		mpeople.y = 1;
		return mpeople;
	}
	else if (preroomid == DOWNROOM && mpeople.nowroom == MIDDELROOM)
	{
		mpeople.x = roomwidth[mpeople.nowroom] / 2;
		mpeople.y = roomheight[mpeople.nowroom] - 2;
		return mpeople;
	}
	if (preroomid == MIDDELROOM && mpeople.nowroom == LEFTROOM)
	{
		mpeople.x = roomwidth[mpeople.nowroom] - 2;
		mpeople.y = roomheight[mpeople.nowroom] / 2;
		return mpeople;
	}
	else if (preroomid == MIDDELROOM && mpeople.nowroom == RIGHTROOM)
	{
		mpeople.x = 1;
		mpeople.y = roomheight[mpeople.nowroom] / 2;
		return mpeople;
	}
	else if (preroomid == MIDDELROOM && mpeople.nowroom == UPROOM)
	{
		mpeople.x = roomwidth[mpeople.nowroom] / 2;
		mpeople.y = roomheight[mpeople.nowroom] - 2;
		return mpeople;
	}
	else if (preroomid == MIDDELROOM && mpeople.nowroom == DOWNROOM)
	{
		mpeople.x = roomwidth[mpeople.nowroom] / 2;
		mpeople.y = 1;
		return mpeople;
	}
	clear();
	return mpeople;
}
void initDraw(int width, int height, int roomid)	//Initialize wall
{
	if (roomid == LEFTROOM)
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				if (j == width - 1 && i != height / 2)
					mdraw[i][j] = '|';
				else if (j == 0)
					mdraw[i][j] = '|';
				else if (i == height - 1)
					mdraw[i][j] = '-';
				else if (i == 0)
					mdraw[i][j] = '-';
				else mdraw[i][j] = ' ';
			}
	}
	else if (roomid == RIGHTROOM)
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				if (j == 0 && i != height / 2)
					mdraw[i][j] = '|';
				else if (j == width - 1)
					mdraw[i][j] = '|';
				else if (i == height - 1)
					mdraw[i][j] = '-';
				else if (i == 0)
					mdraw[i][j] = '-';
				else mdraw[i][j] = ' ';
			}
	}
	else if (roomid == UPROOM)
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				if (i == height - 1 && j != width / 2)
					mdraw[i][j] = '-';
				else if (j == 0)
					mdraw[i][j] = '|';
				else if (j == width - 1)
					mdraw[i][j] = '|';
				else if (i == 0)
					mdraw[i][j] = '-';
				else mdraw[i][j] = ' ';
			}
	}
	else if (roomid == DOWNROOM)
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				if (i == 0 && j != width / 2)
					mdraw[i][j] = '-';
				else if (j == 0)
					mdraw[i][j] = '|';
				else if (j == width - 1)
					mdraw[i][j] = '|';
				else if (i == height - 1)
					mdraw[i][j] = '-';
				else mdraw[i][j] = ' ';
			}
	}
	else if (roomid == MIDDELROOM)
	{
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				if (i == 0 && j != width / 2)
					mdraw[i][j] = '-';
				else if (j == 0 && i != height / 2)
					mdraw[i][j] = '|';
				else if (i == height - 1 && j != width / 2)
					mdraw[i][j] = '-';
				else if (j == width - 1 && i != height / 2)
					mdraw[i][j] = '|';
				else mdraw[i][j] = ' ';
			}
	}
}

void explorer_mode()
{
	people playpeople;
	int rscore = 0;
	robot mrobot[58];
	start_color();
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	int successdoor[2] = { 0,0 };
	int roomid = MIDDELROOM;
	for (int i = 1, j = 6; i <= 5; i++, j += 3)
	{
		initDraw(roomwidth[roomid], roomheight[roomid], roomid);
		srand((unsigned int)time(NULL));
		for (int w = 0; w < j; w++)
		{
			mrobot[w] = initrobot(roomwidth[roomid], roomheight[roomid]);
		}
		playpeople = initpeople(mrobot, j, roomwidth[roomid], roomheight[roomid]);
		playpeople.level = i;
		int flg = 1;
		int sroomid = rand() % 4 + 0;     //number of room have exit door
		int sdirect = rand() % 3 + 0;     //position of exit door
		if (sroomid == LEFTROOM)
		{
			if (sdirect == 0)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = roomheight[sroomid] - 1;
			}
			else if (sdirect == 1)
			{
				successdoor[0] = 0;
				successdoor[1] = roomheight[sroomid] / 2;
			}
			else if (sdirect == 2)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = 0;
			}
		}
		else if (sroomid == UPROOM)
		{
			if (sdirect == 1)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = 0;
			}
			else if (sdirect == 0)
			{
				successdoor[0] = 0;
				successdoor[1] = roomheight[sroomid] / 2;
			}
			else if (sdirect == 2)
			{
				successdoor[0] = roomwidth[sroomid] - 1;
				successdoor[1] = roomheight[sroomid] / 2;
			}
		}
		else if (sroomid == RIGHTROOM)
		{
			if (sdirect == 0)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = 0;
			}
			else if (sdirect == 1)
			{
				successdoor[0] = roomwidth[sroomid] - 1;
				successdoor[1] = roomheight[sroomid] / 2;
			}
			else if (sdirect == 2)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = roomheight[sroomid] - 1;
			}
		}
		else if (sroomid == DOWNROOM)
		{
			if (sdirect == 2)
			{
				successdoor[0] = 0;
				successdoor[1] = roomheight[sroomid] / 2;
			}
			else if (sdirect == 0)
			{
				successdoor[0] = roomwidth[sroomid] - 1;
				successdoor[1] = roomheight[sroomid] / 2;
			}
			else if (sdirect == 1)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = roomheight[sroomid] - 1;
			}
		}
		while (flg)
		{
			Characters_E(roomwidth[roomid], roomheight[roomid], playpeople.x, playpeople.y);
			attron(COLOR_PAIR(3));
			mvprintw(playpeople.y, playpeople.x, "*");
			mvprintw(14, 80, "Level:%d ", i);
			mvprintw(13, 80, "Step:%d ", playpeople.step);
			mvprintw(0, 80,"Operating Instructions:a:left  d:right");
                        mvprintw(1,103,"w:up    s:down");
			if (((playpeople.x == successdoor[0] - 1) || (playpeople.x == successdoor[0]) || (playpeople.x == successdoor[0] + 1)) &&
				((playpeople.y == successdoor[1] - 1) || (playpeople.y == successdoor[1] + 1) ||
					(playpeople.y == successdoor[1])) && playpeople.nowroom == sroomid)
			{
				if (playpeople.level >= i && playpeople.level <= 5)
				{
					rscore += playpeople.Live_Value - playpeople.step + 100 * i;
					mvprintw(4, 80, "Enter to level: %d\n", playpeople.level);
					mvprintw(5, 80, "Score: %d\n", rscore);
					playpeople.level++;
					playpeople.step = 0;
					roomid = MIDDELROOM;
					clear();
					break;
				}
				if (playpeople.level >= 5)
				{
					mvprintw(6, 40, "Successful");
					mvprintw(7, 40, "Score:%d", rscore);
					getch();
					flg = 0;
					clear();
					return;
				}
			}
			else if (roomid != playpeople.nowroom)
			{
				playpeople = changepeople(playpeople, roomid);
				roomid = playpeople.nowroom;
				initDraw(roomwidth[roomid], roomheight[roomid], roomid);
				for (int w = 0; w < j; w++)
				{
					mrobot[w] = initrobot(roomwidth[roomid], roomheight[roomid]);
				}
			}

			if (roomid == sroomid)
				if (successdoor[0] < playpeople.x + 10 && playpeople.x - 10 < successdoor[0] &&
					successdoor[1] < playpeople.y + 10 && playpeople.y - 10 < successdoor[1])
				{
					mvprintw(successdoor[1], successdoor[0], " ");
				}
			refresh();
			attron(COLOR_PAIR(2));
			for (int w = 0; w < j; w++)
			{
				playpeople.Live_Value = changeLive_Value(playpeople.x, playpeople.y, playpeople.Live_Value, mrobot[w]);
				attron(COLOR_PAIR(2));
				mvprintw(2, 80, "Blood: %d%\n", playpeople.Live_Value);
				refresh();
				if (playpeople.Live_Value <= 0 || playpeople.step >= limitstep + i * 100)
				{
					rscore += playpeople.Live_Value;
					clear();
					mvprintw(8, 40, "GAME OVER!\n");
					mvprintw(9, 40, "SCORE: %d", rscore);
					mvprintw(10, 40, "To exit game, please press g; \n");
					mvprintw(11, 40, "To restart game, press any other keys.\n");
					roomid = MIDDELROOM;
					mcount = 0;
					char ch = getch();
					if (ch == 'g')
					{
						exit(0);
					}
					else {
						i = -1;
						j = 0;
						playpeople.score = 0;
						clear();
						return;
					}
					flg = 0;
					break;
				}
				fflush(stdin);
			}
			playpeople = PeopleMove(playpeople, roomid);
			for (int w = 0; w < j; w++)
			{
				mrobot[w] = RobotMove(mrobot[w], roomwidth[roomid], roomheight[roomid]);
				if ((playpeople.x == mrobot[w].x && playpeople.y == mrobot[w].y) ||
					(playpeople.x == mrobot[w].x && playpeople.y == mrobot[w].y + 1) ||
					(playpeople.x == mrobot[w].x && playpeople.y == mrobot[w].y - 1) ||
					(playpeople.x == mrobot[w].x - 1 && playpeople.y == mrobot[w].y) ||
					(playpeople.x == mrobot[w].x + 1 && playpeople.y == mrobot[w].y) ||
					(playpeople.x == mrobot[w].x + 1 && playpeople.y == mrobot[w].y + 1) ||
					(playpeople.x == mrobot[w].x - 1 && playpeople.y == mrobot[w].y - 1) ||
					(playpeople.x == mrobot[w].x + 1 && playpeople.y == mrobot[w].y - 1) ||
					(playpeople.x == mrobot[w].x - 1 && playpeople.y == mrobot[w].y + 1))
				{
					rscore += playpeople.Live_Value - playpeople.step;
					clear();
					mvprintw(8, 40, "GAME OVER!\n");
					mvprintw(9, 40, "SCORE: %d", rscore);
					mvprintw(10, 40, "To exit game, please press g; \n");
					mvprintw(11, 40, "To restart game, press any other keys.\n");
					roomid = MIDDELROOM;
					mcount = 0;
					char ch = getch();
					if (ch == 'g')
					{
						exit(0);
					}
					else {
						i = -1;
						j = 0;
						playpeople.score = 0;
						clear();
						return;
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
	getch();
	endwin();
}
void Normal_mode()
{
	people playpeople;
	int rscore = 0;
	robot mrobot[58];
	start_color();
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	int successdoor[2] = { 0,0 };
	int roomid = MIDDELROOM;
	for (int i = 1, j = 6; i <= 5; i++, j += 3)
	{
		initDraw(roomwidth[roomid], roomheight[roomid], roomid);
		srand((unsigned int)time(NULL));
		for (int w = 0; w < j; w++)
		{
			mrobot[w] = initrobot(roomwidth[roomid], roomheight[roomid]);
		}
		playpeople = initpeople(mrobot, j, roomwidth[roomid], roomheight[roomid]);
		playpeople.level = i;
		int flg = 1;
		int sroomid = rand() % 4 + 0;     //number of room have exit room
		int sdirect = rand() % 3 + 0;     //position of exit door
		if (sroomid == LEFTROOM)
		{
			if (sdirect == 0)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = roomheight[sroomid] - 1;
			}
			else if (sdirect == 1)
			{
				successdoor[0] = 0;
				successdoor[1] = roomheight[sroomid] / 2;
			}
			else if (sdirect == 2)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = 0;
			}
		}
		else if (sroomid == UPROOM)
		{
			if (sdirect == 1)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = 0;
			}
			else if (sdirect == 0)
			{
				successdoor[0] = 0;
				successdoor[1] = roomheight[sroomid] / 2;
			}
			else if (sdirect == 2)
			{
				successdoor[0] = roomwidth[sroomid] - 1;
				successdoor[1] = roomheight[sroomid] / 2;
			}
		}
		else if (sroomid == RIGHTROOM)
		{
			if (sdirect == 0)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = 0;
			}
			else if (sdirect == 1)
			{
				successdoor[0] = roomwidth[sroomid] - 1;
				successdoor[1] = roomheight[sroomid] / 2;
			}
			else if (sdirect == 2)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = roomheight[sroomid] - 1;
			}
		}
		else if (sroomid == DOWNROOM)
		{
			if (sdirect == 2)
			{
				successdoor[0] = 0;
				successdoor[1] = roomheight[sroomid] / 2;
			}
			else if (sdirect == 0)
			{
				successdoor[0] = roomwidth[sroomid] - 1;
				successdoor[1] = roomheight[sroomid] / 2;
			}
			else if (sdirect == 1)
			{
				successdoor[0] = roomwidth[sroomid] / 2;
				successdoor[1] = roomheight[sroomid] - 1;
			}
		}
		while (flg)
		{
			Characters_N(roomwidth[roomid], roomheight[roomid], playpeople.x, playpeople.y);
			attron(COLOR_PAIR(3));
			mvprintw(playpeople.y, playpeople.x, "*");
			mvprintw(14, 80, "Level:%d ", i);
			mvprintw(13, 80, "Step:%d ", playpeople.step);
			mvprintw(0, 80, "a:left,d:right,w:up,s:down:");
			if (((playpeople.x == successdoor[0] - 1) || (playpeople.x == successdoor[0]) || (playpeople.x == successdoor[0] + 1)) &&
				((playpeople.y == successdoor[1] - 1) || (playpeople.y == successdoor[1] + 1) ||
					(playpeople.y == successdoor[1])) && playpeople.nowroom == sroomid)
			{
				if (playpeople.level >= i && playpeople.level <= 5)
				{
					rscore += playpeople.Live_Value + 10 * i;
					mvprintw(4, 80, "Enter to level: %d", playpeople.level);
					mvprintw(5, 80, "Score: %d", rscore);
					playpeople.level++;
					playpeople.step = 0;
					roomid = MIDDELROOM;
					clear();
					break;
				}
				if (playpeople.level >= 5)
				{
					mvprintw(6, 40, "Successful!");
					mvprintw(7, 40, "Score:%d", rscore);
					getch();
					flg = 0;
					clear();
					return;
				}
			}
			else if (roomid != playpeople.nowroom)
			{
				playpeople = changepeople(playpeople, roomid);
				roomid = playpeople.nowroom;
				initDraw(roomwidth[roomid], roomheight[roomid], roomid);
				for (int w = 0; w < j; w++)
				{
					mrobot[w] = initrobot(roomwidth[roomid], roomheight[roomid]);
				}
			}
			if (roomid == sroomid)
			{
				mvprintw(successdoor[1], successdoor[0], " ");
			}
			refresh();
			attron(COLOR_PAIR(2));
			for (int w = 0; w < j; w++)
			{
				playpeople.Live_Value = changeLive_Value(playpeople.x, playpeople.y, playpeople.Live_Value, mrobot[w]);
				attron(COLOR_PAIR(2));
				mvprintw(2, 80, "Blood: %d%\n", playpeople.Live_Value);
				refresh();
				if (playpeople.Live_Value <= 0 || playpeople.step >= limitstep + i * 50)
				{
					rscore += playpeople.Live_Value - playpeople.step;
					clear();
					mvprintw(8, 40, "GAME OVER!\n");
					mvprintw(9, 40, "SCORE: %d", rscore);
					mvprintw(10, 40, "To exit game, please press g; \n");
					mvprintw(11, 40, "To restart game, press any other keys.\n");
					roomid = MIDDELROOM;
					char ch = getch();
					if (ch == 'g')
					{
						exit(0);
					}
					else {
						i = -1;
						j = 0;
						playpeople.score = 0;
						clear();
						return;
					}
					flg = 0;
					break;
				}
				fflush(stdin);
			}
			playpeople = PeopleMove(playpeople, roomid);
			for (int w = 0; w < j; w++)
			{
				mrobot[w] = RobotMove(mrobot[w], roomwidth[roomid], roomheight[roomid]);
				if ((playpeople.x == mrobot[w].x && playpeople.y == mrobot[w].y) ||
					(playpeople.x == mrobot[w].x && playpeople.y == mrobot[w].y + 1) ||
					(playpeople.x == mrobot[w].x && playpeople.y == mrobot[w].y - 1) ||
					(playpeople.x == mrobot[w].x - 1 && playpeople.y == mrobot[w].y) ||
					(playpeople.x == mrobot[w].x + 1 && playpeople.y == mrobot[w].y) ||
					(playpeople.x == mrobot[w].x + 1 && playpeople.y == mrobot[w].y + 1) ||
					(playpeople.x == mrobot[w].x - 1 && playpeople.y == mrobot[w].y - 1) ||
					(playpeople.x == mrobot[w].x + 1 && playpeople.y == mrobot[w].y - 1) ||
					(playpeople.x == mrobot[w].x - 1 && playpeople.y == mrobot[w].y + 1))
				{
					rscore += playpeople.Live_Value - playpeople.step;
					clear();
					mvprintw(8, 40, "GAME OVER!\n");
					mvprintw(9, 40, "SCORE: %d", rscore);
					mvprintw(10, 40, "To exit game, please press g; \n");
					mvprintw(11, 40, "To restart game, press any other keys.\n");
					roomid = MIDDELROOM;
					char ch = getch();
					if (ch == 'g')
					{
						exit(0);
					}
					else {
						i = -1;
						j = 0;
						playpeople.score = 0;
						clear();
						return;
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
	getch();
	endwin();
}

int main() {
        int mode = 1;
	char key1;
	char key;
	initscr();
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	start_color();
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	menu();
	refresh();
	attron(COLOR_PAIR(2));
	mvprintw((yMax / 2 - 12) + 9, (xMax / 2) - 7, "Exit game!");
	refresh();
	attron(COLOR_PAIR(1));
	mvprintw((yMax / 2 - 12) + 10, (xMax / 2) - 7, "Explorer mode!");
	mvprintw((yMax / 2 - 12) + 11, (xMax / 2) - 7, "Normal mode!");
	refresh();
	while (1)
	{
		key1 = _getch();
		key = _getch();
		{
			if (key == 72)
			{
				mode--;
				if (mode < 1)mode = 3;
			}
			else if (key == 80)
			{
				mode++;
				if (mode > 3)
					mode = 1;
			}
		}
		if (mode == 1)
		{
			clear();
			menu();
			attron(COLOR_PAIR(1));
			refresh();
			attron(COLOR_PAIR(2));
			mvprintw((yMax / 2 - 12) + 9, (xMax / 2) - 7, "Exit game!");
			refresh();
			attron(COLOR_PAIR(1));
			mvprintw((yMax / 2 - 12) + 10, (xMax / 2) - 7, "Explorer mode!");
			mvprintw((yMax / 2 - 12) + 11, (xMax / 2) - 7, "Normal mode!");
			refresh();
			if (key == '\r')exit(0);
		}
		else if (mode == 2)
		{
			clear();
			menu();
			attron(COLOR_PAIR(1));
			mvprintw((yMax / 2 - 12) + 9, (xMax / 2) - 7, "Exit game!");
			refresh();
			attron(COLOR_PAIR(2));
			mvprintw((yMax / 2 - 12) + 10, (xMax / 2) - 7, "Explorer mode!");
			refresh();
			attron(COLOR_PAIR(1));
			mvprintw((yMax / 2 - 12) + 11, (xMax / 2) - 7, "Normal mode!");
			refresh();
			if (key == '\r')
			{
				clear();
				start = clock();
				explorer_mode();
			}
		}
		else if (mode == 3)
		{
			clear();
			menu();
			attron(COLOR_PAIR(1));
			mvprintw((yMax / 2 - 12) + 9, (xMax / 2) - 7, "Exit game!");
			mvprintw((yMax / 2 - 12) + 10, (xMax / 2) - 7, "Explorer mode!");
			refresh();
			attron(COLOR_PAIR(2));
			mvprintw((yMax / 2 - 12) + 11, (xMax / 2) - 7, "Normal mode!");
			refresh();
			if (key == '\r')
			{
				clear();
				start = clock();
				Normal_mode();
			}
		}
	}
	endwin();
	return 0;
}
