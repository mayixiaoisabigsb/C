#pragma once
#include "board.h"

class DarknessBoard :
	public board
{
private:
	void printDark();//ֻ��ʾ����
public:
	bool end();//���ж�����ʾȫ������
	void print();//��ӡ���շ�Χ
	void move(char direction, bool artificial = 1);//��ӡ���շ�Χ
	DarknessBoard();
};