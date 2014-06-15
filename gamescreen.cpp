#include "function.h"


// 각 칸을 그리는 함수, name은 이름
void drawcell(int yi, int xi, char *name) {
	printscreen("┌────┐\n│        │\n│        │\n│        │\n└────┘\n", xi * 12 - 9, yi * 5 - 3);

	if (name[0] >= '1' && name[0] <= '3') {
		gotoxy(xi * 12 - 7, yi * 5 - 3);
		printf("%c", name[0]);
	}

	gotoxy(xi * 12 - 5, yi * 5 - 2);
	printf("%6s", name + 2);
}

/*	맵에 대해서 저장된 배열
	
	0	: 특수 지형
	1~3 : 각각 과목에 대한 학점 수
	4	: 공강
	5	: 황금 열쇠
	6	: 휴식
	7	: 셔틀
*/
char subject[29][12] = { "00", "21사표", "22아잉", "11컴과실", "41공강", "51★", "12물실", "31서철", "61♣",
						 "38물연",																	"32이수",
						 "37지리학",																	"51★",
						 "36공수",																	"01세미나",
						 "51★",																		"23정과개",
						 "25논회",																	"33미적",
						 "71◆셔틀", "25운체", "51★", "14인입실", "35선대", "24자구", "51★", "34컴과연", "13한국사" };

int mapid[8][10];
pair<int, int> idmap[29];
// 격자는 총 28칸

void printgamescreen() {
	system("mode con cols=160 lines=47");
	system("cls");

	shuffle();

	int i, j, cnt = 0, id;

	for (i = 1; i <= WIDTH; i++) {
		mapid[1][i] = cnt;
		idmap[cnt] = make_pair(1, i);
		drawcell(1, i, subject[cnt++]);
	}

	for (i = 2; i < HEIGHT; i++) {
		mapid[i][WIDTH] = cnt;
		idmap[cnt] = make_pair(i, WIDTH);
		drawcell(i, WIDTH, subject[cnt++]);
	}

	for (i = WIDTH; i >= 1; i--) {
		mapid[HEIGHT][i] = cnt;
		idmap[cnt] = make_pair(HEIGHT, i);
		drawcell(HEIGHT, i, subject[cnt++]);
	}

	for (i = HEIGHT - 1; i > 1; i--) {
		mapid[i][1] = cnt;
		idmap[cnt] = make_pair(i, 1);
		drawcell(i, 1, subject[cnt++]);
	}

	// 최초 개설된 곳은 O, 개설 불가능 구역은 X

	settextcolor(13);
	for (i = 0; i < 28; i++) {
		if (mapstatus[i]) {
			gotoxy(idmap[i].second * 12 - 9, idmap[i].first * 5 - 2);
			printf(mapstatus[i] > 0 ? "A " : "×");
		}
	}
	settextcolor(15);

	for (int i = 1; i <= HEIGHT * 5; i++) {
		gotoxy(WIDTH * 13 - 2, i + 1);
		printf("|");
	}
}

// 맵 섞기
void shuffle() {
	// 미리 개설된 곳, 개설을 하지 못하는 곳 (각 3, 2개)

	int shufflecount = rand() % 10 + 10;
	int t1, t2;

	while (shufflecount-- > 0) {
		t1 = rand() % 27 + 1;
		t2 = rand() % 27 + 1;

		swap(subject[t1], subject[t2]);
	}

	int i, val;
	for (i = 1; i <= 5; i++) {
		val = rand() % 28;
		if (subject[val][0] >= '1' && subject[val][0] <= '3' && !mapstatus[val]) {
			mapstatus[val] = i % 2 ? 2 : -1;
		}
		else {
			i--;
		}
	}
}
