#pragma once
#include "board.h"

class DevideBoard :
	public board
{
private:
	bool order;//�ִ���ż��
	bool mayMove(char direction);//���ܹ���
	bool cross();//�����ж�
public:
	bool spawn();//��ż���
	DevideBoard();
};