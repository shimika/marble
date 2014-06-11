#include "function.h"
#include <algorithm>
using namespace std;

extern struct playerinfo player[5];
bool comp(playerinfo t1, playerinfo t2) {
	return t1.sorttag < t2.sorttag;
}

int rankcolor[4] = { GOLD, SILVER, BRONZE, GRAY };

void resultscreen() {
	system("cls");
	system("mode con cols=60 lines=25");

	int i;
	for (i = 0; i < nPlayer; i++) {
		if (player[i].sorttag == 0) {
			player[i].sorttag = 4000000 + (player[i].avgscore * 100);
		}
	}

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
}
