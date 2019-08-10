#include<iostream>
#include<iomanip>
#include"insertMove.h"
#include "FrozenBoard.h"
using namespace std;

bool FrozenBoard::fall()
{
	bool change = 0;
	unsigned target[200][4][2] = { 0 }, group[200][2] = { 0 }, groupnumber = 0, i, j;
	for (i = 22; i > 0; --i)
		for (j = 1; j < 11; ++j)
			if (game[i][j] && game[i][j]->sign2 != 2)
			{
				bool flag = 1;
				for (unsigned count = 0; count < groupnumber; ++count)
					if (game[i][j]->sign == group[count][0])
					{
						flag = 0;
						break;
					}
				if (flag)
					group[groupnumber++][0] = game[i][j]->sign;
				target[game[i][j]->sign][member(group, game[i][j]->sign)][ROW] = i;
				target[game[i][j]->sign][member(group, game[i][j]->sign)++][COLUMN] = j;
			}
	for (i = 0; i < groupnumber; ++i)
	{
		unsigned short minihigh = 23, tempHigh;
		for (j = 0; j < member(group, group[i][0]); ++j)
		{
			tempHigh = blockHigh(target[group[i][0]][j][ROW], target[group[i][0]][j][COLUMN]);
			minihigh = minihigh < tempHigh ? minihigh : tempHigh;
		}
		if (minihigh)
			change = 1;
		for (j = 0; j < member(group, group[i][0]); ++j)
		{
			block *temp = game[target[group[i][0]][j][ROW]][target[group[i][0]][j][COLUMN]];
			game[target[group[i][0]][j][ROW]][target[group[i][0]][j][COLUMN]] = 0;
			game[target[group[i][0]][j][ROW] + minihigh][target[group[i][0]][j][COLUMN]] = temp;
		}
	}
	return change;
}

void FrozenBoard::froze()
{
	for (int i = 1; i < 23; ++i)
		for (int j = 1; j < 11; ++j)
			if (game[i][j])
				switch (game[i][j]->sign2)
				{
				case 0:game[i][j]->sign2 = 1; break;
				case 1:
				{
					game[i][j]->sign = supply();
					game[i][j]->sign2 = 2;
				}break;
				case 2: break;
				}
}

void FrozenBoard::printBlock(unsigned short row, unsigned short column)
{
	if (game[row][column])
	{
		if (game[row][column]->getType() != BORDER)
		{
			switch (blockstyle)
			{
			case COLORFUL:case COLORLESS:
			{
				switch (game[row][column]->sign2)
				{
				case 0:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); break;
				case 1:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN); break;
				case 2:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); break;
				}
				if (bigBlock)
					cout << "█";
				else
					cout << "■";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}break;
			case CLASSIC:
			{
				switch (game[row][column]->sign2)
				{
				case 0:cout << "囲"; break;
				case 1:cout << "囚"; break;
				case 2:cout << "囗"; break;
				}
			}break;
			}
		}
		else
			game[row][column]->show();
	}
	else
		cout << "  ";
}

void FrozenBoard::printBlock(block *target)
{
	if (target)
	{
		if (target->getType() != BORDER)
		{
			switch (blockstyle)
			{
			case COLORFUL:case COLORLESS:
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				if (bigBlock)
					cout << "█";
				else
					cout << "■";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}break;
			case CLASSIC:cout << "囲"; break;
			}
		}
		else
			target->show();
	}
	else
		cout << "  ";
}

void FrozenBoard::printOld()
{
	for (int i = 3; i < 23; ++i)
	{
		insertMove(i - 3, 18);
		for (int j = 1; j < 11; ++j)
			printBlock(i, j);
	}
}

unsigned short FrozenBoard::deleteLine()
{
	unsigned short number = 0;
	int i, j;
	for (i = 3; i < 23; ++i)
	{
		bool flag = 1;
		for (j = 1; j < 11; ++j)
			if (!game[i][j])
			{
				flag = 0;
				break;
			}
		if (flag)
		{
			block *unfreeze[10];
			int unfreezenum = 0;
			int it = i;
			for (j = 1; j < 11; ++j)
				if (game[i][j]->sign2 != 2)
				{
					delete[] game[i][j];
					game[i][j] = 0;
				}
				else
					unfreeze[unfreezenum++] = game[i][j];
			for (i = 21; i > 0; --i)
				for (j = 1; j < 11; ++j)
					if (game[i][j] && (!game[i + 1][j] && (!game[i - 1][j] || game[i - 1][j]->sign != game[i][j]->sign) && (!game[i][j + 1] || game[i][j + 1]->sign != game[i][j]->sign) && (!game[i][j - 1] || game[i][j - 1]->sign != game[i][j]->sign)))
						game[i][j]->sign = supply();
			for (j = 1; j < 11; ++j)
				for (i = it; i > frozenLine(it, j) + 1; --i)
				{
					if (!game[i][j])
					{
						game[i][j] = game[i - 1][j];
						game[i - 1][j] = 0;
					}
				}
			for (i = 0; i < unfreezenum; ++i)
				unfreeze[i]->sign2 = 1;
			i = it;
			++number;
		}
	}
	linenum += number;
	return number;
}

unsigned short FrozenBoard::frozenLine(unsigned short row, unsigned short column)
{
	for (unsigned short i = row; i > 0; --i)
		if (game[i][column] && game[i][column]->sign2 == 2)
			return i;
	return 0;
}

bool FrozenBoard::end()
{
	fix();
	addScore(deleteLine());
	printOld();
	Sleep(50);
	unsigned i, j;
	do
	{
		while (fall())
		{
			for (i = 1; i < 23; ++i)
				for (j = 1; j < 11; ++j)
					if (game[i][j] && game[i][j]->sign2 != 2 && (!game[i + 1][j] && (!game[i - 1][j] || game[i - 1][j]->sign != game[i][j]->sign) && (!game[i][j + 1] || game[i][j + 1]->sign != game[i][j]->sign) && (!game[i][j - 1] || game[i][j - 1]->sign != game[i][j]->sign)))
					{
						game[i][j]->sign = supply();
						game[i + 1][j] = game[i][j];
						game[i][j] = 0;
					}
			addScore(deleteLine());
			printOld();
			Sleep(50);
		}
		for (i = 1; i < 23; ++i)
			for (j = 1; j < 11; ++j)
				if (game[i][j] && game[i][j]->sign2 != 2 && (!game[i + 1][j] && (!game[i - 1][j] || game[i - 1][j]->sign != game[i][j]->sign) && (!game[i][j + 1] || game[i][j + 1]->sign != game[i][j]->sign) && (!game[i][j - 1] || game[i][j - 1]->sign != game[i][j]->sign)))
				{
					game[i][j]->sign = supply();
					game[i + 1][j] = game[i][j];
					game[i][j] = 0;
				}
		addScore(deleteLine());
	} while (fall());
	++step;
	if (step >= 8 - ((difficulty - 1) / 5) * 2)
	{
		froze();
		printOld();
		step = 0;
	}
	do
	{
		while (fall())
		{
			for (i = 1; i < 23; ++i)
				for (j = 1; j < 11; ++j)
					if (game[i][j] && game[i][j]->sign2 != 2 && (!game[i + 1][j] && (!game[i - 1][j] || game[i - 1][j]->sign != game[i][j]->sign) && (!game[i][j + 1] || game[i][j + 1]->sign != game[i][j]->sign) && (!game[i][j - 1] || game[i][j - 1]->sign != game[i][j]->sign)))
					{
						game[i][j]->sign = supply();
						game[i + 1][j] = game[i][j];
						game[i][j] = 0;
					}
			addScore(deleteLine());
			printOld();
			Sleep(50);
		}
		for (i = 1; i < 23; ++i)
			for (j = 1; j < 11; ++j)
				if (game[i][j] && game[i][j]->sign2 != 2 && (!game[i + 1][j] && (!game[i - 1][j] || game[i - 1][j]->sign != game[i][j]->sign) && (!game[i][j + 1] || game[i][j + 1]->sign != game[i][j]->sign) && (!game[i][j - 1] || game[i][j - 1]->sign != game[i][j]->sign)))
				{
					game[i][j]->sign = supply();
					game[i + 1][j] = game[i][j];
					game[i][j] = 0;
				}
		addScore(deleteLine());
	} while (fall());
	if (gameover())
		return 0;
	return 1;
}

void FrozenBoard::print()
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
			printBlock(i, j);
		if (i == 4)
			cout << "        下一个            下二个";
		if (i >= 6 && i <= 13)
		{
			cout << "    ";
			for (int j = 0; j < 7; ++j)
				printBlock(next[0][i - 6][j]);
			cout << "    ";
			for (int j = 0; j < 7; ++j)
				printBlock(next[1][i - 6][j]);
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

void FrozenBoard::printNewOnly()
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
			printBlock(obj->getR(i), obj->getC(i));
		}
	}
	insertMove(21, 16);
	if (difficulty <= 5)
	{
		if (step)
			for (int i = 0; i < step; ++i)
				cout << "---";
		else
			cout << "                        ";
	}
	else
		if (difficulty <= 10)
		{
			if (step)
				for (int i = 0; i < step; ++i)
					cout << "----";
			else
				cout << "                        ";
		}
		else
		{
			if (step)
				for (int i = 0; i < step; ++i)
					cout << "------";
			else
				cout << "                        ";
		}
}

void FrozenBoard::printShadow()
{
	unsigned short i, mindif;
	for (i = 0; i < 4; ++i)
		if (shadow[i][ROW] > 2)
			if (!game[shadow[i][ROW]][shadow[i][COLUMN]])
			{
				insertMove(shadow[i][ROW] - 3, shadow[i][COLUMN] * 2 + 16);
				cout << "  ";
			}
	mindif = high();
	for (i = 0; i < 4; ++i)
	{
		shadow[i][ROW] = obj->getR(i) + mindif;
		shadow[i][COLUMN] = obj->getC(i);
		if (!game[obj->getR(i) + mindif][obj->getC(i)] && obj->getR(i) + mindif > 2)
		{
			insertMove(obj->getR(i) + mindif - 3, 2 * obj->getC(i) + 16);
			switch (blockstyle)
			{
			case COLORFUL:case COLORLESS:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); break;
			case CLASSIC:break;
			}
			cout << "囗";
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

FrozenBoard::FrozenBoard() :GravityBoard("冰冻")
{
}