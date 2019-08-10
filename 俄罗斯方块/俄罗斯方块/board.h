#pragma once
#include<string>
#include<Windows.h>
#include"block.h"
#include"tile.h"
using namespace std;

extern unsigned short shadow[4][2];
extern unsigned short difficulty;
extern bool shadowShow;
extern bool bigBlock;

class board
{
protected:
	string name;
	tile *obj;//指向游戏板中唯一活跃的大方块
	block *game[24][12];//游戏面板
	block *next[2][8][7];//下两个方块的信息，用于展示
	tile *nextobj[2];//下两个大方块
	unsigned score;//分数
	unsigned linenum;//消除总行数
	unsigned short weight();//权重，根据难度有得分加成
	unsigned short top();//返回游戏板方块堆积的顶部行数
	unsigned short top(unsigned short column);//返回某一列的顶部行数
	virtual unsigned short deleteLine();//消除满行
	unsigned short high();//返回目前操作方块落地高度
	tile *spawnNew();//随机数生成新大方块
	virtual bool mayMove(char direction);//判断是否可以向指定方向移动
	virtual void printOld();//打印面板，一般用于有变化的模式
public:
	bool start();//开始新的大方块，如果生成失败返回false
	virtual bool end();//大方块落地结算，若游戏不能继续返回false
	virtual void move(char direction, bool artificial = 1);//根据方向移动或变换
	virtual void addScore(unsigned short number);//根据消除行数加分
	unsigned getScore();//返回分数
	unsigned getLinenum();//返回总行数
	virtual void print();//打印面板
	virtual void betterPrint();//更好地打印(很大程度上缓解青光眼)
	virtual void printNewOnly();//只打印新方块并且会对周围刷新，有效缓解青光眼
	virtual void printShadow();//产生影子
	void printScore();//只重印分数
	virtual bool spawn();//生成新方块，若已被占据则生成失败返回false
	virtual void fix();//固定活跃方块，并解除大方块指针对其控制
	virtual void down();//自然下落(其实就是向下移动一格)
	void setblock(unsigned short row, unsigned short column, tiletype target = BORDER);
	bool inDanger();//若活跃大方块落地则返回true
	bool gameover();//若满足失败条件返回true
	board(const string name = "经典");
	virtual ~board();
};