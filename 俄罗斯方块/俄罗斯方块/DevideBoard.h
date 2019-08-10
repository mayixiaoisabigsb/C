#pragma once
#include "board.h"

class DevideBoard :
	public board
{
private:
	bool order;//轮次奇偶性
	bool mayMove(char direction);//不能过线
	bool cross();//过线判断
public:
	bool spawn();//奇偶标记
	DevideBoard();
};