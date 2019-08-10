#pragma once
#include "board.h"

class DarknessBoard :
	public board
{
private:
	void printDark();//只显示光照
public:
	bool end();//消行短暂显示全部画面
	void print();//打印光照范围
	void move(char direction, bool artificial = 1);//打印光照范围
	DarknessBoard();
};