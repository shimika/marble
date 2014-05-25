#ifndef FUNCTION_h
#define FUNCTION_h

#define max2(x, y)((x) > (y) ? (x) : (y))
#define min2(x, y)((x) < (y) ? (x) : (y))

extern int nPlayer;

bool gotoxy(int x, int y);

void mainscreen();
void hidecursor();

#endif