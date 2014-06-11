#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <algorithm>
#include <string>
using namespace std;

#define max2(x, y)((x) > (y) ? (x) : (y))
#define min2(x, y)((x) < (y) ? (x) : (y))

#define WIDTH 9
#define HEIGHT 7
#define MAPSIZE 28

#define MONEYLOOP 40000
#define MONEY 150000
#define MAXCREDIT 15

#define MSGCOLOR 7
#define GREEN 10
#define CYAN 11
#define RED 12
#define PINK 13
#define YELLOW 14
#define WHITE 15


extern int nPlayer;
extern char subject[29][12];
extern int mapid[8][10];
extern pair<int, int> idmap[29];
extern int mapstatus[29];

struct playerinfo {
	int credit, money, passcount, loop, seminar;
	double tscore, avgscore;
	bool isrest, isfree;
};

void setwindowposition();
bool gotoxy(int x, int y);
void hidecursor();
void printscreen(char *str, int xi, int yi);
void settextcolor(int col);

void mainscreen();

void selectrandom();

void printgamescreen();

void shuffle();

void play();