#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "function.h"

extern struct playerinfo player[5];

// �÷��� ���� ��, ��� ���� �����ִ� ȭ��

void selectrandom() {
	system("cls");

	// ������ �÷��̾� �� * ���� �޿��� ����
	player[0].money = MONEY * nPlayer;
	player[0].sorttag = 3000000;

	int i;
	for (i = 1; i < nPlayer; i++) {
		// �÷��̾�� ���� �޿����� ����
		player[i].id = i;

		player[i].money = MONEY;

		player[i].credit = 6;
		player[i].tscore = 18;
		player[i].avgscore = player[i].tscore / player[i].credit;
	}

	for (i = 0; i < nPlayer; i++) {
		// ����� ǥ��

		gotoxy(12, i * 2 + 4);
		printf("Player %d : %s", i + 1, i == 0 ? "Professor" : "Student");
	}

	gotoxy(8, 15);
	printf("���� Ű�� ������ ������ �����մϴ�.");

	// ���Ͱ� �Էµ� ������ ���
	for (char c = 0;;) {
		c = getch();
		if (c == 10 || c == 13) { break; }
	}
}