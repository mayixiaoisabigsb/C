#include<ctime>
#include<stdlib.h>
#include"setWindows.h"
#include"gameboard.h"

int main()
{
	setWindows();
	srand((unsigned)time(0));
	gameboard maingame;
	maingame.menu();
	return 0;
}