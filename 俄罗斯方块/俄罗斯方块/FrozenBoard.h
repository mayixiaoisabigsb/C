#pragma once
#include "GravityBoard.h"

class FrozenBoard :
	public GravityBoard
{
private:
	bool fall();//下落，深度冻结方块不会受重力影响
	unsigned short step;//步数
	void froze();//冰冻
	void printBlock(unsigned short row, unsigned short column);//打印某一处
	void printBlock(block *target);//无偏差打印
	void printOld();//新规则
	unsigned short deleteLine();//深度冻结方块解冻
	unsigned short frozenLine(unsigned short row, unsigned short column);//返回某位置上方深度冰冻方块行数
public:
	bool end();
	void print();
	void printNewOnly();
	void printShadow();
	FrozenBoard();
};