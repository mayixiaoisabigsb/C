#pragma once
#include<Windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")

inline void insertMove(int row, int column)
{
	//���²ο����ϴ��뽫����ƶ� https://blog.csdn.net/qq_38241045/article/details/69941464
	HANDLE hout;
	COORD coord;
	coord.X = column;
	coord.Y = row;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
}