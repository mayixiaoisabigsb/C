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
			cout << "   游戏已暂停\n\n    P:继续\n\n    S:选项\n\n    B:结束游戏";
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
	cout << "游戏结束";
	if (i != 10)
	{
		cout << "\t      恭喜你成为了排行榜的第" << i + 1 << "名！";
		save();
	}
	cout << "\n\t\t是否重来?   Y:是    N:否";
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
	cout << "\n\t名次" << setw(20) << "分数" << setw(20) << "行数" << setw(20) << "难度" << '\n';
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
	cout << "版本号：" << version;
	insertMove(0, 62);
	cout << "开发者：哞菇哞菇哞";
	char choice;
	cout << "\n\n\n\n\t\t\t  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	cout << "俄  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	cout << "罗  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "斯  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	cout << "方  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "块  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << "革  ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	cout << "命\n\n\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << "\t\t\t\t  1:开始游戏\n\n\n\t\t\t\t  2:查看排行榜\n\n\n\t\t\t\t  3:选项\n\n\n\t\t\t\t  4:退出游戏" << endl;
	cout << "\n\n\t    温馨提示:1.由于输入法未优化，请在游戏前将输入法调整为英文!\n\t\t     2.禁用鼠标，否则会产生奇妙的效果";
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
	cout << "请选择游戏模式\n\n\n\t\t\t    1.经典\t    2.漂移\n\n\n\t\t\t    3.引力\t    4.激光\n\n\n\t\t\t    5.延迟\t    6.泉涌\n\n\n\t\t\t    7.深渊\t    8.冰冻\n\n\n\t\t\t    9.黑暗\t    0.分裂\n\n\n\t\t\t\t    B:返回";
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
	cout << "\n\n\n\n\n\t\t\t\t请选择游戏难度\n\n\n\n\n\n\n\n\n\n\t\tA:向前选择    D:向后选择    S:确定    B:返回";
	do
	{
		insertMove(9, 37);
		if (difficulty <= 5)
			cout << "简单";
		else
			if (difficulty <= 10)
				cout << "普通";
			else
				cout << "困难";
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
		cout << "\n\n\n\n\t\t      1:音乐  ";
		if (music)
			cout << "开";
		else
			cout << "关";
		cout << "\t      2:音效  ";
		if (sound)
			cout << "开";
		else
			cout << "关";
		cout << "\n\n\n\n\t\t      3:显示阴影  ";
		if (shadowShow)
			cout << "开";
		else
			cout << "关";
		cout << "\t      4:方块超大显示  ";
		if (bigBlock)
			cout << "开";
		else
			cout << "关";
		cout << "\n\n\n\n\t\t      5:调整方块风格\t      6:重置排行榜\n\n\n\n\t\t      7:帮助\t\t      8:更新日志\n\n\n\n\t\t\t\t      B:返回\n\n\n";
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
					cout << "开";
				else
					cout << "关";
			}break;
			case '2':
			{
				sound = !sound;
				insertMove(4, 54);
				if (sound)
					cout << "开";
				else
					cout << "关";
			}break;
			case '3':
			{
				shadowShow = !shadowShow;
				insertMove(8, 34);
				if (shadowShow)
					cout << "开";
				else
					cout << "关";
			}break;
			case '4':
			{
				bigBlock = !bigBlock;
				insertMove(8, 62);
				if (bigBlock)
					cout << "开";
				else
					cout << "关";
			}break;
			case '5':
			{
				char choice;
				system("cls");
				cout << "\n\n\n\n\n\t\t\t\t请选择方块风格\n\n\n\n\n\t\t\t\t    1:彩色\n\n\n\t\t\t\t    2:无色\n\n\n\t\t\t\t    3:国字框";
				do
					choice = _getch(); while (!(choice >= '1'&&choice <= '3'));
				if (sound&& (!gameing || !music))
					PlaySound((LPCTSTR)IDR_WAVE5, NULL, SND_RESOURCE | SND_ASYNC);
				blockstyle = (style)(choice - '1');
				system("cls");
				for (int i = 1; i <= 10; ++i)
					cout << endl;
				cout << "\t\t\t  设置成功，";
				system("pause");
				system("cls");
			}break;
			case '6':
			{
				system("cls");
				insertMove(8, 32);
				cout << "确定要这么做吗？\n\n\n\n\t\t\t    S:确定\t    B:返回";
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
					cout << "\t\t\t  重置完成，";
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
						cout << "B:返回";
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
		cout << "\n\n经典模式帮助：" << endl << endl << endl;
		cout << "    经典模式与其他俄罗斯方块游戏规则相同，每次操作一个含有四个小方块的大方块落到合适的地点，若凑成满行则此行消除" << endl << endl << endl;
		cout << "    难度：难度会影响下落速度和得分，难度越高下落速度越快，相同操作得的分数越高" << endl << endl << endl;
		cout << "加分规则：1. 在下落时加速下落或直接落地都会有额外加分，但分值较小" << endl << endl;
		cout << "          2. 消除行数会有加分，一次性消除行数越多单位行数得的分越多" << endl << endl << endl;
		cout << "失败条件：当方块堆积到顶部中间位置时便判断失败";
	}break;
	case MOVE:
	{
		cout << "\n\n\n\n\n漂移模式帮助：" << endl << endl << endl;
		cout << "    漂移模式在原游戏基础上添加了全部方块平移功能" << endl << endl << endl;
		cout << "    难度：难度会额外影响已有方块的移动距离" << endl << endl << endl;
		cout << "    漂移：每当大方块落地后，屏幕中所有方块将向左移动1/2/3格";
	}break;
	case GRAVITY:
	{
		cout << "\n\n\n\n\n\n引力模式帮助：" << endl << endl << endl;
		cout << "    引力模式以大方块为单位，当整体悬空时会下落，大方块被破坏后脱离的小块单独受引力作用" << endl << endl << endl;
		cout << "    引力：每当大方块落地后，单位方块受引力吸引下落，此时若凑成整行将消除且加分规则同用户操作落地";
	}break;
	case LASER:
	{
		cout << "\n\n激光模式帮助：" << endl << endl << endl;
		cout << "    激光模式将会在方块下落同时激光束也向下移动，要求速度" << endl << endl << endl;
		cout << "    难度：难度越高激光下落速度越快(与方块自然下落速度成正比)，激光初始位置越低，但击退激光能力越强" << endl << endl << endl;
		cout << "失败条件：1. 当方块堆积到顶部中间位置时失败(一般不会这样死)" << endl << endl;
		cout << "          2. 当方块下落击退激光后激光仍扫到方块则直接失败" << endl << endl << endl;
		cout << "    激光：激光生成于顶层的1/2/3行，下落速度是方块的1/3倍，方块落地后会击退激光一格，若有消行则额外每行击退3/4/5格，但最多击退到第一行";
	}break;
	case DELAY:
	{
		cout << "\n\n\n\n延迟模式帮助：(计步)" << endl << endl << endl;
		cout << "    延迟模式让方块下落后不会立刻消除整行" << endl << endl << endl;
		cout << "    难度：难度会影响步数周期，难度越高周期越长" << endl << endl << endl;
		cout << "加分规则：消除时单位行得分是固定的，不随消除总数改变" << endl << endl << endl;
		cout << "    延迟：每操作4/8/12个大方块，触发一次，消除所有的整行";
	}break;
	case GUSH:
	{
		cout << "\n\n\n\n\n泉涌模式帮助：(计步)" << endl << endl << endl;
		cout << "    泉涌模式将在一个计步周期结束后从底部出现一行非整行方块，可消除" << endl << endl << endl;
		cout << "    难度：难度会影响计步周期和出现的方块缺口数，难度越高周期越短，缺口越多" << endl << endl << endl;
		cout << "    泉涌：每操作8/6/4个大方块，触发一次，从低端一行冒出至多含有1/2/3个缺口的方块";
	}break;
	case CHASM:
	{
		cout << "\n\n\n\n深渊模式帮助：(引力)" << endl << endl << endl;
		cout << "    深渊模式不含有地面，而是含有若干浮空方块，用户需要依靠这些方块搭建平台以进行游戏，落到下面的方块会消失" << endl << endl << endl;
		cout << "加分规则：在下落时加速下落或直接落地若大方块正下方无落脚之处则不会额外加分" << endl << endl << endl;
		cout << "    深渊：随机在中间偏下位置生成1至5个方块，消行时这些方块不会消除，底部不再有落脚方块，掉下去的方块直接消失";
	}break;
	case FROZEN:
	{
		cout << "\n\n\n\n冰冻模式帮助：(引力 + 计步)" << endl << endl << endl;
		cout << "    冰冻模式将在一个计步周期后对场上所有方块进行一次冰冻" << endl << endl << endl;
		cout << "    难度：难度会影响计步周期" << endl << endl << endl;
		cout << "    冰冻：1. 每操作8/6/4个大方块，触发一次，对全场方块进行冰冻" << endl << endl;
		cout << "          2. 已经冻结两次的方块不会受到冰冻效果，不会受引力影响且单独受引力(打乱原来的结构)，在消行时不会消失而是变为冰冻一次的状态";
	}break;
	case DARKNESS:
	{
		cout << "\n\n\n\n\n黑暗模式帮助：" << endl << endl << endl;
		cout << "    黑暗模式让用户看不见除操作方块所在列以外的方块" << endl << endl << endl;
		cout << "    黑暗：1. 大方块下落过程中，其他列的方块将进入隐藏状态" << endl << endl;
		cout << "          2. 每次下落后，将短暂显示所有方块，消行数越多停留越长";
	}break;
	case DEVIDE:
	{
		cout << "\n\n\n\n分裂模式帮助：" << endl << endl << endl;
		cout << "    分裂模式把屏幕一分为二，方块放置范围大大减少" << endl << endl << endl;
		cout << "失败条件：当方块堆积到当前半屏的顶部中间位置时便判断失败" << endl << endl << endl;
		cout << "    分裂：1. 第奇数个大方块生成在偏左位置，它将不能移动到右半部分" << endl << endl;
		cout << "          2. 第偶数个大方块生成在偏右位置，它将不能移动到左半部分";
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
		case 1:cout << "2019.07.10 20:23 远古版alpha1\n功能:\n1. 游戏难度有三种，难度越高下落速度越快\n2. 设有排行榜，在退出时可以保存，但直接关闭窗口不会保存\n不足:\n1. 自从加入时间之后一直存在的闪屏问题(玩久了会得青光眼)\n2. 长条方块bug(尚未发现)\n\n\n2019.07.10 22:00 远古版alpha2\n说明:\n1. 改善了青光眼屏幕，但是还有痕迹\n2. 偶然发现的新bug尚未发现原因\n\n\n2019.07.10 22:19 远古版alpha3\n说明:\n修复了长条的bug"; break;
		case 2:cout << "2019.07.11 09:37 远古版alpha4\n说明:\n全面优化界面\n1. 将方块改为国字框显示，并且框内字与其对应性状相似\n2. 进一步改善闪屏问题，隐藏光标，但仍有痕迹\n\n\n2019.07.11 14:00 远古版alpha5\n说明:\n1. 添加了三种BGM，对应不同难度\n2. 可以在设置里开关音乐或重置排行榜\n3. 修改了在生成时直接占据旧方块的bug\n不足:\n音乐文件使用WAV格式，太大导致程序过大\n\n\n2019.07.11 14:54 远古版alpha6\n多彩世界更新\n1. 界面字体更清晰，方块添加了颜色！不过缺少的橙色用灰色代替\n2. 用户按住方向键将不会漂移，而是以正常速度移动，这让困难模式更加对得起它的分值"; break;
		case 3:cout << "2019.07.11 16:43 远古版alpha6.5\n仅对标题颜色进行彩色化，更多的是对代码进行整理\n\n\n2019.07.11 20:54 古代版beta1\n优化窗口，固定大小\n\n\n2019.07.11 22:38 古代版beta1.1\n1. 加入分数达到一定程度时难度增加功能\n2. 当分数达到排行榜榜首时会提示恭喜的信息\n不足:\n想要优化输入法，但失败了\n\n\n2019.07.12 08:59 古代版beta1.2\n改变固定标题"; break;
		case 4:cout << "2019.07.13 15:16 古代版beta2\n1. 取消了分数高于一定值时的加速效果\n2. 调整按键设置，修复在操作时造成的下落减缓bug(困难模式更加困难！)\n3. 设置里增加选择方块风格的选项，经典的国字框回来了！\n4. 在方块固定后会闪烁提醒，再也不用担心不知道是否已经固定而造成手残操作了\n5. 修复了在暂停后的闪屏bug\n6. 添加了1 - 15更多难度\n7. 当分数能上排行榜时会发出提示，而不仅限于第一名\n8. (有待验证)修复了窗口偶然异常状态？\n9. 排行榜文件改为d盘\n\n\n2019.07.14 08:54 古代版beta2.1\n1. 增加了音效(仅选择时，非游戏过程中，不过感觉听久了会烦，关了就行了)\n2. 增加落地地点提示，再也不用担心看串列了\n3. 方块固定瞬间将高亮而不是闪烁"; break;
		case 5:cout << "2019.07.14 17:31 古代版beta2.2\n1. 全面更新计分系统，难度越高得分越多\n2. 优化排行榜，时刻保存，且记录难度，不同版本计分文件不同\n3. 进一步优化窗口，将窗口设在接近居中位置\n4. 支持游戏内设置并且可以直接结束游戏\n5. 在游戏左侧显示信息弥补了一直以来的空白\n修复:\n窗口大小和光标偶尔异常(可能并没有修复，目前没有发现)\n\n\n2019.07.15 08:25 古代版beta2.2.1\n修复:\n从游戏内设置返回游戏时不显示阴影\n\n\n2019.07.15 17:19 古代版beta3(程序内部写成了beta2.3)\n新内容:\n1. 增加新模式\"漂移\"，并有选择模式选项\n2. 排行榜会记录模式\nbug:\n偶然发现显示滞留问题，但仅出现一次，且尚未发现原因，未修复"; break;
		case 6:cout << "2019.07.15 21:15 古代版beta3.5\n分数再一次贬值，收入过万不是梦\n新增:\n加速下落可以加分\n优化(劣化):\n音乐音质大大降低，不过这将让游戏本身大小大大减少(我知道你不是来听歌的)\n修复:\n漂移模式漂移距离不是严格按照难度\n\n\n2019.07.16 20:46 古代版beta4\n1. 显示窗口优化界面，但时间很短\n2. 增加新模式\"引力\"，比正常模式简单(然而开发过程比预想中复杂得多)\n3. 极有可能有未发现的bug\n\n\n2019.07.17 08:10 古代版beta4.2\n仅修复方块提示的显示bug"; break;
		case 7:cout << "2019.07.17 10:31 古代版beta4.4\n修复了成吨的引力bug:\n1. 同方块粘滞现象\n2. 引力作用下的消除后失去引力\n\n\n2019.07.17 17:38 古代版beta4.6\n没错，这又是个改bug的版本\n1. 进一步修复引力bug，可能后续还会发现\n2. 将操作说明中的漂移改为移动\n3. 添加漂移模式下的动画效果\n\n\n2019.07.21 21:43 古代版beta5\n1. 增加新模式激光，可能有未知bug(不仅是新模式，旧的也有可能出现bug因为改了一下根基)\n2. 修改排行榜，不同模式分不同排行榜\n3. 添加方块超大显示\n4. 游戏名称改为俄罗斯方块革命"; break;
		case 8:cout << "2019.07.21 22:02 古代版beta5.5(结果又忘改版本号了)\n游戏结束时显示优化\n\n\n2019.07.22 11:21 古代版beta6\n仅增加新模式\n\n\n2019.07.22 13:54 古代版beta7\n仅增加新模式\n\n\n2019.07.23 23:47 古代版beta8(深夜党福利)\n1. 增加新模式\"深渊\"，可能有未知bug\n2. 内存释放优化，极大程度减少内存泄露\n3. 优化\"泉涌\"界面"; break;
		case 9:cout << "2019.07.24 16:53 古代版beta8.5\n主要修复一些bug\n1. 修复新模式的深渊方块不完全消除bug\n2. 修复新模式的非深渊方块消除bug\n3. 修复方块堆积导致游戏崩溃的bug\n\n\n2019.07.25 10:12 古代版beta9\n1. 增加新模式\"冰冻\"，建议方块风格选择彩色或无色\n2. 优化\"深渊\"的消行方式\n3. 增加开发者显示(只有一个人QAQ)\n\n\n2019.07.25 23:02 古代版beta9.5\n1. 可能修复了新模式的浮空bug\n2. 添加帮助功能和更新日志\n3. 修复游戏中选项打断BGM的bug"; break;
		case 10:cout << "2019.07.28 08:45 古代版beta10\n1. 增加新模式\"黑暗\"，可能有一些bug\n2. 取消了主观难度(自己体验去吧)\n\n\n2019.07.28 11:32 测试版1.0-pre\n1. 增加新模式\"分裂\"，可能有未知bug，所有模式更新完成\n2. 修复上一个模式的失败显示bug\n\n\n2019.07.28 18:08 测试版1.0-pre2\n修复一个惊天大bug，此bug存在于到上一个版本为止的几乎所有古代版本，然而直到上一个版本之前竟丝毫没有被发现，可谓bug史上的奇迹:\n当消除的行上方没有任何方块时会导致程序崩溃"; break;
		}
		insertMove(21, 27);
		cout << "A:上一页    " << setw(2) << page << "    D:下一页";
		insertMove(23, 37);
		cout << "B:退出";
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
					cout << "B:返回";
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