#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "function.h"

extern struct playerinfo player[5];

// 플레이 시작 전, 사람 수를 보여주는 화면

void selectrandom() {
	system("cls");

	// 교수는 플레이어 수 * 기초 급여를 지급
	player[0].money = MONEY * nPlayer;

	int i;
	for (i = 1; i < nPlayer; i++) {
		// 플레이어는 기초 급여만을 지급
		player[i].money = MONEY;

		player[i].credit = 5;
		player[i].tscore = 15;
		player[i].avgscore = player[i].tscore / player[i].credit;
	}

	for (i = 0; i < nPlayer; i++) {
		// 사람을 표시

		gotoxy(12, i * 2 + 4);
		printf("Player %d : %s", i + 1, i == 0 ? "Professor" : "Student");
	}

	gotoxy(8, 15);
	printf("엔터 키를 누르면 게임을 시작합니다.");

	// 엔터가 입력될 때까지 대기
	for (char c = 0;;) {
		c = getch();
		if (c == 10 || c == 13) { break; }
	}
}
