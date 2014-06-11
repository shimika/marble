#include "function.h"
using namespace std;

static int cursorpos;

void movecursor(int direction) {
	// 선택 커서를 움직이는 함수
	// Direction < 0 => 화살표를 위로
	// Direction > 0 => 화살표를 위로
	// Direction = 0 => 화살표를 그림 (처음에만 호출)
	
	// 새로운 커서 위치를 찾음
	cursorpos = max2(0, cursorpos + direction);
	cursorpos = min2(3, cursorpos);

	int i;
	for (i = 0; i < 4; i++) {
		gotoxy(8, i * 2 + 4);
		printf("  ");
	}

	// 커서 그리기
	gotoxy(8, cursorpos * 2 + 4);
	printf("▶");
}

// 타이틀 드로잉 함수
void printmenu() {
	int i;
	char menutitle[5][21] = { "2 players", "3 players", "4 players", "exit", "\'학고\'대의 마블" };

	for (i = 0; i < 4; i++) {
		gotoxy(12, i * 2 + 4);
		printf("%s", menutitle[i]);
	}

	gotoxy(12, 20);
	printf("%s", menutitle[4]);
}

// 타이틀을 그리고 선택을 받는 함수
void mainscreen() {
	system("mode con cols=50 lines=25");
	system("cls");
	cursorpos = 0;

	printmenu();
	movecursor(0);

	unsigned char key;
	while (1) {
		key = getch();

		if (key == 0 || key == 0xE0) {
			key = getch();
		}

		switch (key) {
			// Enter key
			case 13:
			case 10:
				// if player is 2 ~ 4 (pos 0 ~ 2)
				if (cursorpos <= 2) {
					nPlayer = cursorpos + 2;
					return;
				}
				else {
					exit(0);
				}
				break;

				// up arrow
			case 72:
				movecursor(-1);
				break;
				// down arrow
			case 80:
				movecursor(1);
				break;
		}
	}
}