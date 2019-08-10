#pragma once
#include "board.h"

extern unsigned &member(unsigned group[][2], unsigned sign);

class GravityBoard :
	public board
{
protected:
	unsigned supply();//给方块标记，分为不同团体
	unsigned short blockHigh(unsigned short row, unsigned short column);//返回某行某列距地高度
	virtual unsigned short deleteLine();//需要特殊考虑J和L粘滞情况
	virtual bool fall();//引力效果触发，返回是否有方块变化
public:
	virtual void move(char direction, bool artificial = 1);//移动同时继承标记
	virtual bool end();//落地结算后触发引力
	bool spawn();//带标记的生成
	GravityBoard(const string name = "引力");
};