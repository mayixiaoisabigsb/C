#pragma once
#include "board.h"

class GushBoard :
	public board
{
private:
	unsigned short step;//步数
	void gush(unsigned short voidnum);
public:
	bool end();//增加步数
	void print();//额外打印步数进度
	GushBoard();
};