#pragma once
#include<Windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")

inline void insertMove(int row, int column)
{
	//以下参考网上代码将光标移动 https://blog.csdn.net/qq_38241045/article/details/69941464
	HANDLE hout;
	COORD coord;
	coord.X = column;
	coord.Y = row;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hout, coord);
}