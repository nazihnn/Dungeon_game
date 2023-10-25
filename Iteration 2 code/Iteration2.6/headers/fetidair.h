#include <stdio.h>
#include <stdlib.h>

#define Density1 6   //Concentration1
#define Density2 4   //Concentration2
#define Density3 2   //Concentration3

char mdraw[40][100];

void deleteAllDrawFetid_Air(robot  mrobot, int width, int height)  //Delete the original smell when the robot move
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == 0 || j == 0 || i == 2 || j == 2)
			{
				if (mrobot.fetid_air1[i * 3 + j].x > 0 && mrobot.fetid_air1[i * 3 + j].x < width - 1)
					if (mrobot.fetid_air1[i * 3 + j].y > 0 && mrobot.fetid_air1[i * 3 + j].y < height - 1)
						mdraw[mrobot.fetid_air1[i * 3 + j].y][mrobot.fetid_air1[i * 3 + j].x] = ' ';
			}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (i == 0 || j == 0 || i == 4 || j == 4)
			{
				if (mrobot.fetid_air2[i * 5 + j].x > 0 && mrobot.fetid_air2[i * 5 + j].x < width - 1)
					if (mrobot.fetid_air2[i * 5 + j].y > 0 && mrobot.fetid_air2[i * 5 + j].y < height - 1)
						mdraw[mrobot.fetid_air2[i * 5 + j].y][mrobot.fetid_air2[i * 5 + j].x] = ' ';
			}
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			if (i == 0 || j == 0 || i == 6 || j == 6)
			{
				if (mrobot.fetid_air3[i * 7 + j].x > 0 && mrobot.fetid_air3[i * 7 + j].x < width - 1)
					if (mrobot.fetid_air3[i * 7 + j].y > 0 && mrobot.fetid_air3[i * 7 + j].y < height - 1)
						mdraw[mrobot.fetid_air3[i * 7 + j].y][mrobot.fetid_air3[i * 7 + j].x] = ' ';
			}
}
void DrawAllFetid_Air(robot  mrobot, int width, int height)   //Generation the new smell when the robot move
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (i == 0 || j == 0 || i == 2 || j == 2)
			{
				if (mrobot.fetid_air1[i * 3 + j].x > 0 && mrobot.fetid_air1[i * 3 + j].x < width - 1)
					if (mrobot.fetid_air1[i * 3 + j].y > 0 && mrobot.fetid_air1[i * 3 + j].y < height - 1)
						mdraw[mrobot.fetid_air1[i * 3 + j].y][mrobot.fetid_air1[i * 3 + j].x] = '.';
			}
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (i == 0 || j == 0 || i == 4 || j == 4)
			{
				if (mrobot.fetid_air2[i * 5 + j].x > 0 && mrobot.fetid_air2[i * 5 + j].x < width - 1)
					if (mrobot.fetid_air2[i * 5 + j].y > 0 && mrobot.fetid_air2[i * 5 + j].y < height - 1)
						mdraw[mrobot.fetid_air2[i * 5 + j].y][mrobot.fetid_air2[i * 5 + j].x] = '.';
			}
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 7; j++)
			if (i == 0 || j == 0 || i == 6 || j == 6)
			{
				if (mrobot.fetid_air3[i * 7 + j].x > 0 && mrobot.fetid_air3[i * 7 + j].x < width - 1)
					if (mrobot.fetid_air3[i * 7 + j].y > 0 && mrobot.fetid_air3[i * 7 + j].y < height - 1)
						mdraw[mrobot.fetid_air3[i * 7 + j].y][mrobot.fetid_air3[i * 7 + j].x] = '.';
			}
}
int changeLive_Value(int x, int y, int livevalue, robot robot)   //change blood value
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

