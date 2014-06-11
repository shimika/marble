#include "function.h"
#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

int mapstatus[29];
int playerstatus[5];
struct playerinfo player[5];
int color[5] = { GREEN, CYAN, RED, YELLOW };

char scoreA[8] = { 'A', 'a', 'B', 'b', 'C', 'c', 'd', 'f' };
char scoreFull[8][3] = { "A+", "A", "B+", "B", "C+", "C", "D", "F" };
double scoreN[8] = { 4.5, 4.0, 3.5, 3.0, 2.5, 2.0, 1.0, 0 };
int cost[8] = { 80000, 50000, 30000, 20000, 20000, 20000, 20000, 20000 };

void printnumber(char *num) {
	int line = 0, len = strlen(num), i;
	gotoxy(WIDTH * 6 - 2, HEIGHT * 2);

	for (i = 0; i < len; i++) {
		if (num[i] == 10) {
			line++;
			gotoxy(WIDTH * 6 - 2, HEIGHT * 2 + line);
		}
		else {
			printf("%c", num[i]);
		}
	}
}

string numbers[7] = {
	"",
	"    ##      ####        ##        ##        ##        ##      ######  ",
	"  #######  ##     ##        ##  #######  ##        ##        #########",
	"  #######  ##     ##        ##  #######         ## ##     ##  ####### ",
	" ##        ##    ##  ##    ##  ##    ##  #########       ##        ## ",
	" ########  ##        ##        #######         ##  ##    ##   ######  ",
	"  #######  ##     ## ##        ########  ##     ## ##     ##  ####### ",
};

void printnumber(int num) {
	int i, j;
	static char numchar[7][72];
	static bool isload = false;
	
	if (!isload) {
		for (i = 1; i <= 6; i++) {
			sprintf(numchar[i], "%s", numbers[i].c_str());
		}
	}

	for (i = HEIGHT * 2 + 1; i < HEIGHT * 2 + 8; i++) {
		gotoxy(WIDTH * 6 - 2, i);
		printf("          ");
	}

	if (num > 0) {
		for (i = 0; i < 7; i++) {
			gotoxy(WIDTH * 6 - 2, HEIGHT * 2 + 1 + i);
			for (j = 0; j < 10; j++) {
				printf("%c", numchar[num][i * 10 + j]);
			}
		}
	}
}

void clearuserarea(int start = 1) {
	int i, j;
	char blank[44] = " ";
	for (i = 0; i <= 39; i++) {
		sprintf(blank, "%s ", blank);
	}
	for (i = start; i <= HEIGHT * 5; i++) {
		gotoxy(WIDTH * 13 + 2, i + 1);
		printf("%s", blank);
	}
}

void refreshscore(int pl) {
	int i, j;
	for (i = 0; i < nPlayer - 1; i++) {
		gotoxy(0, HEIGHT * 5 + i * 2 + 3);
		for (j = 1; j <= 10; j++) {
			printf("           ");
		}
	}

	// print student data
	for (i = 0; i < nPlayer; i++) {
		gotoxy(5, HEIGHT * 5 + i * 2 + 3);

		if (playerstatus[i]<0) {
			settextcolor(8);
		}
		else if (pl == i) {
			settextcolor(color[pl]);
		}

		printf("Player %d, %s : 잔액 : %7d원 ", i + 1, i == 0 ? "교수" : "학생", player[i].money);
		if (i > 0) {
			printf(", 이수 학점 %3d , GPA %.2lf , 세미나 완료%s", player[i].credit, player[i].avgscore, player[i].seminar ? "         " : "하지 않음");
		}
		settextcolor(15);
	}
}

void refreshmessage(char *msg, bool issub = false, int col = MSGCOLOR) {
	settextcolor(col);
	clearuserarea(HEIGHT * 5 - (issub ? 2 : 0) - 1);
	gotoxy(WIDTH * 13 + 2, HEIGHT * 5 - (issub ? 2 : 0));
	printf("%s", msg);
	settextcolor(15);
}

void getchmacro(int exception = 0) {
	char in1;
	for (;;) {
		in1 = getch();
		if (exception == 0) { break; }

		if (exception == 10) {
			if (in1 == 10 || in1 == 13) {
				break;
			}
		}
		else if (in1 == exception) {
			break;
		}
	}
}

void movehorse(int pl, int num) {
	settextcolor(color[pl]);

	int i, xi = playerstatus[pl];
	if (playerstatus[pl] >= 0) {
		gotoxy(idmap[xi].second * 12 - 7 + pl * 2, idmap[xi].first * 5);
		printf("%2d", pl + 1);
	}
	else {
		gotoxy(idmap[-xi].second * 12 - 7 + pl * 2, idmap[-xi].first * 5);
		printf("  ", pl + 1);
		return;
	}

	for (i = 1; i <= num; i++) {
		gotoxy(idmap[(xi + i - 1) % MAPSIZE].second * 12 - 7 + pl * 2, idmap[(xi + i - 1) % MAPSIZE].first * 5);
		printf("  ");

		if (playerstatus[pl] < 0) { continue; }

		gotoxy(idmap[(xi + i) % MAPSIZE].second * 12 - 7 + pl * 2, idmap[(xi + i) % MAPSIZE].first * 5);
		printf("%2d", pl + 1);

		Sleep(250);
	}

	settextcolor(15);
	playerstatus[pl] = (xi + num) % MAPSIZE;

	if (playerstatus[pl] < xi) {
		player[pl].loop++;
		if (pl == 0) {
			player[pl].money += MONEYLOOP * nPlayer;
		}
		else {
			player[pl].money += MONEYLOOP;
		}
		refreshscore(pl);

		char msg[59];
		if (pl == 0) {
			sprintf(msg, "월급 %d원을 받았습니다.", MONEYLOOP * nPlayer);
		}
		else {
			sprintf(msg, "용돈 %d원을 받았습니다.", MONEYLOOP);
		}
		refreshmessage(msg, true);
		getchmacro(10);
	}

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void refreshmapstatus(int xi, int make) {
	gotoxy(idmap[xi].second * 12 - 9, idmap[xi].first * 5 - 2);
	settextcolor(PINK);
	
	switch (make) {
		case 1:
			printf("A+");
			break;
		case 2:
			printf("A ");
			break;
		case 3:
			printf("B+");
			break;
		default:
			settextcolor(WHITE);
			printf("│");
			break;
	}

	settextcolor(WHITE);
}

int moveoptioncursor(vector<string> v, int selectcount) {
	int select = 0, i;
	char key;

	for (i = 0; i < v.size(); i++) {
		gotoxy(WIDTH * 13 + 4, HEIGHT + i * 2 + 2);
		printf("%s", v[i].c_str());
	}

	gotoxy(WIDTH * 13, HEIGHT + 2);
	printf("▶");

	while (1) {
		key = getch();

		if (key == 0 || key == 0xE0) {
			key = getch();
		}

		switch (key) {
			// Enter key
			case 13:
			case 10:
				return select;
			case 72:
				// up arrow
				select = max2(0, select - 1);
				break;
			case 80:
				// down arrow
				select = min2(selectcount - 1, select + 1);
				break;
		}

		for (i = 0; i < 5; i++) {
			gotoxy(WIDTH * 13, HEIGHT + i * 2 + 2);
			printf("  ");
		}

		gotoxy(WIDTH * 13, HEIGHT + select * 2 + 2);
		printf("▶");
	}

	return 0;
}

const int goldcnt = 5;
char goldmsg[21][64] = {
	"특별 성과급 10만원을 얻었다.",
	"학생들의 세미나 대출을 전부 잡았다.",
	"개설한 과목 중에 하나의 등급을 올렸다.",
	"모든 학생에게 A 3학점을 주었다.",
	"갑자기 쉬게 되었다. 한 턴을 쉰다.",

	"세미나 대출권을 얻었다. 대출을 했다.",
	"드랍권을 얻었다.",
	"특별 용돈을 5만원 얻었다.",
	"여친이 학점을 0.2 내려버렸다. 행복하다.",
	"학점 인정 B, 10학점이 늘었다.",

	"세미나 대출권을 얻었으나, 쓸 일이 없었다.",
	"꽝!",
};

void goldenkey(int pl) {
	int value = rand() % (goldcnt * 2);
	char a[99];
	sprintf(a, "%d (%d)", value, pl);

	//MessageBoxA(NULL, a, "", 0);
	if ((pl == 0 && value / goldcnt == 1) || (pl > 0 && value / goldcnt == 0)) {
		value = goldcnt * 2 + 1;
	}

	int i;

	switch (value) {
		case 0:
			player[pl].money += 100000;
			break;
		case 1:
			for (i = 1; i < nPlayer; i++) {
				if (player[i].seminar == 2) {
					player[i].seminar = 0;
				}
			}
			break;
		case 2:
			for (i = 0; i < MAPSIZE; i++) {
				if (mapstatus[i] > 1) {
					mapstatus[i]--;
					refreshmapstatus(i, mapstatus[i]);
					break;
				}
			}
			break;
		case 3:
			for (i = 1; nPlayer; i++) {
				player[pl].tscore += 12;
				player[pl].credit += 3;
				player[pl].avgscore = player[pl].tscore / player[pl].credit;
			}
			break;
		case 4:
			player[pl].isrest = true;
			break;
		case 5:
			if (player[pl].seminar > 0) {
				value = goldcnt * 2;
			}
			else {
				player[pl].seminar = 2;
			}
			break;
		case 6:
			player[pl].passcount++;
			break;
		case 7:
			player[pl].money += 50000;
			break;
		case 8:
			if (player[pl].avgscore >= 0.2) {
				player[pl].tscore -= player[pl].credit * 0.2;
				player[pl].avgscore = player[pl].tscore / player[pl].credit;
			}
			break;
		case 9:
			player[pl].tscore += 30;
			player[pl].credit += 10;
			player[pl].avgscore = player[pl].tscore / player[pl].credit;
			break;
	}

	refreshmessage(goldmsg[value], true, CYAN);
}

void selectaction(int pl) {
	refreshmessage("");

	int xi = playerstatus[pl];
	int options[6], i;

	int code = (subject[xi][0] - '0') * 10 + subject[xi][1] - '0';
	int id = code / 10;
	int move = 0, option = 0, value;
	char msg[69];
	vector<string> vc;

	gotoxy(WIDTH * 13 + 2, 5);
	printf("%s", subject[xi] + 2);
	if (id >= 1 && id <= 3) {
		printf(" (%d학점)", id);
	}

	switch (id) {
		case 0:
			// 시작점, 세미나

			if (code % 10 == 0) {
				//
			}
			else if (pl == 0) {
				refreshmessage("교수님은 세미나를 들을 필요가 없죠.", true);
			}
			else if (pl > 0 && code % 10 == 1 && player[pl].seminar == 0) {
				refreshmessage("세미나 수강 완료.", true);
				player[pl].seminar = 1;
			}
			else {
				refreshmessage("이미 세미나를 수강하였습니다.", true);
			}

			break;
		case 1:
		case 2:
		case 3:
			// 강의 (1 ~ 3학점)

			if (player[pl].credit >= MAXCREDIT) {
				refreshmessage("세미나만 들어도 되기에 강의는 패스", true);
				return;
			}

			if (pl == 0) {
				if (mapstatus[xi] > 0) {
					refreshmessage("이미 강의가 개설된 과목입니다.", true);
				}
				else if (mapstatus[xi] < 0) {
					refreshmessage("이 과목은 강의를 개설할 수 없습니다.", true);
				}
				else if (player[pl].money < cost[2] * id) {
					refreshmessage("강의를 개설할 돈이 부족합니다.", true);
				}
				else {
					vc.push_back("개설하지 않음");
					options[option++] = 0;

					for (i = 0; i < 3; i++) {
						if (player[pl].money >= cost[i] * id) {
							sprintf(msg, "%-2s (%d)", scoreFull[i], cost[i] * id);
							vc.push_back(msg);

							options[option++] = cost[i] * id;
						}
					}

					value = moveoptioncursor(vc, option);
					
					if (value > 0) {
						switch (option) {
							case 3:
								value++;
								break;
							case 2:
								value++;
								break;
						}

						player[pl].money -= options[value];
						mapstatus[xi] = value;
						refreshmapstatus(xi, value);

						refreshmessage("강의를 개설했습니다.", true);
					}
					else {
						refreshmessage("강의를 개설하지 않았습니다.", true);
					}
				}
			}
			else {
				if (mapstatus[xi] > 0) {
					if (player[pl].passcount > 0) {
						vc.push_back("드랍하지 않는다");

						sprintf(msg, "드랍하기 (%d번 남음)", player[pl].passcount);
						vc.push_back(msg);

						option = moveoptioncursor(vc, 2);
					}

					if (option == 0) {
						switch (mapstatus[xi]) {
							case 1:
								refreshmessage("천사 교수님을 만났습니다. ", true);
								settextcolor(CYAN);
								printf("A+");
								break;
							case 2:
								refreshmessage("꿀강의였습니다. ", true);
								settextcolor(CYAN);
								printf("A");
								break;
							case 3:
								refreshmessage("부모님께 혼나지는 않을 것 같네요. ", true);
								settextcolor(CYAN);
								printf("B+");
								break;
						}

						settextcolor(WHITE);

						player[pl].credit += id;
						player[pl].tscore += scoreN[mapstatus[xi] - 1] * id;
						player[pl].avgscore = player[pl].tscore / player[pl].credit;

						player[pl].money -= cost[mapstatus[xi] - 1];

						player[0].money += (cost[mapstatus[xi] - 1] * 3) / 10;
					}
					else {
						player[pl].passcount--;
						refreshmessage("과목을 드랍했습니다.", true);
					}

					mapstatus[xi] = 0;
					refreshmapstatus(xi, 0);
				}
				else if (player[pl].money >= 20000) {
					vc.push_back("강의 듣기 (B ~ F 랜덤, 2만원 소비)");
					vc.push_back("듣지 않는다");

					option = moveoptioncursor(vc, 2);

					if (option == 0) {
						int randscore = rand() % 11;

						switch (randscore) {
							case 0:
								randscore = 7;
								break;
							case 1:
							case 2:
								randscore = 6;
								break;
							case 3:
							case 4:
								randscore = 5;
								break;
							case 5:
							case 6:
							case 7:
								randscore = 4;
								break;
							case 8:
							case 9:
							case 10:
								randscore = 3;
								break;
						}

						switch (randscore) {
							case 3:
								refreshmessage("적당히 출석과 과제를 잘 했습니다. ", true);
								settextcolor(CYAN);
								printf("B");
								break;
							case 4:
								refreshmessage("잘한 것 같은데 점수가 잘 안나왔다. ", true);
								settextcolor(CYAN);
								printf("C+");
								break;
							case 5:
								refreshmessage("귀찮아서 자체 조기 종강을 했습니다. ", true);
								settextcolor(CYAN);
								printf("C");
								break;
							case 6:
								refreshmessage("던졌습니다. ", true);
								settextcolor(CYAN);
								printf("D");
								break;
							case 7:
								refreshmessage("학점 포기하면 되죠. ", true);
								settextcolor(CYAN);
								printf("F");
								break;
						}

						settextcolor(WHITE);

						player[pl].credit += id;
						player[pl].tscore += scoreN[randscore] * id;
						player[pl].money -= 20000;

						player[pl].avgscore = player[pl].tscore / player[pl].credit;
					}
					else {
						refreshmessage("강의를 듣지 않았습니다.", true);
					}
				}
				else {
					refreshmessage("강의를 듣고 싶었으나, 돈이 없었습니다.", true);
				}
			}

			break;
		case 4:
			// 공강
			
			if (player[pl].credit >= MAXCREDIT) {
				refreshmessage("세미나만 들어도 되기에 강의는 패스", true);
				return;
			}

			refreshmessage("공강이니 쉽시다.", true);
			break;
		case 5:
			// 특별]

			option = 1;
			if (pl == 0) {
				sprintf(msg, "연구 지원비 (+2~10만원)");
				vc.push_back(msg);
			}
			else {
				sprintf(msg, "아르바이트 (+1~5만원)");
				vc.push_back(msg);
			}

			if (pl == 0 || player[pl].money >= 0) {
				vc.push_back("황금 열쇠 (가칭)");
				option++;
			}

			option = moveoptioncursor(vc, option);

			if (option == 0) {
				option = rand() % 5 + 1;
				sprintf(msg, "%d만원을 얻었습니다.", option);
				refreshmessage(msg, true);

				if (pl == 0) {
					player[pl].money += 20000 * option;
				}
				else {
					player[pl].money += 10000 * option;
				}
			}
			else {
				// Golden key
				goldenkey(pl);
			}

			break;
		case 6:
			// 휴식

			if (player[pl].credit >= MAXCREDIT) {
				refreshmessage("세미나만 들어도 되기에 강의는 패스", true);
				return;
			}

			player[pl].isrest = true;
			switch (pl) {
				case 0:
					refreshmessage("안식년입니다. 1턴을 쉽니다.", true);
					break;
				default:
					refreshmessage("방학입니다. 1턴을 쉽니다.", true);
					break;
			}
			break;
		case 7:
			// 셔틀
			move = max2(1, rand() % MAPSIZE);

			sprintf(msg, "셔틀 버스로 %d칸 이동합니다.", move);
			refreshmessage(msg, true);
			movehorse(pl, move);

			selectaction(pl);
			return;

			break;
	}
}

void gameturn(int pl) {
	char in1, in2;
	int num = -1, i;

	clearuserarea();

	for (i = 0; i < nPlayer; i++) {
		movehorse(i, 0);
	}

	for (i = 0; i < 5; i++) {
		gotoxy(WIDTH * 13, HEIGHT + i * 2 + 2);
		printf("  ");
	}

	gotoxy(WIDTH * 13 + 2, 3);

	settextcolor(color[pl]);
	printf("Player %d (%s)", pl + 1, pl == 0 ? "교수" : "학생");
	if (pl>0) { printf(" [%.2lf]", player[pl].avgscore); }
	settextcolor(15);

	printnumber(0);

	refreshmessage("Space를 눌러 주사위를 굴리세요... ");
	getchmacro(' ');

	num = ((rand() % 9) + 3) % 6 + 1;
	//num = 1;
	//printf("(%d)", num);
	printnumber(num);

	Sleep(500);
	movehorse(pl, num);

	selectaction(pl);
	refreshscore(pl);

	refreshmessage("Enter를 눌러 턴을 종료합니다.");
	getchmacro(10);
}

void play() {
	int live = nPlayer - 1, i;
	char msg[99];

	for (i = 0; i < nPlayer; i++) {
		movehorse(i, 0);
	}

	for (i = 0; live; i = (i + 1) % nPlayer) {
		if (playerstatus[i] < 0) { continue; }

		if (player[i].isrest) {
			refreshmessage("휴식 끝", true);
			player[i].isrest = false;
			getchmacro();

			continue;
		}

		refreshscore(i);
		gameturn(i);

		if (((player[i].credit >= MAXCREDIT  && player[i].seminar > 0) || player[i].avgscore <= 1.75) && i > 0) {
			playerstatus[i] *= -1;
			live--;

			if (player[i].avgscore <= 1.75) {
				sprintf(msg, "학고를 받았습니다. 축하합니다.");
			}
			else {
				sprintf(msg, "졸업하였습니다. 축하합니다. 학점 : %.2lf", player[i].avgscore);
			}

			movehorse(i, 0);
			refreshmessage(msg, PINK);
			getchmacro(10);
		}
		if (i == 0 && player[i].loop >= 30) {
			refreshmessage("교수님이 30바퀴를 돌파하여 게임을 종료합니다.");
			getchmacro(10);
			break;
		}
	}

	system("cls");
	printf("끝");
}
