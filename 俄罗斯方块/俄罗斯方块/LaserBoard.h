#pragma once
#include "board.h"

class LaserBoard :
	public board
{
private:
	short laserHigh;//����߶�
	void printOld();//��ֹˢ������
public:
	bool end();//���˼���
	void down();//����ͬʱ����
	void betterPrint();//��ֹˢ������
	void printNewOnly();//��ֹˢ������
	void printShadow();//Ӱ�ӱ������ڵ�
	void laserPrint(bool force = 0);//��ӡ���⣬�Ƿ�ǿ�ƴ�ӡ
	LaserBoard();
};