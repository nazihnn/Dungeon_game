#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include<string>
#include <graphics.h>//Graphics libary
#include <time.h>//time funtion
#define WIDTH 900
#define HIGHT 600
#define MSIZE 20//grid width
#define WALLWIDTH 10//wall width
#define PeoPlewidth 18
#define Density1 6 //Concentration 1
#define Density2 4 //Concentration 2
#define Density3 2 //Concentration 2
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
typedef struct Robot {//Robot
	int x;
	int y;
	double r;
	fetid_Air fetid_air1[9];
	fetid_Air fetid_air2[25];
	fetid_Air fetid_air3[49];
}robot;

void CharToTchar(const char* _char, TCHAR* tchar)//character type conversion
{
	int iLength;//Get byte length
	iLength = MultiByteToWideChar(CP_ACP, 0, _char, -1, NULL, 0);
	//Assign the value of tchar to_char
	MultiByteToWideChar(CP_ACP, 0, _char, -1, tchar, iLength);
}
void DrawWallAndDoor()//make door and wall
{
	setfillcolor(RGB(0, 0, 0));//set wall colour:black
	//fill all
	fillrectangle(0, 0, WALLWIDTH, HIGHT);//left
	fillrectangle(0, 0, HIGHT, WALLWIDTH);//up
	fillrectangle(HIGHT - WALLWIDTH, 0, HIGHT, HIGHT);//right
	fillrectangle(0, HIGHT - WALLWIDTH, HIGHT, HIGHT);//down
	setfillcolor(RGB(0, 255, 0));//set wall colour: black

	//fillrectangle(0, HIGHT/2- WALLWIDTH, WALLWIDTH, HIGHT/2+ WALLWIDTH);//left

	//fillrectangle(HIGHT/2- WALLWIDTH, 0, HIGHT/2+ WALLWIDTH, WALLWIDTH);//up
	int door_y = (HIGHT - 2 * WALLWIDTH) / MSIZE / 2 + (HIGHT - 2 * WALLWIDTH) / MSIZE % 2;
	door_y = WALLWIDTH + door_y * MSIZE;
	fillrectangle(HIGHT - WALLWIDTH, door_y, HIGHT, door_y + MSIZE);//right

	//fillrectangle(HIGHT/2- WALLWIDTH, HIGHT- WALLWIDTH, HIGHT/2+ WALLWIDTH, HIGHT);//down
}
void deleteFetidAir(int x, int y, int density)//delete smell
{
	for (int i = WALLWIDTH + x * MSIZE + 2; i < WALLWIDTH + x * MSIZE + MSIZE - 2; i += density)
		for (int j = WALLWIDTH + y * MSIZE + 2; j < WALLWIDTH + y * MSIZE + MSIZE - 2; j += density)
			putpixel(i, j, RGB(255, 255, 255));//Horizontal and vertical coordinates and colour

}
void DrawFetidAir(int x, int y, int density)//make smell
{
	for (int i = WALLWIDTH + x * MSIZE + 2; i < WALLWIDTH + x * MSIZE + MSIZE - 2; i += density)
		for (int j = WALLWIDTH + y * MSIZE + 2; j < WALLWIDTH + y * MSIZE + MSIZE - 2; j += density)
			putpixel(i, j, RGB(0, 0, 0));//Horizontal and vertical coordinates and colour
}
void DrawGrid(int start_x, int start_y, int end_x, int end_y)//make grid
{
	setlinecolor(RGB(0, 255, 0));//green
	setlinestyle(1, 1);//
	for (int i = start_x; i <= end_x; i += MSIZE)//make vertical line
	{
		line(i, start_y, i, end_y);//
	}
	for (int i = start_y; i <= end_y; i += MSIZE)//make horizontal line
	{
		line(start_x, i, end_x, i);
	}
}

int changeLive_Value(int x, int y, int livevalue, Robot robot)//change blood value
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
	setfillcolor(RGB(255, 255, 255));//set fill colour of wall: white
	//fill all
	fillrectangle(600, 150, 800, 180);//left
	setfillcolor(RGB(255, 0, 0));//set fill color of colour: red
	//fill all

	fillrectangle(600, 150, 600 + 2 * livevalue, 180);//left
	setlinecolor(RGB(255, 255, 255));
	setfillcolor(RGB(255, 255, 255));//set fill color of wall: white

	//fill all
	fillrectangle(805, 150, 845, 180);//left
	TCHAR  tstr[100];
	char str[20]; sprintf(str, "%d", livevalue);
	CharToTchar(str, tstr);
	//setbkmode(TRANSPARENT);//word background transparent
	outtextxy(805, 150, tstr);

	setlinecolor(RGB(0, 255, 0));//line restore to green
	return livevalue;
}
int PeopleMoveCheck(int x, int y)//check player move
{
	if (x == (HIGHT - 2 * WALLWIDTH) / MSIZE &&
		y == (HIGHT - 2 * WALLWIDTH) / MSIZE / 2 + (HIGHT - 2 * WALLWIDTH) / MSIZE % 2)
	{

		return 1;

	}
	else if (x == (HIGHT - 2 * WALLWIDTH) / MSIZE &&
		y != (HIGHT - 2 * WALLWIDTH) / MSIZE / 2 + (HIGHT - 2 * WALLWIDTH) / MSIZE % 2)
	{
		return 0;
	}

	if (x < 0)
	{
		return 0;

	}


	if (y < 0)
	{
		return 0;
	}
	if (y == (HIGHT - 2 * WALLWIDTH) / MSIZE)
	{

		return 0;

	}


	return 2;
}
people PeopleMove(people mpeople)//player move
{
	char ch = _getch();
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
		setfillcolor(RGB(255, 255, 255));//restore white
		//fill all
		fillrectangle(WALLWIDTH + MSIZE * mpeople.x, WALLWIDTH + MSIZE * mpeople.y, WALLWIDTH + MSIZE * mpeople.x + PeoPlewidth, WALLWIDTH + MSIZE * mpeople.y + PeoPlewidth);
		setfillcolor(RGB(255, 0, 0));//restore white
		mpeople.x = tmpx;
		mpeople.y = tmpy;
		//fill all
		fillrectangle(WALLWIDTH + MSIZE * mpeople.x, WALLWIDTH + MSIZE * mpeople.y, WALLWIDTH + MSIZE * mpeople.x + PeoPlewidth, WALLWIDTH + MSIZE * mpeople.y + PeoPlewidth);
		mpeople.step++;
		return mpeople;
	}
	else if (PeopleMoveCheck(tmpx, tmpy) == 1)
	{
		setcolor(RGB(255, 0, 0));//word colour
		settextstyle(30, 30, L"����");//word width and height and font
		//setbkmode(TRANSPARENT);//word background transparent
		outtextxy(250, 200, L"success to pass!");
		mpeople.level++;

		return mpeople;

	}
	return mpeople;


}
void deleteAllDrawFetid_Air(robot& mrobot)//make smell
{
	int max = (HIGHT - 2 * WALLWIDTH) / MSIZE;
	setfillcolor(RGB(255, 255, 255));//set fill colour of wall: white
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == 0 || j == 0 || i == 2 || j == 2)
			{
				if (mrobot.fetid_air1[i * 3 + j].x >= 0 && mrobot.fetid_air1[i * 3 + j].x < max)
					if (mrobot.fetid_air1[i * 3 + j].y >= 0 && mrobot.fetid_air1[i * 3 + j].y < max)
						deleteFetidAir(mrobot.fetid_air1[i * 3 + j].x,
							mrobot.fetid_air1[i * 3 + j].y,
							8 - Density1
						);


			}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (i == 0 || j == 0 || i == 4 || j == 4)
			{
				if (mrobot.fetid_air2[i * 5 + j].x >= 0 && mrobot.fetid_air2[i * 5 + j].x < max)
					if (mrobot.fetid_air2[i * 5 + j].y >= 0 && mrobot.fetid_air2[i * 5 + j].y < max)
						deleteFetidAir(mrobot.fetid_air2[i * 5 + j].x,
							mrobot.fetid_air2[i * 5 + j].y,
							8 - Density2
						);
			}
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			if (i == 0 || j == 0 || i == 6 || j == 6)
			{
				if (mrobot.fetid_air3[i * 7 + j].x >= 0 && mrobot.fetid_air3[i * 7 + j].x < max)
					if (mrobot.fetid_air3[i * 7 + j].y >= 0 && mrobot.fetid_air3[i * 7 + j].y < max)
						deleteFetidAir(mrobot.fetid_air3[i * 7 + j].x,
							mrobot.fetid_air3[i * 7 + j].y,
							8 - Density3
						);


			}
}
void DrawAllFetid_Air(robot& mrobot)//make smell
{
	int max = (HIGHT - 2 * WALLWIDTH) / MSIZE;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == 0 || j == 0 || i == 2 || j == 2)
			{
				if (mrobot.fetid_air1[i * 3 + j].x >= 0 && mrobot.fetid_air1[i * 3 + j].x < max)
					if (mrobot.fetid_air1[i * 3 + j].y >= 0 && mrobot.fetid_air1[i * 3 + j].y < max)
						DrawFetidAir(mrobot.fetid_air1[i * 3 + j].x,
							mrobot.fetid_air1[i * 3 + j].y,
							8 - Density1
						);

			}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (i == 0 || j == 0 || i == 4 || j == 4)
			{
				if (mrobot.fetid_air2[i * 5 + j].x >= 0 && mrobot.fetid_air2[i * 5 + j].x < max)
					if (mrobot.fetid_air2[i * 5 + j].y >= 0 && mrobot.fetid_air2[i * 5 + j].y < max)
						DrawFetidAir(mrobot.fetid_air2[i * 5 + j].x,
							mrobot.fetid_air2[i * 5 + j].y,
							8 - Density2
						);
			}
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			if (i == 0 || j == 0 || i == 6 || j == 6)
			{
				if (mrobot.fetid_air3[i * 7 + j].x >= 0 && mrobot.fetid_air3[i * 7 + j].x < max)
					if (mrobot.fetid_air3[i * 7 + j].y >= 0 && mrobot.fetid_air3[i * 7 + j].y < max)
						DrawFetidAir(mrobot.fetid_air3[i * 7 + j].x,
							mrobot.fetid_air3[i * 7 + j].y,
							8 - Density3
						);
			}
}
robot initFetid_Air(robot& mrobot)//Initialize smell location
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
robot RobotMove(robot& mrobot)//robot move
{
	int tmpx = mrobot.x, tmpy = mrobot.y;
	//srand((unsigned int)time(NULL));//set random point
	int direction = rand() % 4 + 0;//rand() make random number
	if (direction == 0)//up
		tmpy--;
	else if (direction == 1)//right
		tmpx++;
	else if (direction == 2)//down
		tmpy++;
	else if (direction == 3)//left
		tmpx--;
	if (tmpx < 0)
	{
		return mrobot;

	}

	if (tmpx >= (HIGHT - 2 * WALLWIDTH) / MSIZE)
	{

		return mrobot;

	}
	if (tmpy < 0)
	{
		return mrobot;
	}
	if (tmpy >= (HIGHT - 2 * WALLWIDTH) / MSIZE)
	{

		return mrobot;

	}
	setfillcolor(RGB(255, 255, 255));//set fill colour
	//fill all
	fillcircle(MSIZE + MSIZE * mrobot.x, MSIZE + MSIZE * mrobot.y, mrobot.r);//Horizontal and vertical coordinate and radius
	deleteAllDrawFetid_Air(mrobot);
	mrobot.x = tmpx;
	mrobot.y = tmpy;

	setfillcolor(RGB(0, 0, 0));//set fill colour
	//fill all
	fillcircle(MSIZE + MSIZE * mrobot.x, MSIZE + MSIZE * mrobot.y, mrobot.r);//Horizontal and vertical coordinate and radius
	mrobot = initFetid_Air(mrobot);
	DrawAllFetid_Air(mrobot);
	return mrobot;
}
robot initrobot()//initialize robot
{
	robot mrobot;
	//srand((unsigned int)time(NULL));//set random point
	int mrand = (HIGHT - 2 * WALLWIDTH) / 20;

	int initnumx = rand() % mrand + 0;
	int initnumy = rand() % mrand + 0;
	mrobot.x = initnumx;
	mrobot.y = initnumy;
	mrobot.r = 10;
	mrobot = initFetid_Air(mrobot);
	setfillcolor(RGB(0, 0, 0));//black
	//fill all
	fillcircle(MSIZE + initnumx * MSIZE, initnumy * MSIZE + MSIZE, mrobot.r);
	return mrobot;

}
people initpeople(robot* mrobot, int num)//initialize player
{
	people mpeople;
	int mrand = (HIGHT - 2 * WALLWIDTH) / 20;
	int initnum;
	while (1)
	{
		int flg = 0;
		srand((unsigned int)time(NULL));//set random location

		initnum = rand() % mrand + 0;
		for (int i = 0; i < num; i++)
		{
			if (mrobot[i].x == initnum)
			{
				flg = 1;
				break;
			}
		}
		if (flg == 0)
		{
			mpeople.x = initnum;
			mpeople.y = initnum;
			break;
		}
	}
	mpeople.Live_Value = 100;//blood value
	mpeople.step = initnum - mrand - abs(initnum - mrand / 2);

	setfillcolor(RGB(255, 0, 0));//red
	//fill all
	fillrectangle(11 + initnum * 20, 11 + initnum * 20, initnum * 20 + 11 + PeoPlewidth, initnum * 20 + PeoPlewidth + 11);
	return mpeople;
}
void initDraw()//initialize
{
	setbkcolor(RGB(255, 255, 255));
	cleardevice();
	DrawWallAndDoor();
	DrawGrid(WALLWIDTH, WALLWIDTH, HIGHT - WALLWIDTH, HIGHT - WALLWIDTH);
	setcolor(RGB(255, 0, 0));//word colour
	settextstyle(20, 10, L"����");//word width height and font
	setbkmode(TRANSPARENT);//word background transparent
	outtextxy(625, 120, L"Blood:");
	setfillcolor(RGB(255, 0, 0));//set fill colour of wall: red
	//fill all
	fillrectangle(625, 90, 645, 110);//left
	outtextxy(650, 90, L"Player");

	setfillcolor(RGB(0, 0, 0));
	//full fill
	fillcircle(635, 60, 10);//left
	outtextxy(650, 50, L"Robot");
	outtextxy(625, 180, L"Instructions: ");
	outtextxy(625, 205, L"a: left, d: left");
	outtextxy(625, 235, L"w: up, s: down");
}

int main() {
	people mpeople;
	int rscore = 0;
	robot mrobot[28];
	initgraph(WIDTH, HIGHT);//Create window

	for (int i = 1, j = 4; i <= 5; i++, j += 4)
	{

		initDraw();
		srand((unsigned int)time(NULL));//set random location

		for (int w = 0; w < j; w++)
		{
			mrobot[w] = initrobot();
		}
		mpeople = initpeople(mrobot, j);
		mpeople.level = i;
		int flg = 1;
		while (flg)
		{
			mpeople = PeopleMove(mpeople);
			if (mpeople.level > i && mpeople.level <= 5)
			{
				setcolor(RGB(255, 0, 0));//word colour
				settextstyle(30, 30, L"����");//set word width and height and font
				TCHAR  tstr[100];
				char str[20]; sprintf(str, "Enter to level %d", mpeople.level);
				CharToTchar(str, tstr);
				//setbkmode(TRANSPARENT);//word background transparent
				outtextxy(250, 300, tstr);
				setcolor(RGB(255, 0, 0));//word colour
				settextstyle(20, 10, L"����");//word width and height and font
				TCHAR  tsocre[100];
				rscore += mpeople.Live_Value - mpeople.step;
				char score[20]; sprintf(score, "current score: %d", rscore);
				CharToTchar(score, tsocre);
				//setbkmode(TRANSPARENT);//word background transparent
				outtextxy(600, 400, tsocre);
				_getch();
				break;

			}
			if (mpeople.level > i && mpeople.level >= 5)
			{
				setcolor(RGB(255, 0, 0));//word colour
				settextstyle(30, 30, L"����");//word width and height and font

				//setbkmode(TRANSPARENT);//
				outtextxy(250, 300, L"congratulation to pass!");

				TCHAR  tsocre[100];
				rscore += mpeople.Live_Value - mpeople.step;
				char score[20]; sprintf(score, "Total score: %d", rscore);
				CharToTchar(score, tsocre);
				//setbkmode(TRANSPARENT);//word background transparent
				settextstyle(20, 10, L"����");//word width and height and font
				outtextxy(600, 400, tsocre);
				_getch();
				break;

			}
			for (int w = 0; w < j; w++)
			{
				mpeople.Live_Value = changeLive_Value(mpeople.x, mpeople.y, mpeople.Live_Value, mrobot[w]);
				if (mpeople.Live_Value <= 0)
				{
					setcolor(RGB(0, 0, 0));//word colour
					settextstyle(20, 10, L"����");//word width and height and font
					//setbkmode(TRANSPARENT);//word background transparent
					outtextxy(20, 300, L"Failure!");
					outtextxy(20, 340, L"End the game please press: g, restart the game press any key");
					setcolor(RGB(255, 0, 0));//word colour
					settextstyle(20, 10, L"����");//word weight and height and font
					TCHAR  tsocre[100];
					char score[20]; sprintf(score, "current score: %d", mpeople.Live_Value - mpeople.step);
					CharToTchar(score, tsocre);
					//setbkmode(TRANSPARENT);//word background transparent
					outtextxy(600, 400, tsocre);
					char ch = _getch();
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
			}
			for (int w = 0; w < j; w++)
			{
				mrobot[w] = RobotMove(mrobot[w]);
				if (mpeople.x == mrobot[w].x && mpeople.y == mrobot[w].y)
				{
					setcolor(RGB(0, 0, 0));//word colour
					settextstyle(20, 10, L"����");
					//setbkmode(TRANSPARENT);word background transparent
					outtextxy(20, 300, L"Failure!");
					outtextxy(20, 340, L"end the game please press: g, restart the game press any key");
					setcolor(RGB(255, 0, 0));//word colour
					settextstyle(20, 10, L"����");
					TCHAR  tsocre[100];
					char score[20]; sprintf(score, "current score: %d", mpeople.Live_Value - mpeople.step);
					CharToTchar(score, tsocre);
					//setbkmode(TRANSPARENT);//word background transparent
					outtextxy(600, 400, tsocre);
					char ch = _getch();
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
			}

		}
	}
	_getch();
	closegraph();//colse window

}