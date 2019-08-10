#include<iostream>
#include<Windows.h>
#include "block.h"
using namespace std;

style blockstyle;//������
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
		//����������ɫ����ο���ҳ https://blog.csdn.net/u012424148/article/details/52792472?tdsourcetag=s_pcqq_aiomsg
		switch (type)
		{
		case BORDER:break;
		case I:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); break;//��
		case J:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY); break;//��(��û�У��û�ɫ����)
		case L:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN); break;//��
		case O:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); break;//��
		case S:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE); break;//��
		case Z:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN); break;//��
		case T:SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE); break;//��
		}
		if (bigBlock)
			cout << "��";
		else
			cout << "��";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}break;
	case COLORLESS:
	{
		if (type != BORDER)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		if (bigBlock)
			cout << "��";
		else
			cout << "��";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}break;
	case CLASSIC:
	{
		switch (type)
		{
		case BORDER:cout << "��"; break;
		case I:cout << "��"; break;
		case J:cout << "��"; break;
		case L:cout << "��"; break;
		case O:cout << "��"; break;
		case S:cout << "��"; break;
		case Z:cout << "��"; break;
		case T:cout << "��"; break;
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