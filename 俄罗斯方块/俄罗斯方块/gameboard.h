#pragma once
#include"board.h"
using namespace std;

enum { SCORE, LINE, DIFFICULTY };
enum mode { NONE, NORMAL, MOVE, GRAVITY, LASER, DELAY, GUSH, CHASM, FROZEN, DARKNESS, DEVIDE };

class gameboard
{
private:
	unsigned scores[11][3][11];//分数排行榜(前10名)
	board *mainboard;//一个游戏面板
	long speed;//下落速度
	bool music;//是否有音乐
	bool sound;//是否有音效
	mode current;//当前模式
	void rScores();//重置分数排行榜
	void gameStart();//开始新游戏
	bool playing();//大方块操作中，若满足固定条件返回false
	bool gameover();//游戏结束后用户是否重新开始游戏
	void showScores(mode gamemode);//展示排行榜
	void save();//保存排行榜至文件(D盘下的TetrisScores.bat)
	char beginning();//开始界面，返回选择
	mode selectMode(bool gameing = 0);//选择模式界面，返回模式
	bool selectGame();//选择游戏界面，返回是否开始游戏
	void settings(bool gameing = 0);//设置
	void help(mode gamemode);//帮助
	void updateShow(bool gameing = 0);//更新日志
public:
	void menu();//开始整个游戏操作
	gameboard();//会读取文件中的排行榜修改自己的排行榜，如果没有就全归零
};