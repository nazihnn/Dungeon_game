#include <stdlib.h>
#include <stdio.h>

typedef struct  People {//player
	int x;
	int y;
	int step;
	int Live_Value;
	int score;
	int nowroom;
	int level;
}people;

typedef struct Fetid_Air {//smell
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