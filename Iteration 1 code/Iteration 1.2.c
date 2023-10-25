#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include<string.h>
#include<Windows.h>
#define WIDTH 58
#define HIGHT 29
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
char mdraw[HIGHT][WIDTH];
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
int main() {
	people mpeople;
}

