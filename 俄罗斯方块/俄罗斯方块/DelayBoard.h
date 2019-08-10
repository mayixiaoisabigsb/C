#pragma once
#include "board.h"

class DelayBoard :
	public board
{
private:
	unsigned short step;//步数
public:
	bool end();//增加步数
	void addScore(unsigned short number);//积分规则改变
	void print();//额外打印步数进度
	DelayBoard();
};