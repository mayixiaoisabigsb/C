#include<iostream>
#include<iomanip>
#include"insertMove.h"
#include "ChasmBoard.h"
using namespace std;

bool ChasmBoard::fall()
{
	bool change = 0;
	unsigned target[200][4][2] = { 0 }, group[200][2] = { 0 }, groupnumber = 0, i, j;
	for (i = 22; i > 0; --i)
		for (j = 1; j < 11; ++j)
			if (game[i][j] && game[i][j]->getType() != BORDER)
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

unsigned short ChasmBoard::deleteLine()
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
			int it = i;
			for (j = 1; j < 11; ++j)
				if (game[i][j]->getType() != BORDER)
				{
					delete[] game[i][j];
					game[i][j] = 0;
				}
			for (i = 21; i > 0; --i)
				for (j = 1; j < 11; ++j)
					if (game[i][j] && (!game[i + 1][j] && (!game[i - 1][j] || game[i - 1][j]->sign != game[i][j]->sign) && (!game[i][j + 1] || game[i][j + 1]->sign != game[i][j]->sign) && (!game[i][j - 1] || game[i][j - 1]->sign != game[i][j]->sign)))
						game[i][j]->sign = supply();
			for (j = 1; j < 11; ++j)
				for (i = it; i > borderLine(it, j) + 1; --i)
				{
					if (!game[i][j])
					{
						game[i][j] = game[i - 1][j];
						game[i - 1][j] = 0;
					}
				}
			i = it;
			++number;
		}
	}
	linenum += number;
	return number;
}

unsigned short ChasmBoard::borderLine(unsigned short row, unsigned short column)
{
	for (unsigned short i = row; i > 0; --i)
		if (game[i][column] && game[i][column]->getType() == BORDER)
			return i;
	return 0;
}

void ChasmBoard::move(char direction, bool artificial)
{
	int i;
	unsigned short order;
	switch (direction)
	{
	case 'w':case 'W':
	{
		if (mayMove('w'))
		{
			order = game[obj->getR(0)][obj->getC(0)]->sign;
			for (i = 0; i < 4; ++i)
			{
				delete[] game[obj->getR(i)][obj->getC(i)];
				game[obj->getR(i)][obj->getC(i)] = 0;
			}
			obj->turnAround();
			for (i = 0; i < 4; ++i)
				game[obj->getR(i)][obj->getC(i)] = new block(obj->getType(), 1, order);
		}
		return;
	}
	case 's':case'S':
	{
		if (mayMove('s'))
		{
			order = game[obj->getR(0)][obj->getC(0)]->sign;
			for (i = 0; i < 4; ++i)
			{
				delete[] game[obj->getR(i)][obj->getC(i)];
				game[obj->getR(i)][obj->getC(i)] = 0;
			}
			if (artificial&&shadow[0][ROW] < 19)
			{
				score += (difficulty - 1) / 5 + 1;
				printScore();
			}
			obj->move('s');
			for (i = 0; i < 4; ++i)
				game[obj->getR(i)][obj->getC(i)] = new block(obj->getType(), 1, order);
		}
		return;
	}
	case 'a':case 'A':
	{
		if (mayMove('a'))
		{
			order = game[obj->getR(0)][obj->getC(0)]->sign;
			for (i = 0; i < 4; ++i)
			{
				delete[] game[obj->getR(i)][obj->getC(i)];
				game[obj->getR(i)][obj->getC(i)] = 0;
			}
			obj->move('a');
			for (i = 0; i < 4; ++i)
				game[obj->getR(i)][obj->getC(i)] = new block(obj->getType(), 1, order);
		}
		return;
	}
	case 'd':case 'D':
	{
		if (mayMove('d'))
		{
			order = game[obj->getR(0)][obj->getC(0)]->sign;
			for (i = 0; i < 4; ++i)
			{
				delete[] game[obj->getR(i)][obj->getC(i)];
				game[obj->getR(i)][obj->getC(i)] = 0;
			}
			obj->move('d');
			for (i = 0; i < 4; ++i)
				game[obj->getR(i)][obj->getC(i)] = new block(obj->getType(), 1, order);
		}
		return;
	}
	case ' ':
	{
		order = game[obj->getR(0)][obj->getC(0)]->sign;
		for (i = 0; i < 4; ++i)
		{
			delete[] game[obj->getR(i)][obj->getC(i)];
			game[obj->getR(i)][obj->getC(i)] = 0;
		}
		if (shadow[0][ROW] < 19)
			score += high()*((difficulty - 1) / 5 + 1) * 2;
		while (!inDanger())
			obj->move('s');
		for (i = 0; i < 4; ++i)
			game[obj->getR(i)][obj->getC(i)] = new block(obj->getType(), 0, order);
	}
	default:return;
	}
}

void ChasmBoard::print()
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
		if (i != 23)
			for (int j = 0; j < 12; ++j)
			{
				if (game[i][j])
					game[i][j]->show();
				else
					cout << "  ";
			}
		else
		{
			game[23][0]->show();
			cout << "                    ";
			game[23][11]->show();
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

void ChasmBoard::printShadow()
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
	bool flag = 1;
	for (i = 0; i < 4; ++i)
	{
		shadow[i][ROW] = obj->getR(i) + mindif;
		shadow[i][COLUMN] = obj->getC(i);
		if (shadow[i][ROW] == 22)
			flag = 0;
	}
	for (i = 0; i < 4; ++i)
	{
		if (!game[obj->getR(i) + mindif][obj->getC(i)] && obj->getR(i) + mindif > 2 && flag)
		{
			insertMove(obj->getR(i) + mindif - 3, 2 * obj->getC(i) + 16);
			switch (blockstyle)
			{
			case COLORFUL:
			{
				switch (obj->getType())
				{
				case I:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); break;
				case J:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); break;
				case L:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN); break;
				case O:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); break;
				case S:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); break;
				case Z:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN); break;
				case T:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE); break;
				}
			}break;
			case COLORLESS:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); break;
			case CLASSIC:break;
			}
			cout << "囗";
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void ChasmBoard::fix()
{
	int i;
	for (i = 0; i < 4; ++i)
	{
		if (obj->getR(i) > 2 && obj->getR(i) < 19)
		{
			insertMove(obj->getR(i) - 3, 16 + obj->getC(i) * 2);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			if (bigBlock)
				cout << "█";
			else
				cout << "■";
		}
	}
	Sleep(50);
	printOld();
	for (i = 0; i < 4; ++i)
		game[obj->getR(i)][obj->getC(i)]->fix();
	delete[] obj;
}

bool ChasmBoard::end()
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
					if (game[i][j] && game[i][j]->getType() != BORDER && (!game[i + 1][j] && (!game[i - 1][j] || game[i - 1][j]->sign != game[i][j]->sign) && (!game[i][j + 1] || game[i][j + 1]->sign != game[i][j]->sign) && (!game[i][j - 1] || game[i][j - 1]->sign != game[i][j]->sign)))
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
				if (game[i][j] && game[i][j]->getType() != BORDER && (!game[i + 1][j] && (!game[i - 1][j] || game[i - 1][j]->sign != game[i][j]->sign) && (!game[i][j + 1] || game[i][j + 1]->sign != game[i][j]->sign) && (!game[i][j - 1] || game[i][j - 1]->sign != game[i][j]->sign)))
				{
					game[i][j]->sign = supply();
					game[i + 1][j] = game[i][j];
					game[i][j] = 0;
				}
		addScore(deleteLine());
	} while (fall());
	do
	{
		for (int i = 20; i < 23; ++i)
			for (int j = 1; j < 11; ++j)
				if (game[i][j])
				{
					delete[] game[i][j];
					game[i][j] = 0;
				}
	} while (fall());
	if (gameover())
		return 0;
	return 1;
}

ChasmBoard::ChasmBoard() :GravityBoard("深渊")
{
	int i, j;
	for (int counter = 0; counter < 5; ++counter)
	{
		i = rand() % 4 + 15;
		j = rand() % 10 + 1;
		if (!game[i][j])
			game[i][j] = new block(BORDER, 0);
	}
}