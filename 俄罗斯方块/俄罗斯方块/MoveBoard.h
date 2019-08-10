#pragma once
#include "board.h"

class MoveBoard :
	public board
{
public:
	bool end();//增加漂移功能
	void print();//去除边界的打印
	MoveBoard();
};