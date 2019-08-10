#pragma once
#include "GravityBoard.h"

class ChasmBoard :
	public GravityBoard
{
private:
	bool fall();//下落，空岛方块不会受重力影响
	unsigned short deleteLine();//不会消除空岛方块
	unsigned short borderLine(unsigned short row, unsigned short column);//返回某位置上方边界方块的行数
public:
	void move(char direction, bool artificial = 1);//加分规则改变
	void print();//不会显示深渊
	void printShadow();//不显示深渊中的影子
	void fix();//深渊方块不会闪烁提示
	bool end();//落下深渊
	ChasmBoard();
};