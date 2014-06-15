#include "function.h"


// �� ĭ�� �׸��� �Լ�, name�� �̸�
void drawcell(int yi, int xi, char *name) {
	printscreen("������������\n��        ��\n��        ��\n��        ��\n������������\n", xi * 12 - 9, yi * 5 - 3);

	if (name[0] >= '1' && name[0] <= '3') {
		gotoxy(xi * 12 - 7, yi * 5 - 3);
		printf("%c", name[0]);
	}

	gotoxy(xi * 12 - 5, yi * 5 - 2);
	printf("%6s", name + 2);
}

/*	�ʿ� ���ؼ� ����� �迭
	
	0	: Ư�� ����
	1~3 : ���� ���� ���� ���� ��
	4	: ����
	5	: Ȳ�� ����
	6	: �޽�
	7	: ��Ʋ
*/
char subject[29][12] = { "00", "21��ǥ", "22����", "11�İ���", "41����", "51��", "12����", "31��ö", "61��",
						 "38����",																	"32�̼�",
						 "37������",																	"51��",
						 "36����",																	"01���̳�",
						 "51��",																		"23������",
						 "25��ȸ",																	"33����",
						 "71�߼�Ʋ", "25��ü", "51��", "14���Խ�", "35����", "24�ڱ�", "51��", "34�İ���", "13�ѱ���" };

int mapid[8][10];
pair<int, int> idmap[29];
// ���ڴ� �� 28ĭ

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

	// ���� ������ ���� O, ���� �Ұ��� ������ X

	settextcolor(13);
	for (i = 0; i < 28; i++) {
		if (mapstatus[i]) {
			gotoxy(idmap[i].second * 12 - 9, idmap[i].first * 5 - 2);
			printf(mapstatus[i] > 0 ? "A " : "��");
		}
	}
	settextcolor(15);

	for (int i = 1; i <= HEIGHT * 5; i++) {
		gotoxy(WIDTH * 13 - 2, i + 1);
		printf("|");
	}
}

// �� ����
void shuffle() {
	// �̸� ������ ��, ������ ���� ���ϴ� �� (�� 3, 2��)

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
