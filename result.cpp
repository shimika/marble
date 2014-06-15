#include "function.h"
#include <algorithm>
using namespace std;

extern struct playerinfo player[5];

/*	구조체 정렬

	SortTag는 7자리로 구성
	TNNNLLL

	맨 앞자리는 종료 조건 T
	1 : 학고로 인해 중퇴
	2 : 정상적으로 졸업
	3 : 교수 코드
	4 : 교수가 퇴임할 때까지 졸업하지 못함

	2~4자리의 숫자 3자리는 종료 시점의 학점
	N.NN점을 NNN으로 수치 변환

	5~7자리의 숫자 3자리는 종료 시점의 턴 수를 측정
	LLL
*/
bool comp(playerinfo t1, playerinfo t2) {
	return t1.sorttag < t2.sorttag;
}

// 각각 랭크에 대한 색을 정의
int rankcolor[4] = { GOLD, SILVER, BRONZE, GRAY };

void resultscreen() {
	system("cls");
	system("mode con cols=60 lines=25");

	// 종료되었음에도 졸업하지 못한 학생에게 소트 태그 부여
	int i;
	for (i = 0; i < nPlayer; i++) {
		if (player[i].sorttag == 0) {
			player[i].sorttag = 4000000 + (player[i].avgscore * 100);
		}
	}

	// 구조체 정렬
	sort(player, player + nPlayer, comp);

	gotoxy(6, 2);

	printf("===================  RESULT  ===================");

	for (i = 0; i < nPlayer; i++) {
		gotoxy(6, i * 2 + 4);
		settextcolor(rankcolor[i]);

		printf("%d위 Player %d (%s)", i + 1, player[i].id + 1, player[i].id == 0 ? "Professor" : "Student");
		if (player[i].id > 0) {
			printf(" (학점 : %.2lf, ", player[i].avgscore);
			switch (player[i].sorttag / 1000000) {
				case 1:
					printf("학고, 중퇴)");
					break;
				case 2:
					printf("졸업)");
					break;
				case 4:
					printf("재학 중)");
					break;
			}
		}
	}

	settextcolor(WHITE);
	gotoxy(6, i * 2 + 6);
	printf("===============  수고하셨습니다  ===============");

	gotoxy(6, i * 2 + 8);

	getch();
}
