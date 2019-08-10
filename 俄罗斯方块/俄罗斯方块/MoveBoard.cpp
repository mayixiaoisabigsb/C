#include<iostream>
#include<iomanip>
#include "MoveBoard.h"
#include"insertMove.h"
using namespace std;

bool MoveBoard::end()
{
	fix();
	addScore(deleteLine());
	if (gameover())
		return 0;
	int i, j;
	for (int count = 0; count < (difficulty - 1) / 5 + 1; ++count)
	{
		block *temp[23];
		for (i = 0; i < 23; ++i)
			temp[i] = game[i][1];
		for (j = 1; j < 10; ++j)
			for (i = 0; i < 23; ++i)
				game[i][j] = game[i][j + 1];
		for (i = 0; i < 23; ++i)
			game[i][10] = temp[i];
		printOld();
		Sleep(50);
	}
	if (gameover())
		return 0;
	return 1;
}

void MoveBoard::print()
{
	insertMove(5, 6);
	cout << name << "\n\n    ";
	if (difficulty <= 5)
		cout << "��  ";
	else
		if (difficulty <= 10)
			cout << "��ͨ  ";
		else
			cout << "����  ";
	cout << setw(2) << difficulty;
	insertMove(0, 0);
	for (int i = 3; i < 24; ++i)
	{
		cout << "\t\t";
		for (int j = 0; j < 12; ++j)
		{
			if (game[i][j] && (game[i][j]->getType() != BORDER || i == 23))
				game[i][j]->show();
			else
				cout << "  ";
		}
		if (i == 4)
			cout << "        ��һ��            �¶���";
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
			cout << "                ��Ϸ�淨";
		if (i == 17)
			cout << "      A:�����ƶ�        D:�����ƶ�";
		if (i == 19)
			cout << "      W:˳ʱ��ת        S:��������";
		if (i == 21)
			cout << "      P:��Ϸ��ͣ    space:ֱ�����";
		if (i == 23)
		{
			cout << "      ��������:" << linenum;
			insertMove(20, 61);
			cout << "�÷�:" << score << endl;
		}
		cout << endl;
	}
}

MoveBoard::MoveBoard() :board("Ư��")
{
}