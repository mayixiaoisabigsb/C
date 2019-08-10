#include "DevideBoard.h"

bool DevideBoard::mayMove(char direction)
{
	bool flag = 1;
	switch (direction)
	{
	case 'w':
	{
		obj->turnAround();
		for (int i = 0; i < 4; ++i)
			if (game[obj->getR(i)][obj->getC(i)] && !game[obj->getR(i)][obj->getC(i)]->getActive() || cross())
				flag = 0;
		for (int j = 1; j < obj->getConditionnum(); ++j)
			obj->turnAround();
	}break;
	case 'a':
	{
		obj->move('a');
		for (int i = 0; i < 4; ++i)
			if (game[obj->getR(i)][obj->getC(i)] && !game[obj->getR(i)][obj->getC(i)]->getActive() || cross())
				flag = 0;
		obj->move('d');
	}break;
	case 'd':
	{
		obj->move('d');
		for (int i = 0; i < 4; ++i)
			if (game[obj->getR(i)][obj->getC(i)] && !game[obj->getR(i)][obj->getC(i)]->getActive() || cross())
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

bool DevideBoard::cross()
{
	if (order)
	{
		for (int i = 0; i < 4; ++i)
			if (obj->getC(i) < 6)
				return 1;
	}
	else
	{
		for (int i = 0; i < 4; ++i)
			if (obj->getC(i) > 5)
				return 1;
	}
	return 0;
}

bool DevideBoard::spawn()
{
	int i;
	obj = nextobj[0];
	nextobj[0] = nextobj[1];
	nextobj[1] = spawnNew();
	if (order)
	{
		obj->move('a');
		obj->move('a');
	}
	else
	{
		obj->move('d');
		obj->move('d');
		obj->move('d');
	}
	for (i = 0; i < 4; ++i)
	{
		if (game[obj->getR(i)][obj->getC(i)])
			return 0;
		game[obj->getR(i)][obj->getC(i)] = new block(obj->getType());
	}
	order = !order;
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

DevideBoard::DevideBoard() :board("╥жая"), order(1)
{
}