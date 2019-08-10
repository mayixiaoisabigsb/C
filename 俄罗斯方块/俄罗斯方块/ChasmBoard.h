#pragma once
#include "GravityBoard.h"

class ChasmBoard :
	public GravityBoard
{
private:
	bool fall();//���䣬�յ����鲻��������Ӱ��
	unsigned short deleteLine();//���������յ�����
	unsigned short borderLine(unsigned short row, unsigned short column);//����ĳλ���Ϸ��߽緽�������
public:
	void move(char direction, bool artificial = 1);//�ӷֹ���ı�
	void print();//������ʾ��Ԩ
	void printShadow();//����ʾ��Ԩ�е�Ӱ��
	void fix();//��Ԩ���鲻����˸��ʾ
	bool end();//������Ԩ
	ChasmBoard();
};