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

		printf("Player %d, %s : �ܾ� : %7d�� ", i + 1, i == 0 ? "����" : "�л�", player[i].money);
		if (i > 0) {
			printf(", �̼� ���� %3d , GPA %.2lf , ���̳� �Ϸ�%s", player[i].credit, player[i].avgscore, player[i].seminar ? "         " : "���� ����");
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
			sprintf(msg, "���� %d���� �޾ҽ��ϴ�.", MONEYLOOP * nPlayer);
		}
		else {
			sprintf(msg, "�뵷 %d���� �޾ҽ��ϴ�.", MONEYLOOP);
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
			printf("��");
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
	printf("��");

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
		printf("��");
	}

	return 0;
}

const int goldcnt = 5;
char goldmsg[21][64] = {
	"Ư�� ������ 10������ �����.",
	"�л����� ���̳� ������ ���� ��Ҵ�.",
	"������ ���� �߿� �ϳ��� ����� �÷ȴ�.",
	"��� �л����� A 3������ �־���.",
	"���ڱ� ���� �Ǿ���. �� ���� ����.",

	"���̳� ������� �����. ������ �ߴ�.",
	"������� �����.",
	"Ư�� �뵷�� 5���� �����.",
	"��ģ�� ������ 0.2 �������ȴ�. �ູ�ϴ�.",
	"���� ���� B, 10������ �þ���.",

	"���̳� ������� �������, �� ���� ������.",
	"��!",
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
		printf(" (%d����)", id);
	}

	switch (id) {
		case 0:
			// ������, ���̳�

			if (code % 10 == 0) {
				//
			}
			else if (pl == 0) {
				refreshmessage("�������� ���̳��� ���� �ʿ䰡 ����.", true);
			}
			else if (pl > 0 && code % 10 == 1 && player[pl].seminar == 0) {
				refreshmessage("���̳� ���� �Ϸ�.", true);
				player[pl].seminar = 1;
			}
			else {
				refreshmessage("�̹� ���̳��� �����Ͽ����ϴ�.", true);
			}

			break;
		case 1:
		case 2:
		case 3:
			// ���� (1 ~ 3����)

			if (player[pl].credit >= MAXCREDIT) {
				refreshmessage("���̳��� �� �Ǳ⿡ ���Ǵ� �н�", true);
				return;
			}

			if (pl == 0) {
				if (mapstatus[xi] > 0) {
					refreshmessage("�̹� ���ǰ� ������ �����Դϴ�.", true);
				}
				else if (mapstatus[xi] < 0) {
					refreshmessage("�� ������ ���Ǹ� ������ �� �����ϴ�.", true);
				}
				else if (player[pl].money < cost[2] * id) {
					refreshmessage("���Ǹ� ������ ���� �����մϴ�.", true);
				}
				else {
					vc.push_back("�������� ����");
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

						refreshmessage("���Ǹ� �����߽��ϴ�.", true);
					}
					else {
						refreshmessage("���Ǹ� �������� �ʾҽ��ϴ�.", true);
					}
				}
			}
			else {
				if (mapstatus[xi] > 0) {
					if (player[pl].passcount > 0) {
						vc.push_back("������� �ʴ´�");

						sprintf(msg, "����ϱ� (%d�� ����)", player[pl].passcount);
						vc.push_back(msg);

						option = moveoptioncursor(vc, 2);
					}

					if (option == 0) {
						switch (mapstatus[xi]) {
							case 1:
								refreshmessage("õ�� �������� �������ϴ�. ", true);
								settextcolor(CYAN);
								printf("A+");
								break;
							case 2:
								refreshmessage("�ܰ��ǿ����ϴ�. ", true);
								settextcolor(CYAN);
								printf("A");
								break;
							case 3:
								refreshmessage("�θ�Բ� ȥ������ ���� �� ���׿�. ", true);
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
						refreshmessage("������ ����߽��ϴ�.", true);
					}

					mapstatus[xi] = 0;
					refreshmapstatus(xi, 0);
				}
				else if (player[pl].money >= 20000) {
					vc.push_back("���� ��� (B ~ F ����, 2���� �Һ�)");
					vc.push_back("���� �ʴ´�");

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
								refreshmessage("������ �⼮�� ������ �� �߽��ϴ�. ", true);
								settextcolor(CYAN);
								printf("B");
								break;
							case 4:
								refreshmessage("���� �� ������ ������ �� �ȳ��Դ�. ", true);
								settextcolor(CYAN);
								printf("C+");
								break;
							case 5:
								refreshmessage("�����Ƽ� ��ü ���� ������ �߽��ϴ�. ", true);
								settextcolor(CYAN);
								printf("C");
								break;
							case 6:
								refreshmessage("�������ϴ�. ", true);
								settextcolor(CYAN);
								printf("D");
								break;
							case 7:
								refreshmessage("���� �����ϸ� ����. ", true);
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
						refreshmessage("���Ǹ� ���� �ʾҽ��ϴ�.", true);
					}
				}
				else {
					refreshmessage("���Ǹ� ��� �;�����, ���� �������ϴ�.", true);
				}
			}

			break;
		case 4:
			// ����
			
			if (player[pl].credit >= MAXCREDIT) {
				refreshmessage("���̳��� �� �Ǳ⿡ ���Ǵ� �н�", true);
				return;
			}

			refreshmessage("�����̴� ���ô�.", true);
			break;
		case 5:
			// Ư��]

			option = 1;
			if (pl == 0) {
				sprintf(msg, "���� ������ (+2~10����)");
				vc.push_back(msg);
			}
			else {
				sprintf(msg, "�Ƹ�����Ʈ (+1~5����)");
				vc.push_back(msg);
			}

			if (pl == 0 || player[pl].money >= 0) {
				vc.push_back("Ȳ�� ���� (��Ī)");
				option++;
			}

			option = moveoptioncursor(vc, option);

			if (option == 0) {
				option = rand() % 5 + 1;
				sprintf(msg, "%d������ ������ϴ�.", option);
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
			// �޽�

			if (player[pl].credit >= MAXCREDIT) {
				refreshmessage("���̳��� �� �Ǳ⿡ ���Ǵ� �н�", true);
				return;
			}

			player[pl].isrest = true;
			switch (pl) {
				case 0:
					refreshmessage("�Ƚĳ��Դϴ�. 1���� ���ϴ�.", true);
					break;
				default:
					refreshmessage("�����Դϴ�. 1���� ���ϴ�.", true);
					break;
			}
			break;
		case 7:
			// ��Ʋ
			move = max2(1, rand() % MAPSIZE);

			sprintf(msg, "��Ʋ ������ %dĭ �̵��մϴ�.", move);
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
	printf("Player %d (%s)", pl + 1, pl == 0 ? "����" : "�л�");
	if (pl>0) { printf(" [%.2lf]", player[pl].avgscore); }
	settextcolor(15);

	printnumber(0);

	refreshmessage("Space�� ���� �ֻ����� ��������... ");
	getchmacro(' ');

	num = ((rand() % 9) + 3) % 6 + 1;
	//num = 1;
	//printf("(%d)", num);
	printnumber(num);

	Sleep(500);
	movehorse(pl, num);

	selectaction(pl);
	refreshscore(pl);

	refreshmessage("Enter�� ���� ���� �����մϴ�.");
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
			refreshmessage("�޽� ��", true);
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
				sprintf(msg, "�а� �޾ҽ��ϴ�. �����մϴ�.");
			}
			else {
				sprintf(msg, "�����Ͽ����ϴ�. �����մϴ�. ���� : %.2lf", player[i].avgscore);
			}

			movehorse(i, 0);
			refreshmessage(msg, PINK);
			getchmacro(10);
		}
		if (i == 0 && player[i].loop >= 30) {
			refreshmessage("�������� 30������ �����Ͽ� ������ �����մϴ�.");
			getchmacro(10);
			break;
		}
	}

	system("cls");
	printf("��");
}
