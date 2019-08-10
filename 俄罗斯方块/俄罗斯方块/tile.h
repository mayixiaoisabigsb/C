#pragma once
#include"block.h"

enum { ROW, COLUMN };

class tile
{
protected:
	short shape[4][2];//记载内含的四个小方块的相对位置[编号][行0列1]
	unsigned short condition;//大方块状态，0为字母形状，按顺时针顺序记其他形状
	short position[2];//编号为零(绝对位置，旋转时不会变坐标)的方块在游戏板上的位置{行数,列数}
	tiletype type;//大方块类型(七种)
	short bottom[4][2];//底端的相对位置(最多四个低端)
	const unsigned short conditonnum;//状态数(相同大方块状态是绝对的)
	unsigned short bottomnum;//底端方块数
public:
	const unsigned short getConditionnum();//返回状态数
	unsigned short getBottomnum();//返回底端方块数
	short getBR(unsigned short number);//返回指定编号的底端方块的绝对行数
	short getBC(unsigned short number);//返回指定编号的底端方块的绝对列数
	short getSR(unsigned short number);//返回指定编号的方块的相对行数
	short getSC(unsigned short number);//返回指定编号的方块的相对列数
	short getR(unsigned short number);//返回指定编号的方块的绝对行数
	short getC(unsigned short number);//返回指定编号的方块的绝对列数
	void move(char direction);//根据指定方向移动
	tiletype getType();//返回方块类型
	virtual void turnAround() = 0;//旋转
	tile(const unsigned short conditionnum, tiletype type);//状态数，方块类型，用于继承
};

class tile_I:public tile
{
public:
	tile_I();
	void turnAround();
};

class tile_J :public tile
{
public:
	tile_J();
	void turnAround();
};

class tile_L :public tile
{
public:
	tile_L();
	void turnAround();
};

class tile_O :public tile
{
public:
	tile_O();
	void turnAround();
};

class tile_S :public tile
{
public:
	tile_S();
	void turnAround();
};

class tile_Z :public tile
{
public:
	tile_Z();
	void turnAround();
};

class tile_T :public tile
{
public:
	tile_T();
	void turnAround();
};