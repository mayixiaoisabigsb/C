#include "GravityBoard.h"

unsigned &member(unsigned group[][2],unsigned sign)
{
	int i = 0;
	while (group[i][0] != sign)
		++i;
	return group[i][1];
}

unsigned GravityBoard::supply()
{
	unsigned order = 1;
	while (1)
	{
		bool flag = 0;
		for (int i = 22; i >= 0; --i)
		{
			for (int j = 1; j < 11; ++j)
				if (game[i][j] && game[i][j]->sign == order)
				{
					flag = 1;
					break;
				}
			if (flag)
				break;
		}
		if (flag)
			++order;
		else
			return order;
	}
}

unsigned short GravityBoard::blockHigh(unsigned short row, unsigned short column)
{
	unsigned short high = 0, r = row;
	while (!game[r + 1][column] || game[r + 1][column]->sign == game[row][column]->sign)
	{
		++r;
		++high;
	}
	return high;
}

unsigned short GravityBoard::deleteLine()
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
			int it = i;
			for (j = 1; j < 11; ++j)
			{
				delete[] game[i][j];
				game[i][j] = 0;
			}
			for (i = 21; i > 0; --i)
				for (j = 1; j < 11; ++j)
					if (game[i][j] && (!game[i + 1][j] && (!game[i - 1][j] || game[i - 1][j]->sign != game[i][j]->sign) && (!game[i][j + 1] || game[i][j + 1]->sign != game[i][j]->sign) && (!game[i][j - 1] || game[i][j - 1]->sign != game[i][j]->sign)))
						game[i][j]->sign = supply();
			for (i = it; it >= top() ; --it)
				for (j = 1; j < 11; ++j)
				{
					if (!game[it][j])
					{
						game[it][j] = game[it - 1][j];
						game[it - 1][j] = 0;
					}
				}
			++i;
			++number;
		}
	}
	linenum += number;
	return number;
}

bool GravityBoard::fall()
{
	bool change = 0;
	unsigned target[200][4][2] = { 0 }, group[200][2] = { 0 }, groupnumber = 0, i, j;
	for (i = 22; i > 0; --i)
		for (j = 1; j < 11; ++j)
			if (game[i][j])
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

void GravityBoard::move(char direction, bool artificial)
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
			if (artificial)
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
		score += high()*((difficulty - 1) / 5 + 1) * 2;
		while (!inDanger())
			obj->move('s');
		for (i = 0; i < 4; ++i)
			game[obj->getR(i)][obj->getC(i)] = new block(obj->getType(), 0, order);
	}
	default:return;
	}
}

bool GravityBoard::end()
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
					if (game[i][j] && (!game[i + 1][j] && (!game[i - 1][j] || game[i - 1][j]->sign != game[i][j]->sign) && (!game[i][j + 1] || game[i][j + 1]->sign != game[i][j]->sign) && (!game[i][j - 1] || game[i][j - 1]->sign != game[i][j]->sign)))
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
				if (game[i][j] && (!game[i + 1][j] && (!game[i - 1][j] || game[i - 1][j]->sign != game[i][j]->sign) && (!game[i][j + 1] || game[i][j + 1]->sign != game[i][j]->sign) && (!game[i][j - 1] || game[i][j - 1]->sign != game[i][j]->sign)))
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

bool GravityBoard::spawn()
{
	unsigned order = supply();
	int i;
	obj = nextobj[0];
	nextobj[0] = nextobj[1];
	nextobj[1] = spawnNew();
	for (i = 0; i < 4; ++i)
	{
		if (game[obj->getR(i)][obj->getC(i)])
			return 0;
		game[obj->getR(i)][obj->getC(i)] = new block(obj->getType(), 1, order);
	}
	for (i = 1; i < 6; ++i)
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

GravityBoard::GravityBoard(const string name) :board(name)
{
}