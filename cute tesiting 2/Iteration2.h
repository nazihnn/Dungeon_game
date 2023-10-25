
#include <stdio.h>
#include <conio.h>
#include<string.h>
#include"curses.h"
#include<Windows.h>
#include <time.h>


#define Density1 6 //Concentration1
#define Density2 4 //Concentration2
#define Density3 2 //Concentration3

int gameflag = 0;

int roomwidth[5] = {
  40,
  80,
  40,
  80,
  58
};
int roomheight[5] = {
  20,
  29,
  20,
  29,
  29
};

enum {
  LEFTROOM, //left room
  UPROOM, //up room
  RIGHTROOM, //right room
  DOWNROOM, //down room
  MIDDELROOM, //middle room
  KEEPSTATE, //Remain unchanged
  PEOPLEMOVE, //move
  SUCCESS //success
};


typedef struct  People {//player
	int x;
	int y;
	int step;
	int Live_Value;
	int score;
	int nowroom;
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


char mdraw[40][100];

people createpeople( int x, int y, int step ,int Live_Value, int score, int level);

robot createrobot(int x,int y);

fetid_Air createpoison(int x, int y );

void deleteAllDrawFetid_Air(robot  mrobot,int width, int height); //delete smell

void DrawAllFetid_Air(robot  mrobot,int width, int height) ;

int changeLive_Value(int x, int y, int livevalue, robot robot);//Vitality

int PeopleMoveCheckAtMiddleRoom(int x, int y, int width, int height);//check player move 
int PeopleMoveCheckAtLeftRoom(int x, int y, int width, int height);
int PeopleMoveCheckAtRightRoom(int x, int y, int width, int height);
int PeopleMoveCheckAtUpRoom(int x, int y, int width, int height);
int PeopleMoveCheckAtDownRoom(int x, int y, int width, int height);


people PeopleMove(people mpeople, int room);//player move

robot initFetid_Air(robot mrobot);//Initialize smell position

robot RobotMove(robot mrobot, int width, int height);//robot move

robot initrobot(int width, int height);//Initialize robot

people initpeople(robot * mrobot, int num, int width, int height);

//people initTestPeople();

void initDraw();//Initialize

void Draw2(int width, int height);

void run2();

void menuscreen();


void Draw();



