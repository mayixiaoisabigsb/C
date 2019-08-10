#include<iostream>
#include<Windows.h>
#include "block.h"
using namespace std;

style blockstyle;//方块风格
extern bool bigBlock;

void block::fix()
{
	active = 0;
}

void block::realease()
{
	active = 1;
}

void block::show()
{
	switch (blockstyle)
	{
	case COLORFUL:
	{
		//以下字体颜色代码参考网页 https://blog.csdn.net/u012424148/article/details/52792472?tdsourcetag=s_pcqq_aiomsg
		switch (type)
		{
		case BORDER:break;
		case I:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); break;//红
		case J:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); break;//橙(并没有，用灰色代替)
		case L:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN); break;//黄
		case O:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); break;//绿
		case S:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); break;//蓝
		case Z:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN); break;//靛
		case T:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE); break;//紫
		}
		if (bigBlock)
			cout << "█";
		else
			cout << "■";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}break;
	case COLORLESS:
	{
		if (type != BORDER)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		if (bigBlock)
			cout << "█";
		else
			cout << "■";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}break;
	case CLASSIC:
	{
		switch (type)
		{
		case BORDER:cout << "囗"; break;
		case I:cout << "囬"; break;
		case J:cout << "团"; break;
		case L:cout << "囜"; break;
		case O:cout << "回"; break;
		case S:cout << "囸"; break;
		case Z:cout << "囝"; break;
		case T:cout << "囨"; break;
		}
	}break;
	}
}

bool block::getActive()
{
	return active;
}

tiletype block::getType()
{
	return type;
}

block::block(tiletype type, bool active, unsigned sign, unsigned sign2) :type(type), active(active), sign(sign), sign2(sign2)
{
}