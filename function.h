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

#define MONEYLOOP 60000
#define MONEY 120000
#define MAXCREDIT 120
#define MAXLOOP 12

#define BRONZE 6
#define MSGCOLOR 7
#define SILVER 7
#define GRAY 8
#define GREEN 10
#define CYAN 11
#define RED 12
#define PINK 13
#define YELLOW 14
#define GOLD 14
#define WHITE 15


extern int nPlayer;					// 플레이어 수
extern char subject[29][12];		// 과목의 코드와 이름
extern int mapid[8][10];			// 해당 맵에 대한 코드
extern pair<int, int> idmap[29];	// 코드에 대한 맵의 위치
extern int mapstatus[29];			// 그 맵에 부여된 학점의 스테이터스

struct playerinfo {
	int credit, money, passcount, loop;	// 각각 수강학점, 돈, 드랍권, 루프수
	int seminar;						// 세미나 (0 = 수강X, 1 = 수강완료, 2 = 대출 (취소될 수 있음))
	double tscore, avgscore;			// 총 환산 학점, GPA
	bool isrest;						// 현재 턴에 쉬는지
	int id, sorttag;					// 아이디와 소트 태그
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

void resultscreen();