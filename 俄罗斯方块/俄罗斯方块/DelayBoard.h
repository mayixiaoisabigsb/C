#pragma once
#include "board.h"

class DelayBoard :
	public board
{
private:
	unsigned short step;//����
public:
	bool end();//���Ӳ���
	void addScore(unsigned short number);//���ֹ���ı�
	void print();//�����ӡ��������
	DelayBoard();
};