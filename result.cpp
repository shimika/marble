#include "function.h"
#include <algorithm>
using namespace std;

extern struct playerinfo player[5];

/*	����ü ����

	SortTag�� 7�ڸ��� ����
	TNNNLLL

	�� ���ڸ��� ���� ���� T
	1 : �а�� ���� ����
	2 : ���������� ����
	3 : ���� �ڵ�
	4 : ������ ������ ������ �������� ����

	2~4�ڸ��� ���� 3�ڸ��� ���� ������ ����
	N.NN���� NNN���� ��ġ ��ȯ

	5~7�ڸ��� ���� 3�ڸ��� ���� ������ �� ���� ����
	LLL
*/
bool comp(playerinfo t1, playerinfo t2) {
	return t1.sorttag < t2.sorttag;
}

// ���� ��ũ�� ���� ���� ����
int rankcolor[4] = { GOLD, SILVER, BRONZE, GRAY };

void resultscreen() {
	system("cls");
	system("mode con cols=60 lines=25");

	// ����Ǿ������� �������� ���� �л����� ��Ʈ �±� �ο�
	int i;
	for (i = 0; i < nPlayer; i++) {
		if (player[i].sorttag == 0) {
			player[i].sorttag = 4000000 + (player[i].avgscore * 100);
		}
	}

	// ����ü ����
	sort(player, player + nPlayer, comp);

	gotoxy(6, 2);

	printf("===================  RESULT  ===================");

	for (i = 0; i < nPlayer; i++) {
		gotoxy(6, i * 2 + 4);
		settextcolor(rankcolor[i]);

		printf("%d�� Player %d (%s)", i + 1, player[i].id + 1, player[i].id == 0 ? "Professor" : "Student");
		if (player[i].id > 0) {
			printf(" (���� : %.2lf, ", player[i].avgscore);
			switch (player[i].sorttag / 1000000) {
				case 1:
					printf("�а�, ����)");
					break;
				case 2:
					printf("����)");
					break;
				case 4:
					printf("���� ��)");
					break;
			}
		}
	}

	settextcolor(WHITE);
	gotoxy(6, i * 2 + 6);
	printf("===============  �����ϼ̽��ϴ�  ===============");

	gotoxy(6, i * 2 + 8);

	getch();
}
