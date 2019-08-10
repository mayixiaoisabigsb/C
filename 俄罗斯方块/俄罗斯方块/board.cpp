#include<conio.h>
#include<iostream>
#include<iomanip>
#include"insertMove.h"
#include "board.h"
using namespace std;

unsigned short shadow[4][2];
unsigned short difficulty = 1;
bool shadowShow = 1;
bool bigBlock = 1;

board::board(const string name) :score(0), linenum(0), name(name)
{
	int i;
	for (i = 0; i < 23; ++i)
		for (int j = 1; j < 11; ++j)
			game[i][j] = 0;
	for (i = 0; i < 23; ++i)
	{
		game[i][0] = new block(BORDER, 0);
		game[i][11] = new block(BORDER, 0);
	}
	for (i = 0; i < 12; ++i)
		game[23][i] = new block(BORDER, 0);
	nextobj[0] = spawnNew();
	nextobj[1] = spawnNew();
	for (i = 0; i < 7; ++i)
	{
		next[0][0][i] = new block(BORDER, 0);
		next[1][0][i] = new block(BORDER, 0);
		next[0][7][i] = new block(BORDER, 0); 
		next[1][7][i] = new block(BORDER, 0);
	}
	for (i = 1; i < 8; ++i)
	{
		next[0][i][0] = new block(BORDER, 0); 
		next[0][i][6] = new block(BORDER, 0); 
		next[1][i][0] = new block(BORDER, 0); 
		next[1][i][6] = new block(BORDER, 0);
	}
	for (i = 1; i < 7; ++i)
		for (int j = 1; j < 6; ++j)
			next[0][i][j] = next[1][i][j] = 0;
	for (i = 0; i < 4; ++i)
	{
		next[0][3 + nextobj[0]->getSR(i)][3 + nextobj[0]->getSC(i)] = new block(nextobj[0]->getType(), 0);
		next[1][3 + nextobj[1]->getSR(i)][3 + nextobj[1]->getSC(i)] = new block(nextobj[1]->getType(), 0);
	}
}

board::~board()
{
	int i, j;
	for (i = 0; i < 24; ++i)
		for (j = 0; j < 12; ++j)
			if (game[i][j])
				delete[] game[i][j];
	for (i = 0; i < 8; ++i)
		for (j = 0; j < 7; ++j)
		{
			if (next[0][i][j])
				delete[] next[0][i][j];
			if (next[1][i][j])
				delete[] next[1][i][j];
		}
	delete[] nextobj[0];
	delete[] nextobj[1];
}

bool board::start()
{
	bool successspawn = spawn();
	if (!successspawn)
	{
		delete[] obj;
		obj = 0;
	}
	betterPrint();
	if (shadowShow&&successspawn)
		printShadow();
	return successspawn;
}

bool board::end()
{
	fix();
	addScore(deleteLine());
	if (gameover())
		return 0;
	return 1;
}

void board::move(char direction,bool artificial)
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

void board::addScore(unsigned short number)
{
	switch (number)
	{
	case 0:score += 0; break;
	case 1:score += 30 * weight(); break;
	case 2:score += 90 * weight(); break;
	case 3:score += 180 * weight(); break;
	case 4:default:score += 300 * weight();
	}
}

unsigned short board::weight()
{
	if (difficulty <= 5)
		return 9 + difficulty;
	else
		if (difficulty <= 10)
			return 14 + 2 * (difficulty - 5);
		else
			return 24 + 4 * (difficulty - 10);
}

unsigned short board::top()
{
	for (int i = 3; i < 23; ++i)
	{
		for (int j = 1; j < 11; ++j)
			if (game[i][j] && !game[i][j]->getActive())
				return i;
	}
	return 22;
}

unsigned short board::top(unsigned short column)
{
	for (int i = 0; i < 24; ++i)
		if (game[i][column] && !game[i][column]->getActive())
			return i;
	return 23;
}

unsigned short board::high()
{
	unsigned short mindif = 21;
	for (int i = 0; i < obj->getBottomnum(); ++i)
	{
		int j;
		for (j = 0; !game[obj->getBR(i) + j][obj->getBC(i)] || game[obj->getBR(i) + j][obj->getBC(i)]->getActive(); ++j);
		mindif = j > mindif ? mindif : j;
	}
	return mindif;
}

unsigned short board::deleteLine()
{
	unsigned short number = 0;
	int i, j;
	for (i = 22; i > 2; --i)
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
			for (j = 1; j < 11; ++j)
			{
				delete[] game[i][j];
				game[i][j] = 0;
			}
			for (int it = i; it >= top() ; --it)
				for (j = 1; j < 11; ++j)
				{
					game[it][j] = game[it - 1][j];
					game[it - 1][j] = 0;
				}
			++i;
			++number;
		}
	}
	linenum += number;
	return number;
}

unsigned board::getScore()
{
	return score;
}

unsigned board::getLinenum()
{
	return linenum;
}

void board::print()
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
			if (game[i][j])
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

void board::betterPrint()
{
	insertMove(0, 0);
	print();
}

void board::printNewOnly()
{
	int i;
	for (i = obj->getR(0)-3; i <=obj->getR(0)+4; ++i)
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
			game[obj->getR(i)][obj->getC(i)]->show();
		}
	}
	insertMove(22, 0);
}

void board::printShadow()
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

void board::printScore()
{
	insertMove(20, 66);
	cout << "           ";
	insertMove(20, 66);
	cout << score;
}

bool board::spawn()
{
	int i;
	obj = nextobj[0];
	nextobj[0] = nextobj[1];
	nextobj[1] = spawnNew();
	for (i = 0; i < 4; ++i)
	{
		if (game[obj->getR(i)][obj->getC(i)])
			return 0;
		game[obj->getR(i)][obj->getC(i)] = new block(obj->getType());
	}
	for (i = 1; i < 7; ++i)
		for (int j = 1; j < 6; ++j)
		{
			if (next[0][i][j])
			{
				delete[] next[0][i][j];
				next[0][i][j] = 0;
			}
			if (next[1][i][j])
			{
				delete[] next[1][i][j];
				next[1][i][j] = 0;
			}
		}
	for (i = 0; i < 4; ++i)
	{
		unsigned short row1 = 3, column1 = 3, row2 = 3, column2 = 3;
		switch (nextobj[0]->getType())
		{
		case O:--column1; break;
		case S:case Z:++row1; break;
		}
		switch (nextobj[1]->getType())
		{
		case O:--column2; break;
		case S:case Z:++row2; break;
		}
		next[0][row1 + nextobj[0]->getSR(i)][column1 + nextobj[0]->getSC(i)] = new block(nextobj[0]->getType());
		next[1][row2 + nextobj[1]->getSR(i)][column2 + nextobj[1]->getSC(i)] = new block(nextobj[1]->getType());
	}
	return 1;
}

void board::fix()
{
	int i;
	for (i = 0; i < 4; ++i)
	{
		if (obj->getR(i) > 2)
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
	obj = 0;
}

void board::down()
{
	move('s', 0);
}

void board::setblock(unsigned short row, unsigned short column,tiletype target)
{
	if (game[row][column])
		delete[] game[row][column];
	game[row][column] = new block(target, 0);
}

tile * board::spawnNew()
{
	tile *temp;
	switch (rand() % 7)
	{
	case 0:temp = new tile_I; break;
	case 1:temp = new tile_J; break;
	case 2:temp = new tile_L; break;
	case 3:temp = new tile_O; break;
	case 4:temp = new tile_S; break;
	case 5:temp = new tile_Z; break;
	case 6:temp = new tile_T; break;
	default:return 0;
	}
	return temp;
}

bool board::mayMove(char direction)
{
	bool flag = 1;
	switch (direction)
	{
	case 'w':
	{
		obj->turnAround();
		for (int i = 0; i < 4; ++i)
			if (game[obj->getR(i)][obj->getC(i)] && !game[obj->getR(i)][obj->getC(i)]->getActive())
				flag = 0;
		for (int j = 1; j < obj->getConditionnum(); ++j)
			obj->turnAround();
	}break;
	case 'a':
	{
		obj->move('a');
		for (int i = 0; i < 4; ++i)
			if (game[obj->getR(i)][obj->getC(i)] && !game[obj->getR(i)][obj->getC(i)]->getActive())
				flag = 0;
		obj->move('d');
	}break;
	case 'd':
	{
		obj->move('d');
		for (int i = 0; i < 4; ++i)
			if (game[obj->getR(i)][obj->getC(i)] && !game[obj->getR(i)][obj->getC(i)]->getActive())
				flag = 0;
		obj->move('a');
	}break;
	case 's':
	{
		obj->move('s');
		for (int i = 0; i < 4; ++i)
			if (game[obj->getR(i)][obj->getC(i)] && !game[obj->getR(i)][obj->getC(i)]->getActive())
				flag = 0;
		obj->move('w');
	}break;
	default:return 0;
	}
	return flag;
}

void board::printOld()
{
	for (int i = 3; i < 23; ++i)
	{
		insertMove(i - 3, 18);
		for (int j = 1; j < 11; ++j)
		{
			if (game[i][j])
				game[i][j]->show();
			else
				cout << "  ";
		}
	}
}

bool board::inDanger()
{
	for (int i = 0; i < obj->getBottomnum(); ++i)
		if (game[obj->getBR(i)][obj->getBC(i)])
			return 1;
	return 0;
}

bool board::gameover()
{
	for (int i = 0; i < 3; ++i)
		if (game[i][5] || game[i][6])
			return 1;
	return 0;
}