#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include<string.h>
#include<Windows.h>
#include <time.h>
#define WIDTH 58
#define HIGHT 29

#define Density1 6 //Concentration1
#define Density2 4 //Concentration2
#define Density3 2 //Concentration3
typedef struct  People{//player
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
	if (x == WIDTH-1 &&
		y  == HIGHT /2)
	{

		return 1;

	}
	else if (x == WIDTH-1 &&
		y != HIGHT / 2)
	{
		return 0;
	}

	if (x <= 0)
	{
		return 0;

	}


	 if (y<= 0)
	{
		return 0;
	}
	 if (y>=  HIGHT-1)
	{

		return 0;

	}
	
	return 2;
}
people PeopleMove(people mpeople)//player move
{
	     printf("a left d right w up s down:");
	     setbuf(stdin,NULL);//Clear cache
	    char ch= _getch();
		
		//scanf("%c", &ch);
		int tmpx = mpeople.x, tmpy = mpeople.y;
		if (ch == 'a')//Move to the left
		{
			tmpx --;
		}
		else if (ch == 'd')//right
		{
			tmpx ++;
		}
		else if (ch == 'w')//up
		{
			tmpy --;
		}
		else if (ch == 's')//down
		{
			tmpy ++;
		}
		if (PeopleMoveCheck(tmpx, tmpy) ==2)
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
			
			printf("Success!\n");
			mpeople.level++;
			
			return mpeople;
			
		}
		return mpeople;
		
	
}
robot initFetid_Air(robot mrobot)//Initialize smell position
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == 0 || j == 0||i==2||j==2)
			{
				mrobot.fetid_air1[i*3+j].x = mrobot.x - 1+i;
				mrobot.fetid_air1[i*3+j].y = mrobot.y-1+j;
			}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (i == 0 || j == 0||j==4||i==4)
			{
				mrobot.fetid_air2[i * 5 + j].x = mrobot.x-2+i;
				mrobot.fetid_air2[i * 5 + j].y = mrobot.y-2+j;
			}
	for (int i = 0; i <7; i++)
		for (int j = 0; j < 7; j++)
			if (i == 0 || j == 0||i==6||j==6)
			{
				mrobot.fetid_air3[i * 7 + j].x = mrobot.x -3+i;
				mrobot.fetid_air3[i * 7 + j].y = mrobot.y -3+j;
			}
	return mrobot;
}
robot RobotMove(robot mrobot)//robot move
{
	int tmpx = mrobot.x, tmpy = mrobot.y;
	//srand((unsigned int)time(NULL));//set random point
	int direction = rand() % 4+0;//Generate random values
	if (direction == 0)//up
		tmpy --;
	else if (direction == 1)//left
		tmpx ++;
	else if (direction == 2)//down
		tmpy ++;
	else if (direction == 3)//right
		tmpx --;
	if (tmpx<=0)
	{
		return mrobot;

	}
	
	 if (tmpx >= WIDTH - 1)
	{
		
		return mrobot;

	}
	 if (tmpy<= 0)
	{
		return mrobot;
	}
	if (tmpy>= HIGHT - 1)
	{
		
		return mrobot;

	}
	mdraw[mrobot.y][mrobot.x] = ' ';
	mrobot.x = tmpx;
	mrobot.y = tmpy;
	
	mdraw[mrobot.y][mrobot.x] = '#';
	mrobot=initFetid_Air(mrobot);
	
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
people initpeople(robot *mrobot,int num)//Initialize player
{
	people mpeople;
	
	int initnumx,initnumy;
	while (1)
	{
		int flg = 0;
		srand((unsigned int)time(NULL));//set random points
		
		initnumx = rand() % 57 + 0;
		initnumy = rand() % 28 + 0;
		for (int i = 0; i < num; i++)
		{
			if (mrobot[i].x == initnumx&&mrobot[i].y==initnumy)
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
	mpeople.step =initnumx-58 -abs(initnumy-HIGHT/2);
	
	
	return mpeople;
}
void initDraw()//Initialize
{
	for(int i=0;i<HIGHT;i++)
		for (int j = 0; j < WIDTH; j++)
		{
			if (j == WIDTH - 1 && i != HIGHT / 2)
				mdraw[i][j] = '|';
			else if (i== HIGHT - 1)
				mdraw[i][j] = '-';
			else mdraw[i][j] = ' ';
		}
}
void Draw()
{
	system("cls");
	for (int i = 0; i < HIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			printf("%c", mdraw[i][j]);
		}
		printf("\n");
	}
}
int main() {
	people mpeople;
	int rscore = 0;
	robot mrobot[58];
	

	for(int i=1,j=10;i<=5;i++,j+=6)
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
			setbuf(stdin, NULL);//Clear cache
			Draw();
			printf("Vitality:%d\n", mpeople.Live_Value);
			mpeople = PeopleMove(mpeople);
			
			if (mpeople.level > i&&mpeople.level<=5)
			{
				rscore += mpeople.Live_Value - mpeople.step + 10 * i;
				printf("About to enter the%d level\n", mpeople.level);
				printf("Current score%d\n", rscore);
				_getch();
				break;

			}
			if (mpeople.level > i&&mpeople.level >= 5)
			{
				
				printf("Success!\n");

				printf( "The total score: %d", rscore);
				
				_getch();
				fflush(stdin);
				break;

			}
			for (int w = 0; w < j; w++)
			{
				mpeople.Live_Value = changeLive_Value(mpeople.x, mpeople.y, mpeople.Live_Value, mrobot[w]);
				if (mpeople.Live_Value <= 0)
				{
					rscore += mpeople.Live_Value - mpeople.step ;
					printf( "Failure！\n");
					printf("Total score: %d",rscore);
					printf("To end the game, please press: g. To restart the game, please press any key.\n");
					
					
					
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
				fflush(stdin);
			}
			for (int w = 0; w < j; w++)
			{
				mrobot[w] = RobotMove(mrobot[w]);
				if (mpeople.x == mrobot[w].x&&mpeople.y == mrobot[w].y)
				{
					rscore += mpeople.Live_Value - mpeople.step;
					printf("Failure! \n");
					printf("Total score: %d", rscore);
					printf("To end the game, please press: g. To restart the game, please press any key.\n");
					char ch=_getch() ;
					
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
			
		}
	}
	_getch();
	return 0;
}
