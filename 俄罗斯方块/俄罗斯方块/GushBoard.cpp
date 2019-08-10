#include<iostream>
#include "GushBoard.h"
#include"insertMove.h"
using namespace std;

void GushBoard::gush(unsigned short voidnum)
{
	int i, j;
	for (i = 1; i < 22; ++i)
		for (j = 1; j < 11; ++j)
			game[i][j] = game[i + 1][j];
	for (i = 1; i < 11; ++i)
		game[22][i] = new block(S, 0);
	for (i = 0; i < voidnum; ++i)
	{
		j = rand() % 10 + 1;
		if (game[22][j])
			delete[] game[22][j];
		game[22][j] = 0;
	}
}

bool GushBoard::end()
{
	fix();
	addScore(deleteLine());
	++step;
	if (step >= 8 - ((difficulty - 1) / 5) * 2)
	{
		gush((difficulty - 1) / 5 + 1);
		printOld();
		step = 0;
	}
	if (gameover())
		return 0;
	return 1;
}

void GushBoard::print()
{
	board::print();
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

GushBoard::GushBoard() :board("Ȫӿ"), step(0)
{
	delete[] game[23][1];
	delete[] game[23][3];
	delete[] game[23][8];
	delete[] game[23][10];
	game[23][1] = new block(S, 0);
	game[23][3] = new block(S, 0);
	game[23][8] = new block(S, 0);
	game[23][10] = new block(S, 0);
}