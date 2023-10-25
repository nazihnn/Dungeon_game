#include <stdio.h>
#include <stdlib.h>

void Characters_E(int width, int height, int x, int y)		//Add colors for chatracters in explorer mode
{
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(4, COLOR_BLACK, COLOR_RED);
	init_pair(6, COLOR_BLACK, COLOR_YELLOW);
	init_pair(16, COLOR_BLACK, COLOR_BLACK);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j<x + 10 && j>x - 10 && i<y + 10 && i>y - 10)
			{
				if (mdraw[i][j] == '#')			//Robot color
				{
					attrset(COLOR_PAIR(5));
					mvprintw(i, j, "%c", mdraw[i][j]);
					refresh();
				}
				else  if (mdraw[i][j] == '|')		//Horizontal Wall color
				{
					attrset(COLOR_PAIR(1));
					mvprintw(i, j, "%c", mdraw[i][j]);
					refresh();
				}
				else  if (mdraw[i][j] == '-')		//Vertical Wall color
				{
					attrset(COLOR_PAIR(1));
					mvprintw(i, j, "%c", mdraw[i][j]);
					refresh();
				}
				else  if (mdraw[i][j] == '.')		//Smell color
				{
					attrset(COLOR_PAIR(5));
					mvprintw(i, j, "%c", mdraw[i][j]);
					refresh();
				}
				else
				{
					attrset(COLOR_PAIR(16));
					mvprintw(i, j, " ");
					refresh();
				}
			}
		}
	}
}
void Characters_N(int width, int height, int x, int y)	  //Add colors for chatracters in normal mode
{
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(4, COLOR_BLACK, COLOR_RED);
	init_pair(6, COLOR_BLACK, COLOR_YELLOW);
	init_pair(16, COLOR_BLACK, COLOR_BLACK);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			{
				if (mdraw[i][j] == '#')		        //Robot color
				{
					attrset(COLOR_PAIR(5));
					mvprintw(i, j, "%c", mdraw[i][j]);
					refresh();
				}
				else  if (mdraw[i][j] == '|')		//Horizontal Wall color
				{
					attrset(COLOR_PAIR(1));
					mvprintw(i, j, "%c", mdraw[i][j]);
					refresh();
				}
				else  if (mdraw[i][j] == '-')		//Vertical Wall color
				{
					attrset(COLOR_PAIR(1));
					mvprintw(i, j, "%c", mdraw[i][j]);
					refresh();
				}
				else  if (mdraw[i][j] == '.')		//Smell color
				{
					attrset(COLOR_PAIR(5));
					mvprintw(i, j, "%c", mdraw[i][j]);
					refresh();
				}
				else
				{
					attrset(COLOR_PAIR(16));
					mvprintw(i, j, " ");
					refresh();
				}
			}
		}
	}
}