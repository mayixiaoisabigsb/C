#pragma once
#include "board.h"

extern unsigned &member(unsigned group[][2], unsigned sign);

class GravityBoard :
	public board
{
protected:
	unsigned supply();//�������ǣ���Ϊ��ͬ����
	unsigned short blockHigh(unsigned short row, unsigned short column);//����ĳ��ĳ�о�ظ߶�
	virtual unsigned short deleteLine();//��Ҫ���⿼��J��Lճ�����
	virtual bool fall();//����Ч�������������Ƿ��з���仯
public:
	virtual void move(char direction, bool artificial = 1);//�ƶ�ͬʱ�̳б��
	virtual bool end();//��ؽ���󴥷�����
	bool spawn();//����ǵ�����
	GravityBoard(const string name = "����");
};