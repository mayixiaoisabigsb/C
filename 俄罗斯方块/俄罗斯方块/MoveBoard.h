#pragma once
#include "board.h"

class MoveBoard :
	public board
{
public:
	bool end();//����Ư�ƹ���
	void print();//ȥ���߽�Ĵ�ӡ
	MoveBoard();
};