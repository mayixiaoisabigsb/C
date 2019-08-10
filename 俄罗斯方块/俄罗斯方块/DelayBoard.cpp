#include<iostream>
#include"insertMove.h"
#include "DelayBoard.h"
using namespace std;

bool DelayBoard::end()
{
	fix();
	++step;
	if (step >= ((difficulty - 1) / 5 + 1) * 4)
	{
		addScore(deleteLine());
		step = 0;
	}
	if (gameover())
		return 0;
	return 1;
}

void DelayBoard::addScore(unsigned short number)
{
	score += number * 40 * weight();
}

void DelayBoard::print()
{
	board::print();
	insertMove(21, 16);
	if (difficulty <= 5)
	{
		if (step)
			for (int i = 0; i < step; ++i)
				cout << "------";
		else
			cout << "                        ";
	}
	else
		if (difficulty <= 10)
		{
			if (step)
				for (int i = 0; i < step; ++i)
					cout << "---";
			else
				cout << "                        ";
		}
		else
		{
			if (step)
				for (int i = 0; i < step; ++i)
					cout << "--";
			else
				cout << "                        ";
		}
}

DelayBoard::DelayBoard() :board("ясЁы"), step(0)
{
}