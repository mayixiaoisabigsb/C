#pragma once
#include "board.h"

class GushBoard :
	public board
{
private:
	unsigned short step;//����
	void gush(unsigned short voidnum);
public:
	bool end();//���Ӳ���
	void print();//�����ӡ��������
	GushBoard();
};