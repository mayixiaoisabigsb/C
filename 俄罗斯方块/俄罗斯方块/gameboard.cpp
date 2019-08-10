#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<iomanip>
#include<ctime>
#include<fstream>
#include<string>
#include"resource.h"
#include"insertMove.h"
#include "gameboard.h"
#include"MoveBoard.h"
#include"GravityBoard.h"
#include"LaserBoard.h"
#include"DelayBoard.h"
#include"GushBoard.h"
#include"ChasmBoard.h"
#include"FrozenBoard.h"
#include"DarknessBoard.h"
#include"DevideBoard.h"
using namespace std;

const string version = "1.0-pre2";
const string locate = "d:\\TetrisRevolutionScores.bat";

void gameboard::rScores()
{
	for (int j = 1; j <= 10; ++j)
		for (int i = 1; i <= 10; ++i)
			scores[j][SCORE][i] = scores[j][LINE][i] = scores[j][DIFFICULTY][i] = 0;
	save();
}

void gameboard::gameStart()
{
	if (difficulty <= 5)
	{
		speed = 560 - 60 * difficulty;
		if (music)
			PlaySound((LPCTSTR)IDR_WAVE1, NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
	}
	else
		if (difficulty <= 10)
		{
			speed = 220 - 20 * (difficulty - 5);
			if (music)
				PlaySound((LPCTSTR)IDR_WAVE2, NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
		}
		else
		{
			speed = 100 - 10 * (difficulty - 10);
			if (music)
				PlaySound((LPCTSTR)IDR_WAVE3, NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
		}
	do
	{
		switch (current)
		{
		case NORMAL:mainboard = new board; break;
		case MOVE:mainboard = new MoveBoard; break;
		case GRAVITY:mainboard = new GravityBoard; break;
		case LASER:mainboard = new LaserBoard; break;
		case DELAY:mainboard = new DelayBoard; break;
		case GUSH:mainboard = new GushBoard; break;
		case CHASM:mainboard = new ChasmBoard; break;
		case FROZEN:mainboard = new FrozenBoard; break;
		case DARKNESS:mainboard = new DarknessBoard; break;
		case DEVIDE:mainboard = new DevideBoard; break;
		}
		do
		{
			if (!mainboard->start())
				break;
			while (playing());
		} while (mainboard->end());
	} while (gameover());
	PlaySound(NULL, NULL, SND_FILENAME);
}

bool gameboard::playing()
{
	long gamebegin = clock();
	static long lasttime = 0;
	static long landtime = 0;
	static long entertime = 0;
	static bool land = 0;
	if (mainboard->inDanger())
	{
		if (land&&gamebegin - landtime > 800)
		{
			land = 0;
			return 0;
		}
		else
			if (!land)
			{
				land = 1;
				landtime = clock();
			}
	}
	else
		land = 0;
	char direction = 0;
	long begin = clock();
	while (clock() - entertime >= 150 && clock() - begin <= 10)
		if (_kbhit())
		{
			entertime = clock();
			direction = _getch();
		}
	if (direction == 'p' || direction == 'P')
	{
		long pausebegin = clock();
		char choice;
		do
		{
			insertMove(11, 0);
			cout << "   ��Ϸ����ͣ\n\n    P:����\n\n    S:ѡ��\n\n    B:������Ϸ";
			do
				choice = _getch(); while (choice != 's'&&choice != 'S'&&choice != 'p'&&choice != 'P'&&choice != 'b'&&choice != 'B');
			if (choice == 's' || choice == 'S')
			{
				system("cls");
				settings(1);
				system("cls");
				mainboard->print();
				if (shadowShow)
					mainboard->printShadow();
			}
			if (choice == 'b' || choice == 'B')
			{
				insertMove(11, 0);
				cout << "             \n\n          \n\n          \n\n              ";
				mainboard->setblock(0, 5);
				return 0;
			}
		} while (choice != 'p'&&choice != 'P');
		long pauseend = clock();
		lasttime += pauseend - pausebegin;
		landtime += pauseend - pausebegin;
		entertime += pauseend - pausebegin;
		insertMove(11, 0);
		cout << "             \n\n          \n\n          \n\n              ";
	}
	mainboard->move(direction);
	if (gamebegin - lasttime > speed && direction != ' ')
	{
		mainboard->down();
		lasttime = gamebegin;
	}
	if (direction == ' ')
	{
		land = 0;
		return 0;
	}
	if (shadowShow && (direction == 'a' || direction == 'A' || direction == 'd' || direction == 'D' || direction == 'w' || direction == 'W'))
		mainboard->printShadow();
	mainboard->printNewOnly();
	return 1;
}

bool gameboard::gameover()
{
	char choice;
	unsigned score = mainboard->getScore();
	mainboard->betterPrint();
	int i = 10;
	if (score > scores[current][SCORE][10])
	{
		for (i = 9; i; --i)
			if (score > scores[current][SCORE][i])
			{
				scores[current][SCORE][i + 1] = scores[current][SCORE][i];
				scores[current][LINE][i + 1] = scores[current][LINE][i];
				scores[current][DIFFICULTY][i + 1] = scores[current][DIFFICULTY][i];
			}
			else
				break;
		scores[current][SCORE][i + 1] = score;
		scores[current][LINE][i + 1] = mainboard->getLinenum();
		scores[current][DIFFICULTY][i + 1] = difficulty;
	}
	delete[] mainboard;
	insertMove(22, 24);
	cout << "��Ϸ����";
	if (i != 10)
	{
		cout << "\t      ��ϲ���Ϊ�����а�ĵ�" << i + 1 << "����";
		save();
	}
	cout << "\n\t\t�Ƿ�����?   Y:��    N:��";
	do
		choice = _getch(); while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
	system("cls");
	if (choice == 'Y' || choice == 'y')
		return 1;
	else
		return 0;
}

void gameboard::showScores(mode gamemode)
{
	cout << "\n\t����" << setw(20) << "����" << setw(20) << "����" << setw(20) << "�Ѷ�" << '\n';
	for (int i = 1; i <= 10; ++i)
	{
		cout << "\t";
		for (int j = 0; j < 65; ++j)
			cout << '-';
		cout << "\n\t " << setw(2) << i << setw(21) << scores[gamemode][SCORE][i] << setw(19) << scores[gamemode][LINE][i] << setw(20) << scores[gamemode][DIFFICULTY][i] << endl;
	}
	cout << "\t";
	for (int j = 0; j < 65; ++j)
		cout << '-';
}

void gameboard::save()
{
	ofstream file;
	file.open(locate, ios::binary | ios::out | ios::trunc);
	for (int j = 1; j <= 10; ++j)
		for (int i = 1; i <= 10; ++i)
			file << scores[j][SCORE][i] << ' ' << scores[j][LINE][i] << ' ' << scores[j][DIFFICULTY][i] << ' ';
}

char gameboard::beginning()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "�汾�ţ�" << version;
	insertMove(0, 62);
	cout << "�����ߣ��蹽�蹽��";
	char choice;
	cout << "\n\n\n\n\t\t\t  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "��  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "��  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "˹  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "��  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "��  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "��  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "��\n\n\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "\t\t\t\t  1:��ʼ��Ϸ\n\n\n\t\t\t\t  2:�鿴���а�\n\n\n\t\t\t\t  3:ѡ��\n\n\n\t\t\t\t  4:�˳���Ϸ" << endl;
	cout << "\n\n\t    ��ܰ��ʾ:1.�������뷨δ�Ż���������Ϸǰ�����뷨����ΪӢ��!\n\t\t     2.������꣬�������������Ч��";
	do
		choice = _getch(); while (!(choice >= '1'&&choice <= '4'));
	if (sound)
		PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
	return choice;
}

mode gameboard::selectMode(bool gameing)
{
	char choice;
	insertMove(4, 32);
	cout << "��ѡ����Ϸģʽ\n\n\n\t\t\t    1.����\t    2.Ư��\n\n\n\t\t\t    3.����\t    4.����\n\n\n\t\t\t    5.�ӳ�\t    6.Ȫӿ\n\n\n\t\t\t    7.��Ԩ\t    8.����\n\n\n\t\t\t    9.�ڰ�\t    0.����\n\n\n\t\t\t\t    B:����";
	do
		choice = _getch(); while (!(choice >= '0'&&choice <= '9' || choice == 'b' || choice == 'B'));
	if (sound && (!gameing || !music))
		PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
	if (choice != 'b'&&choice != 'B'&&choice != '0')
		return (mode)(choice - '0');
	else
		if (choice == '0')
			return DEVIDE;
		else
			return NONE;
}

bool gameboard::selectGame()
{
	char change;
	cout << "\n\n\n\n\n\t\t\t\t��ѡ����Ϸ�Ѷ�\n\n\n\n\n\n\n\n\n\n\t\tA:��ǰѡ��    D:���ѡ��    S:ȷ��    B:����";
	do
	{
		insertMove(9, 37);
		if (difficulty <= 5)
			cout << "��";
		else
			if (difficulty <= 10)
				cout << "��ͨ";
			else
				cout << "����";
		insertMove(12, 38);
		cout << setw(2) << difficulty;
		change = _getch();
		switch (change)
		{
		case 'a':case 'A':
		{
			if (difficulty != 1)
			{
				--difficulty;
				if (sound)
					PlaySound((LPCTSTR)IDR_WAVE4, NULL, SND_RESOURCE | SND_ASYNC);
				Sleep(100);
			}
		}break;
		case 'd':case 'D':
		{
			if (difficulty != 15)
			{
				++difficulty;
				if (sound)
					PlaySound((LPCTSTR)IDR_WAVE4, NULL, SND_RESOURCE | SND_ASYNC);
				Sleep(100);
			}
		}break;
		}
	} while (change != 's'&&change != 'S'&&change != 'b'&&change != 'B');
	if (change == 'S' || change == 's')
		return 1;
	if (sound)
		PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
	return 0;
}

void gameboard::settings(bool gameing)
{
	char choice;
	do
	{
		cout << "\n\n\n\n\t\t      1:����  ";
		if (music)
			cout << "��";
		else
			cout << "��";
		cout << "\t      2:��Ч  ";
		if (sound)
			cout << "��";
		else
			cout << "��";
		cout << "\n\n\n\n\t\t      3:��ʾ��Ӱ  ";
		if (shadowShow)
			cout << "��";
		else
			cout << "��";
		cout << "\t      4:���鳬����ʾ  ";
		if (bigBlock)
			cout << "��";
		else
			cout << "��";
		cout << "\n\n\n\n\t\t      5:����������\t      6:�������а�\n\n\n\n\t\t      7:����\t\t      8:������־\n\n\n\n\t\t\t\t      B:����\n\n\n";
		do
		{
			do
				choice = _getch(); while (!(choice >= '1'&&choice <= '8') && choice != 'b'&&choice != 'B');
			if ((sound&&choice != '2' || !sound&&choice == '2') && (!gameing || !music))
				PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
			switch (choice)
			{
			case '1':
			{
				music = !music;
				if (gameing)
					if (!music)
						PlaySound(NULL, NULL, SND_FILENAME);
					else
						if (difficulty <= 5)
							PlaySound((LPCTSTR)IDR_WAVE1, NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
						else
							if (difficulty <= 10)
								PlaySound((LPCTSTR)IDR_WAVE2, NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
							else
								PlaySound((LPCTSTR)IDR_WAVE3, NULL, SND_RESOURCE | SND_ASYNC | SND_LOOP);
				insertMove(4, 30);
				if (music)
					cout << "��";
				else
					cout << "��";
			}break;
			case '2':
			{
				sound = !sound;
				insertMove(4, 54);
				if (sound)
					cout << "��";
				else
					cout << "��";
			}break;
			case '3':
			{
				shadowShow = !shadowShow;
				insertMove(8, 34);
				if (shadowShow)
					cout << "��";
				else
					cout << "��";
			}break;
			case '4':
			{
				bigBlock = !bigBlock;
				insertMove(8, 62);
				if (bigBlock)
					cout << "��";
				else
					cout << "��";
			}break;
			case '5':
			{
				char choice;
				system("cls");
				cout << "\n\n\n\n\n\t\t\t\t��ѡ�񷽿���\n\n\n\n\n\t\t\t\t    1:��ɫ\n\n\n\t\t\t\t    2:��ɫ\n\n\n\t\t\t\t    3:���ֿ�";
				do
					choice = _getch(); while (!(choice >= '1'&&choice <= '3'));
				if (sound&& (!gameing || !music))
					PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
				blockstyle = (style)(choice - '1');
				system("cls");
				for (int i = 1; i <= 10; ++i)
					cout << endl;
				cout << "\t\t\t  ���óɹ���";
				system("pause");
				system("cls");
			}break;
			case '6':
			{
				system("cls");
				insertMove(8, 32);
				cout << "ȷ��Ҫ��ô����\n\n\n\n\t\t\t    S:ȷ��\t    B:����";
				char choice;
				do
					choice = _getch(); while (choice != 's'&&choice != 'S'&&choice != 'b'&&choice != 'B');
				if (sound && (!gameing || !music))
					PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
				if (choice == 's' || choice == 'S')
				{
					rScores();
					system("cls");
					for (int i = 1; i <= 10; ++i)
						cout << endl;
					cout << "\t\t\t  ������ɣ�";
					system("pause");
				}
				system("cls");
			}break;
			case '7':
			{
				system("cls");
				mode choice;
				do
				{
					choice = selectMode(gameing);
					system("cls");
					if (choice)
					{
						help(choice);
						insertMove(23, 37);
						cout << "B:����";
						char choice;
						do
							choice = _getch(); while (choice != 'b' && choice != 'B');
						if (sound && (!gameing || !music))
							PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
						system("cls");
					}
				} while (choice);
			}break;
			case '8':updateShow(gameing); break;
			}
		} while (choice >= '1'&&choice <= '4');
	} while (choice != 'b'&&choice != 'B');
}

void gameboard::help(mode gamemode)
{
	switch (gamemode)
	{
	case NORMAL:
	{
		cout << "\n\n����ģʽ������" << endl << endl << endl;
		cout << "    ����ģʽ����������˹������Ϸ������ͬ��ÿ�β���һ�������ĸ�С����Ĵ󷽿��䵽���ʵĵص㣬���ճ��������������" << endl << endl << endl;
		cout << "    �Ѷȣ��ѶȻ�Ӱ�������ٶȺ͵÷֣��Ѷ�Խ�������ٶ�Խ�죬��ͬ�����õķ���Խ��" << endl << endl << endl;
		cout << "�ӷֹ���1. ������ʱ���������ֱ����ض����ж���ӷ֣�����ֵ��С" << endl << endl;
		cout << "          2. �����������мӷ֣�һ������������Խ�൥λ�����õķ�Խ��" << endl << endl << endl;
		cout << "ʧ��������������ѻ��������м�λ��ʱ���ж�ʧ��";
	}break;
	case MOVE:
	{
		cout << "\n\n\n\n\nƯ��ģʽ������" << endl << endl << endl;
		cout << "    Ư��ģʽ��ԭ��Ϸ�����������ȫ������ƽ�ƹ���" << endl << endl << endl;
		cout << "    �Ѷȣ��ѶȻ����Ӱ�����з�����ƶ�����" << endl << endl << endl;
		cout << "    Ư�ƣ�ÿ���󷽿���غ���Ļ�����з��齫�����ƶ�1/2/3��";
	}break;
	case GRAVITY:
	{
		cout << "\n\n\n\n\n\n����ģʽ������" << endl << endl << endl;
		cout << "    ����ģʽ�Դ󷽿�Ϊ��λ������������ʱ�����䣬�󷽿鱻�ƻ��������С�鵥������������" << endl << endl << endl;
		cout << "    ������ÿ���󷽿���غ󣬵�λ�����������������䣬��ʱ���ճ����н������Ҽӷֹ���ͬ�û��������";
	}break;
	case LASER:
	{
		cout << "\n\n����ģʽ������" << endl << endl << endl;
		cout << "    ����ģʽ�����ڷ�������ͬʱ������Ҳ�����ƶ���Ҫ���ٶ�" << endl << endl << endl;
		cout << "    �Ѷȣ��Ѷ�Խ�߼��������ٶ�Խ��(�뷽����Ȼ�����ٶȳ�����)�������ʼλ��Խ�ͣ������˼�������Խǿ" << endl << endl << endl;
		cout << "ʧ��������1. ������ѻ��������м�λ��ʱʧ��(һ�㲻��������)" << endl << endl;
		cout << "          2. ������������˼���󼤹���ɨ��������ֱ��ʧ��" << endl << endl << endl;
		cout << "    ���⣺���������ڶ����1/2/3�У������ٶ��Ƿ����1/3����������غ����˼���һ���������������ÿ�л���3/4/5�񣬵������˵���һ��";
	}break;
	case DELAY:
	{
		cout << "\n\n\n\n�ӳ�ģʽ������(�Ʋ�)" << endl << endl << endl;
		cout << "    �ӳ�ģʽ�÷�������󲻻�������������" << endl << endl << endl;
		cout << "    �Ѷȣ��ѶȻ�Ӱ�첽�����ڣ��Ѷ�Խ������Խ��" << endl << endl << endl;
		cout << "�ӷֹ�������ʱ��λ�е÷��ǹ̶��ģ��������������ı�" << endl << endl << endl;
		cout << "    �ӳ٣�ÿ����4/8/12���󷽿飬����һ�Σ��������е�����";
	}break;
	case GUSH:
	{
		cout << "\n\n\n\n\nȪӿģʽ������(�Ʋ�)" << endl << endl << endl;
		cout << "    Ȫӿģʽ����һ���Ʋ����ڽ�����ӵײ�����һ�з����з��飬������" << endl << endl << endl;
		cout << "    �Ѷȣ��ѶȻ�Ӱ��Ʋ����ںͳ��ֵķ���ȱ�������Ѷ�Խ������Խ�̣�ȱ��Խ��" << endl << endl << endl;
		cout << "    Ȫӿ��ÿ����8/6/4���󷽿飬����һ�Σ��ӵͶ�һ��ð�����ຬ��1/2/3��ȱ�ڵķ���";
	}break;
	case CHASM:
	{
		cout << "\n\n\n\n��Ԩģʽ������(����)" << endl << endl << endl;
		cout << "    ��Ԩģʽ�����е��棬���Ǻ������ɸ��շ��飬�û���Ҫ������Щ����ƽ̨�Խ�����Ϸ���䵽����ķ������ʧ" << endl << endl << endl;
		cout << "�ӷֹ���������ʱ���������ֱ��������󷽿����·������֮���򲻻����ӷ�" << endl << endl << endl;
		cout << "    ��Ԩ��������м�ƫ��λ������1��5�����飬����ʱ��Щ���鲻���������ײ���������ŷ��飬����ȥ�ķ���ֱ����ʧ";
	}break;
	case FROZEN:
	{
		cout << "\n\n\n\n����ģʽ������(���� + �Ʋ�)" << endl << endl << endl;
		cout << "    ����ģʽ����һ���Ʋ����ں�Գ������з������һ�α���" << endl << endl << endl;
		cout << "    �Ѷȣ��ѶȻ�Ӱ��Ʋ�����" << endl << endl << endl;
		cout << "    ������1. ÿ����8/6/4���󷽿飬����һ�Σ���ȫ��������б���" << endl << endl;
		cout << "          2. �Ѿ��������εķ��鲻���ܵ�����Ч��������������Ӱ���ҵ���������(����ԭ���Ľṹ)��������ʱ������ʧ���Ǳ�Ϊ����һ�ε�״̬";
	}break;
	case DARKNESS:
	{
		cout << "\n\n\n\n\n�ڰ�ģʽ������" << endl << endl << endl;
		cout << "    �ڰ�ģʽ���û���������������������������ķ���" << endl << endl << endl;
		cout << "    �ڰ���1. �󷽿���������У������еķ��齫��������״̬" << endl << endl;
		cout << "          2. ÿ������󣬽�������ʾ���з��飬������Խ��ͣ��Խ��";
	}break;
	case DEVIDE:
	{
		cout << "\n\n\n\n����ģʽ������" << endl << endl << endl;
		cout << "    ����ģʽ����Ļһ��Ϊ����������÷�Χ������" << endl << endl << endl;
		cout << "ʧ��������������ѻ�����ǰ�����Ķ����м�λ��ʱ���ж�ʧ��" << endl << endl << endl;
		cout << "    ���ѣ�1. ���������󷽿�������ƫ��λ�ã����������ƶ����Ұ벿��" << endl << endl;
		cout << "          2. ��ż�����󷽿�������ƫ��λ�ã����������ƶ�����벿��";
	}
	}
}

void gameboard::updateShow(bool gameing)
{
	static unsigned short page = 1;
	char choice;
	do
	{
		system("cls");
		switch (page)
		{
		case 1:cout << "2019.07.10 20:23 Զ�Ű�alpha1\n����:\n1. ��Ϸ�Ѷ������֣��Ѷ�Խ�������ٶ�Խ��\n2. �������а����˳�ʱ���Ա��棬��ֱ�ӹرմ��ڲ��ᱣ��\n����:\n1. �ԴӼ���ʱ��֮��һֱ���ڵ���������(����˻�������)\n2. ��������bug(��δ����)\n\n\n2019.07.10 22:00 Զ�Ű�alpha2\n˵��:\n1. �������������Ļ�����ǻ��кۼ�\n2. żȻ���ֵ���bug��δ����ԭ��\n\n\n2019.07.10 22:19 Զ�Ű�alpha3\n˵��:\n�޸��˳�����bug"; break;
		case 2:cout << "2019.07.11 09:37 Զ�Ű�alpha4\n˵��:\nȫ���Ż�����\n1. �������Ϊ���ֿ���ʾ�����ҿ����������Ӧ��״����\n2. ��һ�������������⣬���ع�꣬�����кۼ�\n\n\n2019.07.11 14:00 Զ�Ű�alpha5\n˵��:\n1. ���������BGM����Ӧ��ͬ�Ѷ�\n2. �����������￪�����ֻ��������а�\n3. �޸���������ʱֱ��ռ�ݾɷ����bug\n����:\n�����ļ�ʹ��WAV��ʽ��̫���³������\n\n\n2019.07.11 14:54 Զ�Ű�alpha6\n����������\n1. ��������������������������ɫ������ȱ�ٵĳ�ɫ�û�ɫ����\n2. �û���ס�����������Ư�ƣ������������ٶ��ƶ�����������ģʽ���ӶԵ������ķ�ֵ"; break;
		case 3:cout << "2019.07.11 16:43 Զ�Ű�alpha6.5\n���Ա�����ɫ���в�ɫ����������ǶԴ����������\n\n\n2019.07.11 20:54 �Ŵ���beta1\n�Ż����ڣ��̶���С\n\n\n2019.07.11 22:38 �Ŵ���beta1.1\n1. ��������ﵽһ���̶�ʱ�Ѷ����ӹ���\n2. �������ﵽ���а����ʱ����ʾ��ϲ����Ϣ\n����:\n��Ҫ�Ż����뷨����ʧ����\n\n\n2019.07.12 08:59 �Ŵ���beta1.2\n�ı�̶�����"; break;
		case 4:cout << "2019.07.13 15:16 �Ŵ���beta2\n1. ȡ���˷�������һ��ֵʱ�ļ���Ч��\n2. �����������ã��޸��ڲ���ʱ��ɵ��������bug(����ģʽ�������ѣ�)\n3. ����������ѡ�񷽿����ѡ�����Ĺ��ֿ�����ˣ�\n4. �ڷ���̶������˸���ѣ���Ҳ���õ��Ĳ�֪���Ƿ��Ѿ��̶�������ֲв�����\n5. �޸�������ͣ�������bug\n6. �����1 - 15�����Ѷ�\n7. �������������а�ʱ�ᷢ����ʾ�����������ڵ�һ��\n8. (�д���֤)�޸��˴���żȻ�쳣״̬��\n9. ���а��ļ���Ϊd��\n\n\n2019.07.14 08:54 �Ŵ���beta2.1\n1. ��������Ч(��ѡ��ʱ������Ϸ�����У������о������˻ᷳ�����˾�����)\n2. ������صص���ʾ����Ҳ���õ��Ŀ�������\n3. ����̶�˲�佫������������˸"; break;
		case 5:cout << "2019.07.14 17:31 �Ŵ���beta2.2\n1. ȫ����¼Ʒ�ϵͳ���Ѷ�Խ�ߵ÷�Խ��\n2. �Ż����а�ʱ�̱��棬�Ҽ�¼�Ѷȣ���ͬ�汾�Ʒ��ļ���ͬ\n3. ��һ���Ż����ڣ����������ڽӽ�����λ��\n4. ֧����Ϸ�����ò��ҿ���ֱ�ӽ�����Ϸ\n5. ����Ϸ�����ʾ��Ϣ�ֲ���һֱ�����Ŀհ�\n�޸�:\n���ڴ�С�͹��ż���쳣(���ܲ�û���޸���Ŀǰû�з���)\n\n\n2019.07.15 08:25 �Ŵ���beta2.2.1\n�޸�:\n����Ϸ�����÷�����Ϸʱ����ʾ��Ӱ\n\n\n2019.07.15 17:19 �Ŵ���beta3(�����ڲ�д����beta2.3)\n������:\n1. ������ģʽ\"Ư��\"������ѡ��ģʽѡ��\n2. ���а���¼ģʽ\nbug:\nżȻ������ʾ�������⣬��������һ�Σ�����δ����ԭ��δ�޸�"; break;
		case 6:cout << "2019.07.15 21:15 �Ŵ���beta3.5\n������һ�α�ֵ�������������\n����:\n����������Լӷ�\n�Ż�(�ӻ�):\n�������ʴ�󽵵ͣ������⽫����Ϸ�����С������(��֪���㲻���������)\n�޸�:\nƯ��ģʽƯ�ƾ��벻���ϸ����Ѷ�\n\n\n2019.07.16 20:46 �Ŵ���beta4\n1. ��ʾ�����Ż����棬��ʱ��ܶ�\n2. ������ģʽ\"����\"��������ģʽ��(Ȼ���������̱�Ԥ���и��ӵö�)\n3. ���п�����δ���ֵ�bug\n\n\n2019.07.17 08:10 �Ŵ���beta4.2\n���޸�������ʾ����ʾbug"; break;
		case 7:cout << "2019.07.17 10:31 �Ŵ���beta4.4\n�޸��˳ɶֵ�����bug:\n1. ͬ����ճ������\n2. ���������µ�������ʧȥ����\n\n\n2019.07.17 17:38 �Ŵ���beta4.6\nû�������Ǹ���bug�İ汾\n1. ��һ���޸�����bug�����ܺ������ᷢ��\n2. ������˵���е�Ư�Ƹ�Ϊ�ƶ�\n3. ���Ư��ģʽ�µĶ���Ч��\n\n\n2019.07.21 21:43 �Ŵ���beta5\n1. ������ģʽ���⣬������δ֪bug(��������ģʽ���ɵ�Ҳ�п��ܳ���bug��Ϊ����һ�¸���)\n2. �޸����а񣬲�ͬģʽ�ֲ�ͬ���а�\n3. ��ӷ��鳬����ʾ\n4. ��Ϸ���Ƹ�Ϊ����˹�������"; break;
		case 8:cout << "2019.07.21 22:02 �Ŵ���beta5.5(��������İ汾����)\n��Ϸ����ʱ��ʾ�Ż�\n\n\n2019.07.22 11:21 �Ŵ���beta6\n��������ģʽ\n\n\n2019.07.22 13:54 �Ŵ���beta7\n��������ģʽ\n\n\n2019.07.23 23:47 �Ŵ���beta8(��ҹ������)\n1. ������ģʽ\"��Ԩ\"��������δ֪bug\n2. �ڴ��ͷ��Ż�������̶ȼ����ڴ�й¶\n3. �Ż�\"Ȫӿ\"����"; break;
		case 9:cout << "2019.07.24 16:53 �Ŵ���beta8.5\n��Ҫ�޸�һЩbug\n1. �޸���ģʽ����Ԩ���鲻��ȫ����bug\n2. �޸���ģʽ�ķ���Ԩ��������bug\n3. �޸�����ѻ�������Ϸ������bug\n\n\n2019.07.25 10:12 �Ŵ���beta9\n1. ������ģʽ\"����\"�����鷽����ѡ���ɫ����ɫ\n2. �Ż�\"��Ԩ\"�����з�ʽ\n3. ���ӿ�������ʾ(ֻ��һ����QAQ)\n\n\n2019.07.25 23:02 �Ŵ���beta9.5\n1. �����޸�����ģʽ�ĸ���bug\n2. ��Ӱ������ܺ͸�����־\n3. �޸���Ϸ��ѡ����BGM��bug"; break;
		case 10:cout << "2019.07.28 08:45 �Ŵ���beta10\n1. ������ģʽ\"�ڰ�\"��������һЩbug\n2. ȡ���������Ѷ�(�Լ�����ȥ��)\n\n\n2019.07.28 11:32 ���԰�1.0-pre\n1. ������ģʽ\"����\"��������δ֪bug������ģʽ�������\n2. �޸���һ��ģʽ��ʧ����ʾbug\n\n\n2019.07.28 18:08 ���԰�1.0-pre2\n�޸�һ�������bug����bug�����ڵ���һ���汾Ϊֹ�ļ������йŴ��汾��Ȼ��ֱ����һ���汾֮ǰ��˿��û�б����֣���νbugʷ�ϵ��漣:\n�����������Ϸ�û���κη���ʱ�ᵼ�³������"; break;
		}
		insertMove(21, 27);
		cout << "A:��һҳ    " << setw(2) << page << "    D:��һҳ";
		insertMove(23, 37);
		cout << "B:�˳�";
		do
			choice = _getch(); while (choice != 'b'&&choice != 'B' && !((choice == 'a' || choice == 'A') && page != 1) && !((choice == 'd' || choice == 'D') && page != 10));
		if (choice == 'a' || choice == 'A')
		{
			if (sound && (!gameing || !music))
				PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
			--page;
		}
		if (choice == 'd' || choice == 'D')
		{
			if (sound && (!gameing || !music))
				PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
			++page;
		}
	} while (choice != 'b'&&choice != 'B');
	if (sound && (!gameing || !music))
		PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
	system("cls");
}

gameboard::gameboard() : music(1), sound(1), current(NONE)
{
	ifstream file;
	file.open(locate, ios::binary | ios::in | ios::_Nocreate);
	if (file.is_open())
		for (int j = 1; j <= 10; ++j)
			for (int i = 1; i <= 10; ++i)
				file >> scores[j][SCORE][i] >> scores[j][LINE][i] >> scores[j][DIFFICULTY][i];
	else
		rScores();
}

void gameboard::menu()
{
	char choice;
	while (1)
	{
		choice = beginning();
		system("cls");
		switch (choice)
		{
		case '1':
		{
			bool flag = 1;
			do
			{
				current = selectMode();
				system("cls");
				if (current&& selectGame())
				{
					flag = 0;
					system("cls");
					gameStart();
				}
				system("cls");
			} while (flag&&current);
		}break;
		case '2':
		{
			mode choice;
			do
			{
				choice = selectMode();
				system("cls");
				if (choice)
				{
					showScores(choice);
					insertMove(23, 37);
					cout << "B:����";
					char choice;
					do
						choice = _getch(); while (choice != 'b' && choice != 'B');
					if (sound)
						PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
					system("cls");
				}
			} while (choice);
		}break;
		case '3':settings(); break;
		case '4':return;
		}
		system("cls");
	}
}