#include<conio.h>
#include<iostream>
#include<iomanip>
#include"insertMove.h"
#include "LaserBoard.h"
using namespace std;

void LaserBoard::printOld()
{
	board::printOld();
	laserPrint(1);
}

bool LaserBoard::end()
{
	fix();
	unsigned short line = deleteLine();
	addScore(line);
	laserHigh -= line * (3 + (difficulty - 1) / 5) + 1;
	laserHigh = laserHigh > 3 ? laserHigh : 3;
	laserPrint(1);
	if (gameover())
		return 0;
	if (laserHigh >= top())
	{
		unsigned short endTop = top();
		for (int i = laserHigh; i >= endTop; --i)
			for (int j = 1; j < 11; ++j)
				if (game[i][j])
				{
					insertMove(i - 3, 16 + 2 * j);
					switch (blockstyle)
					{
					case COLORFUL:case COLORLESS:
					{
						if (bigBlock)
							cout << "¨€";
						else
							cout << "¡ö";
					}break;
					case CLASSIC:cout << "àí"; break;
					}
				}
		Sleep(1000);
		return 0;
	}
	return 1;
}

void LaserBoard::down()
{
	static unsigned clocker = 0;
	move('s', 0);
	if (clocker++ >= ((difficulty - 1u) / 5u + 1u) * 3u)
	{
		if (laserHigh < 22)
			++laserHigh;
		clocker = 0;
	}
	laserPrint();
}

void LaserBoard::betterPrint()
{
	insertMove(0, 0);
	print();
	laserPrint(1);
}

void LaserBoard::printNewOnly()
{
	int i;
	for (i = obj->getR(0) - 3; i <= obj->getR(0) + 4; ++i)
	{
		if (i > 2 && i < 23)
		{
			for (int j = obj->getC(0) - 3; j <= obj->getC(0) + 4; ++j)
			{
				if (j > 0 && j < 11)
				{
					bool flag = 1;
					insertMove(i - 3, 16 + 2 * j);
					for (int k = 0; k < 4; ++k)
						if (shadow[k][ROW] == i && shadow[k][COLUMN] == j)
							flag = 0;
					if (!game[i][j] && flag)
						if (i == laserHigh)
							cout << "--";
						else
							cout << "  ";
				}
			}
		}
	}
	for (i = 0; i < 4; ++i)
	{
		if (obj->getR(i) > 2)
		{
			insertMove(obj->getR(i) - 3, 16 + 2 * obj->getC(i));
			game[obj->getR(i)][obj->getC(i)]->show();
		}
	}
	insertMove(22, 0);
}

void LaserBoard::printShadow()
{
	board::printShadow();
	laserPrint(1);
}

void LaserBoard::laserPrint(bool force)
{
	static short lastLaser = 0;
	if (lastLaser != laserHigh || force)
	{
		int i;
		if (lastLaser)
		{
			for (i = 1; i < 11; ++i)
				if (!game[lastLaser][i])
				{
					insertMove(lastLaser - 3, 16 + i * 2);
					cout << "  ";
				}
			if (!force&&shadowShow)
				board::printShadow();
		}
		for (i = 1; i < 11; ++i)
			if (!game[laserHigh][i])
			{
				insertMove(laserHigh - 3, 16 + i * 2);
				cout << "--";
			}
		lastLaser = laserHigh;
	}
}

LaserBoard::LaserBoard() :board("¼¤¹â"), laserHigh(3 + (difficulty - 1) / 5)
{
}