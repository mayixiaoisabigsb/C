#pragma once
#include "GravityBoard.h"

class FrozenBoard :
	public GravityBoard
{
private:
	bool fall();//���䣬��ȶ��᷽�鲻��������Ӱ��
	unsigned short step;//����
	void froze();//����
	void printBlock(unsigned short row, unsigned short column);//��ӡĳһ��
	void printBlock(block *target);//��ƫ���ӡ
	void printOld();//�¹���
	unsigned short deleteLine();//��ȶ��᷽��ⶳ
	unsigned short frozenLine(unsigned short row, unsigned short column);//����ĳλ���Ϸ���ȱ�����������
public:
	bool end();
	void print();
	void printNewOnly();
	void printShadow();
	FrozenBoard();
};