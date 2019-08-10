#pragma once
#include "board.h"

class LaserBoard :
	public board
{
private:
	short laserHigh;//激光高度
	void printOld();//防止刷掉激光
public:
	bool end();//击退激光
	void down();//激光同时下落
	void betterPrint();//防止刷掉激光
	void printNewOnly();//防止刷掉激光
	void printShadow();//影子被激光遮挡
	void laserPrint(bool force = 0);//打印激光，是否强制打印
	LaserBoard();
};