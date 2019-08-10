#include<iostream>
#include<iomanip>
#include"insertMove.h"
#include "DarknessBoard.h"
using namespace std;

void DarknessBoard::printDark()
{
	for (int i = 3; i < 23; ++i)
	{
		insertMove(i - 3, 18);
		for (int j = 1; j < 11; ++j)
		{
			bool flag = 0;
			for(int counter=0;counter<obj->getBottomnum();++counter)
				if (j == obj->getBC(counter))
				{
					flag = 1;
					break;
				}
			if (game[i][j] && flag)
				game[i][j]->show();
			else
				cout << "  ";
		}
	}
}

bool DarknessBoard::end()
{
	fix();
	unsigned short number = deleteLine();
	addScore(number);
	printOld();
	if (gameover())
		return 0;
	Sleep(100 + number * 200);
	return 1;
}

void DarknessBoard::print()
{
	if (obj)
	{
		insertMove(5, 6);
		cout << name << "\n\n    ";
		if (difficulty <= 5)
			cout << "简单  ";
		else
			if (difficulty <= 10)
				cout << "普通  ";
			else
				cout << "困难  ";
		cout << setw(2) << difficulty;
		insertMove(0, 0);
		for (int i = 3; i < 24; ++i)
		{
			cout << "\t\t";
			for (int j = 0; j < 12; ++j)
			{
				bool flag = 0;
				for (int counter = 0; counter < obj->getBottomnum(); ++counter)
					if (j == obj->getBC(counter))
					{
						flag = 1;
						break;
					}
				if (game[i][j] && (i == 23 || j == 0 || j == 11 || flag))
					game[i][j]->show();
				else
					cout << "  ";
			}
			if (i == 4)
				cout << "        下一个            下二个";
			if (i >= 6 && i <= 13)
			{
				cout << "    ";
				for (int j = 0; j < 7; ++j)
				{
					if (next[0][i - 6][j])
						next[0][i - 6][j]->show();
					else
						cout << "  ";
				}
				cout << "    ";
				for (int j = 0; j < 7; ++j)
				{
					if (next[1][i - 6][j])
						next[1][i - 6][j]->show();
					else
						cout << "  ";
				}
			}
			if (i == 15)
				cout << "                游戏玩法";
			if (i == 17)
				cout << "      A:向左移动        D:向右移动";
			if (i == 19)
				cout << "      W:顺时针转        S:加速下落";
			if (i == 21)
				cout << "      P:游戏暂停    space:直接落地";
			if (i == 23)
			{
				cout << "      消除行数:" << linenum;
				insertMove(20, 61);
				cout << "得分:" << score << endl;
			}
			cout << endl;
		}
	}
	else
		board::print();
}

void DarknessBoard::move(char direction, bool artificial)
{
	int i;
	switch (direction)
	{
	case 'w':case 'W':
	{
		if (mayMove('w'))
		{
			for (i = 0; i < 4; ++i)
			{
				delete[] game[obj->getR(i)][obj->getC(i)];
				game[obj->getR(i)][obj->getC(i)] = 0;
			}
			obj->turnAround();
			for (i = 0; i < 4; ++i)
				game[obj->getR(i)][obj->getC(i)] = new block(obj->getType());
		}
		printDark();
		return;
	}
	case 's':case'S':
	{
		if (mayMove('s'))
		{
			for (i = 0; i < 4; ++i)
			{
				delete[] game[obj->getR(i)][obj->getC(i)];
				game[obj->getR(i)][obj->getC(i)] = 0;
			}
			if (artificial)
			{
				score += (difficulty - 1) / 5 + 1;
				printScore();
			}
			obj->move('s');
			for (i = 0; i < 4; ++i)
				game[obj->getR(i)][obj->getC(i)] = new block(obj->getType());
		}
		return;
	}
	case 'a':case 'A':
	{
		if (mayMove('a'))
		{
			for (i = 0; i < 4; ++i)
			{
				delete[] game[obj->getR(i)][obj->getC(i)];
				game[obj->getR(i)][obj->getC(i)] = 0;
			}
			obj->move('a');
			for (i = 0; i < 4; ++i)
				game[obj->getR(i)][obj->getC(i)] = new block(obj->getType());
		}
		printDark();
		return;
	}
	case 'd':case 'D':
	{
		if (mayMove('d'))
		{
			for (i = 0; i < 4; ++i)
			{
				delete[] game[obj->getR(i)][obj->getC(i)];
				game[obj->getR(i)][obj->getC(i)] = 0;
			}
			obj->move('d');
			for (i = 0; i < 4; ++i)
				game[obj->getR(i)][obj->getC(i)] = new block(obj->getType());
		}
		printDark();
		return;
	}
	case ' ':
	{
		for (i = 0; i < 4; ++i)
		{
			delete[] game[obj->getR(i)][obj->getC(i)];
			game[obj->getR(i)][obj->getC(i)] = 0;
		}
		score += high()*((difficulty - 1) / 5 + 1) * 2;
		while (!inDanger())
			obj->move('s');
		for (i = 0; i < 4; ++i)
			game[obj->getR(i)][obj->getC(i)] = new block(obj->getType(), 0);
	}
	default:return;
	}
}

DarknessBoard::DarknessBoard() :board("黑暗")
{
}