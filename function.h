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


extern int nPlayer;					// �÷��̾� ��
extern char subject[29][12];		// ������ �ڵ�� �̸�
extern int mapid[8][10];			// �ش� �ʿ� ���� �ڵ�
extern pair<int, int> idmap[29];	// �ڵ忡 ���� ���� ��ġ
extern int mapstatus[29];			// �� �ʿ� �ο��� ������ �������ͽ�

struct playerinfo {
	int credit, money, passcount, loop;	// ���� ��������, ��, �����, ������
	int seminar;						// ���̳� (0 = ����X, 1 = �����Ϸ�, 2 = ���� (��ҵ� �� ����))
	double tscore, avgscore;			// �� ȯ�� ����, GPA
	bool isrest;						// ���� �Ͽ� ������
	int id, sorttag;					// ���̵�� ��Ʈ �±�
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