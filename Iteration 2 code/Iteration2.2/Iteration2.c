# include "Iteration1.5.2.h"
#include <stdio.h>
#include <conio.h>
#include<string.h>
#include"curses.h"
#include<Windows.h>
#include <time.h>



people createpeople( int x, int y, int step ,int Live_Value, int score, int level){
	people z ={x,y,step,Live_Value,score,level};
	return z;

}

robot createrobot(int x, int y){
	robot h = {x,y};
	return h;
}

fetid_Air createpoison(int x, int y ){
	fetid_Air b={x,y};
	return b;
}

void deleteAllDrawFetid_Air(robot mrobot, int width, int height) //delete smell
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (i == 0 || j == 0 || i == 2 || j == 2) {
        if (mrobot.fetid_air1[i * 3 + j].x > 0 && mrobot.fetid_air1[i * 3 + j].x < width - 1)
          if (mrobot.fetid_air1[i * 3 + j].y > 0 && mrobot.fetid_air1[i * 3 + j].y < height - 1)
            mdraw[mrobot.fetid_air1[i * 3 + j].y][mrobot.fetid_air1[i * 3 + j].x] = ' ';

      }
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      if (i == 0 || j == 0 || i == 4 || j == 4) {
        if (mrobot.fetid_air2[i * 5 + j].x > 0 && mrobot.fetid_air2[i * 5 + j].x < width - 1)
          if (mrobot.fetid_air2[i * 5 + j].y > 0 && mrobot.fetid_air2[i * 5 + j].y < height - 1)
            mdraw[mrobot.fetid_air2[i * 5 + j].y][mrobot.fetid_air2[i * 5 + j].x] = ' ';
      }
  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 7; j++)
      if (i == 0 || j == 0 || i == 6 || j == 6) {
        if (mrobot.fetid_air3[i * 7 + j].x > 0 && mrobot.fetid_air3[i * 7 + j].x < width - 1)
          if (mrobot.fetid_air3[i * 7 + j].y > 0 && mrobot.fetid_air3[i * 7 + j].y < height - 1)
            mdraw[mrobot.fetid_air3[i * 7 + j].y][mrobot.fetid_air3[i * 7 + j].x] = ' ';
      }
}

void DrawAllFetid_Air(robot mrobot, int width, int height) //Draw smell
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (i == 0 || j == 0 || i == 2 || j == 2) {
        if (mrobot.fetid_air1[i * 3 + j].x > 0 && mrobot.fetid_air1[i * 3 + j].x < width - 1)
          if (mrobot.fetid_air1[i * 3 + j].y > 0 && mrobot.fetid_air1[i * 3 + j].y < height - 1)
            mdraw[mrobot.fetid_air1[i * 3 + j].y][mrobot.fetid_air1[i * 3 + j].x] = '.';
      }
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      if (i == 0 || j == 0 || i == 4 || j == 4) {
        if (mrobot.fetid_air2[i * 5 + j].x > 0 && mrobot.fetid_air2[i * 5 + j].x < width - 1)
          if (mrobot.fetid_air2[i * 5 + j].y > 0 && mrobot.fetid_air2[i * 5 + j].y < height - 1)
            mdraw[mrobot.fetid_air2[i * 5 + j].y][mrobot.fetid_air2[i * 5 + j].x] = '.';
      }
  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 7; j++)
      if (i == 0 || j == 0 || i == 6 || j == 6) {
        if (mrobot.fetid_air3[i * 7 + j].x > 0 && mrobot.fetid_air3[i * 7 + j].x < width - 1)
          if (mrobot.fetid_air3[i * 7 + j].y > 0 && mrobot.fetid_air3[i * 7 + j].y < height - 1)
            mdraw[mrobot.fetid_air3[i * 7 + j].y][mrobot.fetid_air3[i * 7 + j].x] = '.';
      }
}
int changeLive_Value(int x, int y, int livevalue, robot robot) //change blood value
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
int PeopleMoveCheckAtMiddleRoom(int x, int y, int width, int height) //check move of player
{

  if (x >= width - 1 &&
    y == height / 2) {
    return RIGHTROOM;
  } else if (x <= 0 && y == height / 2) {
    return LEFTROOM;
  } else if (y <= 0 && x == width / 2) {
    return UPROOM;
  } else if (y >= height - 1 && x == width / 2) {
    return DOWNROOM;
  } else if (x >= width - 1 &&
    y != height / 2) {
    return KEEPSTATE;
  } else if (x <= 0 && y != height / 2) {
    return KEEPSTATE;
  } else if (y <= 0 && x != width / 2) {
    return KEEPSTATE;
  } else if (y >= height - 1 && x != width / 2) {
    return KEEPSTATE;
  }
  return PEOPLEMOVE;
}
int PeopleMoveCheckAtLeftRoom(int x, int y, int width, int height) //check move of player
{
  if (x >= width - 1 &&
    y == height / 2) {
    return MIDDELROOM;

  } else if (x >= width - 1 &&
    y != height / 2) {

    return KEEPSTATE;
  } else if (x <= 0) {
    return KEEPSTATE;
  } else if (y <= 0) {
    return KEEPSTATE;
  } else if (y >= height - 1) {
    return KEEPSTATE;
  }
  return PEOPLEMOVE;
}
int PeopleMoveCheckAtRightRoom(int x, int y, int width, int height) //check move of player
{
  if (x <= 0 &&
    y == height / 2) {
    return MIDDELROOM;
  } else if (x <= 0 &&
    y != height / 2) {

    return KEEPSTATE;
  } else if (x >= width - 1) {
    return KEEPSTATE;
  } else if (y <= 0) {
    return KEEPSTATE;
  } else if (y >= height - 1) {
    return KEEPSTATE;
  }
  return PEOPLEMOVE;
}
int PeopleMoveCheckAtUpRoom(int x, int y, int width, int height) //check move of player
{
  if (x == width / 2 &&
    y == height - 1) {
    return MIDDELROOM;
  } else if (x != width / 2 &&
    y >= height - 1) {
    return KEEPSTATE;
  } else if (x >= width - 1) {
    return KEEPSTATE;
  } else if (x <= 0) {
    return KEEPSTATE;
  } else if (y <= 0) {
    return KEEPSTATE;
  }
  return PEOPLEMOVE;
}
int PeopleMoveCheckAtDownRoom(int x, int y, int width, int height) //check move of player
{
  if (x == width / 2 &&
    y == 0) {
    return MIDDELROOM;
  } else if (x != width / 2 &&
    y <= 0) {
    return KEEPSTATE;
  } else if (x >= width - 1) {
    return KEEPSTATE;
  } else if (x <= 0) {
    return KEEPSTATE;
  } else if (y >= height - 1) {
    return KEEPSTATE;
  }
  return PEOPLEMOVE;
}
people PeopleMove(people mpeople, int room) //player move
{
  mvprintw(0, 81, "Operating Instructions:A:left  D:right");
  mvprintw(1, 104, "W:up    S:down");
  char ch = _getch();
  int tmpx = mpeople.x, tmpy = mpeople.y;
  if (ch == 'a') //Left
  {
    tmpx--;
  } else if (ch == 'd') {
    tmpx++;
  } else if (ch == 'w') {
    tmpy--;
  } else if (ch == 's') {
    tmpy++;
  }
  if (room == MIDDELROOM) {
    int n = PeopleMoveCheckAtMiddleRoom(tmpx, tmpy, roomwidth[MIDDELROOM], roomheight[MIDDELROOM]);
    if (n == PEOPLEMOVE) {
      mdraw[mpeople.y][mpeople.x] = ' ';
      mpeople.x = tmpx;
      mpeople.y = tmpy;
      //Fully filled
      mdraw[mpeople.y][mpeople.x] = '*';
      mpeople.step++;
      return mpeople;
    } else if (n == KEEPSTATE) {
      return mpeople;
    } else if (n < MIDDELROOM) {
      mdraw[mpeople.y][mpeople.x] = ' ';
      mpeople.x = tmpx;
      mpeople.y = tmpy;
      //Fully filled
      mdraw[mpeople.y][mpeople.x] = '*';
      mpeople.step++;
      mpeople.nowroom = n;
      return mpeople;
    }
  } else if (room == LEFTROOM) {
    int n = PeopleMoveCheckAtLeftRoom(tmpx, tmpy, roomwidth[LEFTROOM], roomheight[LEFTROOM]);
    if (n == PEOPLEMOVE) {
      mdraw[mpeople.y][mpeople.x] = ' ';
      mpeople.x = tmpx;
      mpeople.y = tmpy;
      //Fully filled
      mdraw[mpeople.y][mpeople.x] = '*';
      mpeople.step++;
      return mpeople;
    } else if (n == KEEPSTATE) {

      return mpeople;
    } else {
      mpeople.nowroom = n;
      return mpeople;
    }
  } else if (room == RIGHTROOM) {
    int n = PeopleMoveCheckAtRightRoom(tmpx, tmpy, roomwidth[RIGHTROOM], roomheight[RIGHTROOM]);
    if (n == PEOPLEMOVE) {
      mdraw[mpeople.y][mpeople.x] = ' ';
      mpeople.x = tmpx;
      mpeople.y = tmpy;
      //Fully filled
      mdraw[mpeople.y][mpeople.x] = '*';
      mpeople.step++;
      return mpeople;
    } else if (n == KEEPSTATE) {
      return mpeople;
    } else {
      mpeople.nowroom = n;
      return mpeople;
    }
  } else if (room == UPROOM) {
    int n = PeopleMoveCheckAtUpRoom(tmpx, tmpy, roomwidth[UPROOM], roomheight[UPROOM]);
    if (n == PEOPLEMOVE) {
      mdraw[mpeople.y][mpeople.x] = ' ';
      mpeople.x = tmpx;
      mpeople.y = tmpy;
      //Fully filled
      mdraw[mpeople.y][mpeople.x] = '*';
      mpeople.step++;
      return mpeople;
    } else if (n == KEEPSTATE) {

      return mpeople;

    } else {
      mpeople.nowroom = n;
      return mpeople;
    }
  } else if (room == DOWNROOM) {
    int n = PeopleMoveCheckAtDownRoom(tmpx, tmpy, roomwidth[DOWNROOM], roomheight[DOWNROOM]);
    if (n == PEOPLEMOVE) {
      mdraw[mpeople.y][mpeople.x] = ' ';
      mpeople.x = tmpx;
      mpeople.y = tmpy;
      //Fully filled
      mdraw[mpeople.y][mpeople.x] = '*';
      mpeople.step++;
      return mpeople;
    } else if (n == KEEPSTATE) {
      return mpeople;
    } else {
      mpeople.nowroom = n;
      return mpeople;
    }
  }
  return mpeople;
}
robot initFetid_Air(robot mrobot) //Initialize smell position
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (i == 0 || j == 0 || i == 2 || j == 2) {
        mrobot.fetid_air1[i * 3 + j].x = mrobot.x - 1 + i;
        mrobot.fetid_air1[i * 3 + j].y = mrobot.y - 1 + j;
      }
  for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++)
      if (i == 0 || j == 0 || j == 4 || i == 4) {
        mrobot.fetid_air2[i * 5 + j].x = mrobot.x - 2 + i;
        mrobot.fetid_air2[i * 5 + j].y = mrobot.y - 2 + j;
      }
  for (int i = 0; i < 7; i++)
    for (int j = 0; j < 7; j++)
      if (i == 0 || j == 0 || i == 6 || j == 6) {
        mrobot.fetid_air3[i * 7 + j].x = mrobot.x - 3 + i;
        mrobot.fetid_air3[i * 7 + j].y = mrobot.y - 3 + j;
      }
  return mrobot;
}
robot RobotMove(robot mrobot, int width, int height) //robot move
{
  int tmpx = mrobot.x, tmpy = mrobot.y; //set random point
  int direction = rand() % 4 + 0; //Generate random values
  if (direction == 0) //up
    tmpy--;
  else if (direction == 1) //left
    tmpx++;
  else if (direction == 2) //down
    tmpy++;
  else if (direction == 3) //right
    tmpx--;
  if (tmpx <= 0) {
    return mrobot;
  }
  if (tmpx >= width - 2) {
    return mrobot;
  }
  if (tmpy <= 0) {
    return mrobot;
  }
  if (tmpy >= height - 2) {
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

robot initrobot(int width, int height) //Initialize robot
{
  robot mrobot;
  //srand((unsigned int)time(NULL));//set random points
  int initnumx = rand() % (width - 1) + 1;
  int initnumy = rand() % (height - 1) + 1;
  mrobot.x = initnumx;
  mrobot.y = initnumy;
  mdraw[mrobot.y][mrobot.x] = '#';
  mrobot = initFetid_Air(mrobot);
  return mrobot;
}
people initpeople(robot * mrobot, int num, int width, int height) //Initialize player
{
  people mpeople;
  int initnumx, initnumy;
  while (1) {
    int flg = 0;
    srand((unsigned int) time(NULL)); //set random points
    initnumx = rand() % (width - 1) + 1;
    initnumy = rand() % (height - 1) + 1;
    for (int i = 0; i < num; i++) {
      if (mrobot[i].x == initnumx && mrobot[i].y == initnumy) {
        flg = 1;
        break;
      }
    }
    if (flg == 0) {
      mpeople.x = initnumx;
      mpeople.y = initnumy;
      mdraw[mpeople.y][mpeople.x] = '*';
      break;
    }
  }
  mpeople.Live_Value = 100; //blood value
  mpeople.step = 0;
  mpeople.nowroom = MIDDELROOM;
  return mpeople;
}
people changepeople(people mpeople, int preroomid) //Initialize player
{
  if (preroomid == LEFTROOM && mpeople.nowroom == MIDDELROOM) {
    mpeople.x = 1;
    mpeople.y = roomheight[mpeople.nowroom] / 2;
    return mpeople;
  } else if (preroomid == RIGHTROOM && mpeople.nowroom == MIDDELROOM) {
    mpeople.x = roomwidth[mpeople.nowroom] - 2;
    mpeople.y = roomheight[mpeople.nowroom] / 2;
    return mpeople;
  } else if (preroomid == UPROOM && mpeople.nowroom == MIDDELROOM) {
    mpeople.x = roomwidth[mpeople.nowroom] / 2;
    mpeople.y = 1;
    return mpeople;
  } else if (preroomid == DOWNROOM && mpeople.nowroom == MIDDELROOM) {
    mpeople.x = roomwidth[mpeople.nowroom] / 2;
    mpeople.y = roomheight[mpeople.nowroom] - 2;
    return mpeople;
  }
  if (preroomid == MIDDELROOM && mpeople.nowroom == LEFTROOM) {
    mpeople.x = roomwidth[mpeople.nowroom] - 2;
    mpeople.y = roomheight[mpeople.nowroom] / 2;
    return mpeople;
  } else if (preroomid == MIDDELROOM && mpeople.nowroom == RIGHTROOM) {
    mpeople.x = 1;
    mpeople.y = roomheight[mpeople.nowroom] / 2;
    return mpeople;
  } else if (preroomid == MIDDELROOM && mpeople.nowroom == UPROOM) {
    mpeople.x = roomwidth[mpeople.nowroom] / 2;
    mpeople.y = roomheight[mpeople.nowroom] - 2;
    return mpeople;
  } else if (preroomid == MIDDELROOM && mpeople.nowroom == DOWNROOM) {
    mpeople.x = roomwidth[mpeople.nowroom] / 2;
    mpeople.y = 1;
    return mpeople;
  }
  return mpeople;
}
void initDraw(int width, int height, int roomid) //Initialize wall
{
  if (roomid == LEFTROOM) {
    for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++) {
        if (j == width - 1 && i != height / 2)
          mdraw[i][j] = '|'; //wall
        else if (j == 0)
          mdraw[i][j] = '|';
        else if (i == height - 1)
          mdraw[i][j] = '-';
        else if (i == 0)
          mdraw[i][j] = '-';
        else mdraw[i][j] = ' ';
      }
  } else if (roomid == RIGHTROOM) {
    for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++) {
        if (j == 0 && i != height / 2)
          mdraw[i][j] = '|'; //wall
        else if (j == width - 1)
          mdraw[i][j] = '|';
        else if (i == height - 1)
          mdraw[i][j] = '-';
        else if (i == 0)
          mdraw[i][j] = '-';
        else mdraw[i][j] = ' ';
      }
  } else if (roomid == UPROOM) {
    for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++) {
        if (i == height - 1 && j != width / 2)
          mdraw[i][j] = '-'; //wall
        else if (j == 0)
          mdraw[i][j] = '|';
        else if (j == width - 1)
          mdraw[i][j] = '|';
        else if (i == 0)
          mdraw[i][j] = '-';
        else mdraw[i][j] = ' ';
      }
  } else if (roomid == DOWNROOM) {
    for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++) {
        if (i == 0 && j != width / 2)
          mdraw[i][j] = '-'; //wall
        else if (j == 0)
          mdraw[i][j] = '|';
        else if (j == width - 1)
          mdraw[i][j] = '|';
        else if (i == height - 1)
          mdraw[i][j] = '-';
        else mdraw[i][j] = ' ';
      }
  } else if (roomid == MIDDELROOM) {
    for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++) {
        if (i == 0 && j != width / 2) //wall
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
void Draw2(int width, int height) {
  init_pair(1, COLOR_BLACK, COLOR_GREEN);
  init_pair(5, COLOR_BLACK, COLOR_WHITE);
  init_pair(4, COLOR_BLACK, COLOR_RED);
  init_pair(6, COLOR_BLACK, COLOR_YELLOW);
  init_pair(16, COLOR_BLACK, COLOR_BLACK);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      {
        if (mdraw[i][j] == '#') //robot
        {
          attrset(COLOR_PAIR(5));
          mvprintw(i, j, "%c", mdraw[i][j]);
          refresh();
        } else if (mdraw[i][j] == '|') {
          attrset(COLOR_PAIR(1));
          mvprintw(i, j, "%c", mdraw[i][j]);
          refresh();
        } else if (mdraw[i][j] == '-') {
          attrset(COLOR_PAIR(1));
          mvprintw(i, j, "%c", mdraw[i][j]);
          refresh();
        } else if (mdraw[i][j] == '.') {
          attrset(COLOR_PAIR(5));
          mvprintw(i, j, "%c", mdraw[i][j]);
          refresh();
        } else {
          attrset(COLOR_PAIR(16));
          mvprintw(i, j, " "); //b
          refresh();
        }
      }
    }
  }
}
void run2() {
  initscr();
  people playpeople;
  int rscore = 0;
  robot mrobot[58];
  start_color(); //Initialize colour
  init_pair(2, COLOR_BLACK, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_YELLOW);
  int successdoor[2] = {
    0,
    0
  };
  int roomid = MIDDELROOM;
  for (int i = 1, j = 6; i <= 5; i++, j += 3) {
    initDraw(roomwidth[roomid], roomheight[roomid], roomid);
    srand((unsigned int) time(NULL)); //set random point
    for (int w = 0; w < j; w++) {
      mrobot[w] = initrobot(roomwidth[roomid], roomheight[roomid]);
    }
    playpeople = initpeople(mrobot, j, roomwidth[roomid], roomheight[roomid]);
    playpeople.level = i;
    int flg = 1;
    int sroomid = rand() % 4 + 0; //number of room have exit room
    int sdirect = rand() % 3 + 0; //position of exit door
    if (sroomid == LEFTROOM) {
      if (sdirect == 0) {
        successdoor[0] = roomwidth[sroomid] / 2;
        successdoor[1] = roomheight[sroomid] - 1;
      } else if (sdirect == 1) {
        successdoor[0] = 0;
        successdoor[1] = roomheight[sroomid] / 2;
      } else if (sdirect == 2) {
        successdoor[0] = roomwidth[sroomid] / 2;
        successdoor[1] = 0;
      }
    } else if (sroomid == UPROOM) {
      if (sdirect == 1) {
        successdoor[0] = roomwidth[sroomid] / 2;
        successdoor[1] = 0;
      } else if (sdirect == 0) {
        successdoor[0] = 0;
        successdoor[1] = roomheight[sroomid] / 2;
      } else if (sdirect == 2) {
        successdoor[0] = roomwidth[sroomid] - 1;
        successdoor[1] = roomheight[sroomid] / 2;
      }
    } else if (sroomid == RIGHTROOM) {
      if (sdirect == 0) {
        successdoor[0] = roomwidth[sroomid] / 2;
        successdoor[1] = 0;
      } else if (sdirect == 1) {
        successdoor[0] = roomwidth[sroomid] - 1;
        successdoor[1] = roomheight[sroomid] / 2;
      } else if (sdirect == 2) {
        successdoor[0] = roomwidth[sroomid] / 2;
        successdoor[1] = roomheight[sroomid] - 1;
      }
    } else if (sroomid == DOWNROOM) {
      if (sdirect == 2) {
        successdoor[0] = 0;
        successdoor[1] = roomheight[sroomid] / 2;
      } else if (sdirect == 0) {
        successdoor[0] = roomwidth[sroomid] - 1;
        successdoor[1] = roomheight[sroomid] / 2;
      } else if (sdirect == 1) {
        successdoor[0] = roomwidth[sroomid] / 2;
        successdoor[1] = roomheight[sroomid] - 1;
      }
    }
    while (flg) {
      playpeople = PeopleMove(playpeople, roomid);
      if (((playpeople.x == successdoor[0] - 1) || (playpeople.x == successdoor[0] + 1) ||
          (playpeople.x == successdoor[0] + 1)

        ) &&
        ((playpeople.y == successdoor[1] - 1) || (playpeople.y == successdoor[1] + 1) ||
          (playpeople.y == successdoor[1])) && playpeople.nowroom == sroomid) {
        if (playpeople.level >= i && playpeople.level <= 5) {
          rscore += playpeople.Live_Value + 10 * i;
          mvprintw(5, 81, "enter to level: %d\n", playpeople.level);
          mvprintw(6, 81, "score: %d\n", rscore);
          playpeople.level++;
          break;
        }
        if (playpeople.level > i && playpeople.level >= 5) {
          mvprintw(7, 81, "successful！\n");
          mvprintw(8, 81, "score：%d", rscore);
          flg = 0;
          break;
        }
      } else if (roomid != playpeople.nowroom) {
        playpeople = changepeople(playpeople, roomid);
        roomid = playpeople.nowroom;
        initDraw(roomwidth[roomid], roomheight[roomid], roomid);
        for (int w = 0; w < j; w++) {
          mrobot[w] = initrobot(roomwidth[roomid], roomheight[roomid]);
        }
      }
      Draw2(roomwidth[roomid], roomheight[roomid]);
      attron(COLOR_PAIR(3));
      mvprintw(playpeople.y, playpeople.x, "*");
      if (roomid == sroomid) {
        mvprintw(successdoor[1], successdoor[0], " ");
      }
      refresh();
      attron(COLOR_PAIR(2));
      mvprintw(3, 81, "blood: %d%\n", playpeople.Live_Value);
      refresh();
      attron(COLOR_PAIR(2));
      for (int w = 0; w < j; w++) {
        playpeople.Live_Value = changeLive_Value(playpeople.x, playpeople.y, playpeople.Live_Value, mrobot[w]);
        if (playpeople.Live_Value <= 0) {
          rscore += playpeople.Live_Value - playpeople.step;
          mvprintw(9, 81, "GAME OVER!\n");
          mvprintw(10, 81, "SCORE: %d", rscore);
          mvprintw(11, 81, "To enter the game, please press g; \n");
          mvprintw(12, 81, "To restart the game, press any keys.\n");
          roomid = MIDDELROOM;
          char ch = getch();
          if (ch == 'g') {
            exit(0);
          } else {
            i = -1;
            j = 0;
            playpeople.score = 0;
          }
          flg = 0;
          break;
        }
        fflush(stdin);
      }
      for (int w = 0; w < j; w++) {
        mrobot[w] = RobotMove(mrobot[w], roomwidth[roomid], roomheight[roomid]);
        if ((playpeople.x == mrobot[w].x && playpeople.y == mrobot[w].y) ||
          (playpeople.x == mrobot[w].x && playpeople.y == mrobot[w].y + 1) ||
          (playpeople.x == mrobot[w].x && playpeople.y == mrobot[w].y - 1) ||
          (playpeople.x == mrobot[w].x - 1 && playpeople.y == mrobot[w].y) ||
          (playpeople.x == mrobot[w].x + 1 && playpeople.y == mrobot[w].y) ||
          (playpeople.x == mrobot[w].x + 1 && playpeople.y == mrobot[w].y + 1) ||
          (playpeople.x == mrobot[w].x - 1 && playpeople.y == mrobot[w].y - 1) ||
          (playpeople.x == mrobot[w].x + 1 && playpeople.y == mrobot[w].y - 1) ||
          (playpeople.x == mrobot[w].x - 1 && playpeople.y == mrobot[w].y + 1)) {
          rscore += playpeople.Live_Value - playpeople.step;
          mvprintw(9, 81, "GAME OVER!\n");
          mvprintw(10, 81, "SCORE: %d", rscore);
          mvprintw(11, 81, "To enter the game, please press g; \n");
          mvprintw(12, 81, "To restart the game, press any keys.\n");
          roomid = MIDDELROOM;
          char ch = getch();
          if (ch == 'g') {
            exit(0);
          } else {
            i = -1;
            j = 0;
            playpeople.score = 0;
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
void menuscreen(){
    initscr();
    noecho();
    cbreak();
    
    // get screen size
    int yMax, xMax;
    getmaxyx (stdscr, yMax, xMax); // assigns max values of std screen to yMax and xMax

	char title[6][100] = {" _______           _____   _______  _____   ______   _____    _____  ",
                          "(_______)         (_____) (__ _ __)(_____) (______) (_____)  (_____) ", 
                          "   (_)    ______ (_)___      (_)   (_)__(_)(_)__   (_)___   (_)___   ", 
                          "   (_)   (______)  (___)_    (_)   (_____) (____)    (___)_   (___)_ ",       
                          " __(_)__           ____(_)   (_)   ( ) ( ) (_)____   ____(_)  ____(_)",
                          "(_______)         (_____)    (_)   (_)  (_)(______) (_____)  (_____) "};
    for (int i=0; i<=6; i++)
    {
        mvwprintw (stdscr, (yMax/3) - i, (xMax/2) - 35, title[6 - i]);
    };

    // creates window in middle of screen with height 6 and width 48
    WINDOW * menu = newwin(4, 48, (yMax/2) - 3, (xMax/2) - 24);
    box(menu, 4, 4); // puts box around window

    refresh();
    wrefresh(menu);

    //enables arrow keys for window
    keypad(menu, true);

    // array holding menu options
    char choices[2][12] = {"Start Game", "   Exit   "};
    int choice;
    int highlight = 0;

    while(1)
    {
        for (int i=0; i<3; i++) //prints menu
        {
            if (i == highlight) //starts highlighting first menu option
                wattron   (menu, A_REVERSE); //enables A_REVERSE for menu window
                mvwprintw (menu, i+1, 20, choices[i]); //prints menu options inside top and left border of menu window
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
                if (highlight == 2) //bottom of menu  
                    highlight = 1;
                break;
            case KEY_RIGHT:
                highlight++;
                if (highlight == 2) //bottom of menu  
                    highlight = 1;
                break;

            default: //other key pressed
                break;
        }
        if (choice == 10) //if enter pressed
        {
            refresh();
            if (highlight == 1){
				exit(0);
                return;
            }	else if (highlight == 0){
                gameflag = 1;
                clear();
                refresh();
                break;
            }
        }
    }
}

