#pragma once
#include"block.h"

enum { ROW, COLUMN };

class tile
{
protected:
	short shape[4][2];//�����ں����ĸ�С��������λ��[���][��0��1]
	unsigned short condition;//�󷽿�״̬��0Ϊ��ĸ��״����˳ʱ��˳���������״
	short position[2];//���Ϊ��(����λ�ã���תʱ���������)�ķ�������Ϸ���ϵ�λ��{����,����}
	tiletype type;//�󷽿�����(����)
	short bottom[4][2];//�׶˵����λ��(����ĸ��Ͷ�)
	const unsigned short conditonnum;//״̬��(��ͬ�󷽿�״̬�Ǿ��Ե�)
	unsigned short bottomnum;//�׶˷�����
public:
	const unsigned short getConditionnum();//����״̬��
	unsigned short getBottomnum();//���ص׶˷�����
	short getBR(unsigned short number);//����ָ����ŵĵ׶˷���ľ�������
	short getBC(unsigned short number);//����ָ����ŵĵ׶˷���ľ�������
	short getSR(unsigned short number);//����ָ����ŵķ�����������
	short getSC(unsigned short number);//����ָ����ŵķ�����������
	short getR(unsigned short number);//����ָ����ŵķ���ľ�������
	short getC(unsigned short number);//����ָ����ŵķ���ľ�������
	void move(char direction);//����ָ�������ƶ�
	tiletype getType();//���ط�������
	virtual void turnAround() = 0;//��ת
	tile(const unsigned short conditionnum, tiletype type);//״̬�����������ͣ����ڼ̳�
};

class tile_I:public tile
{
public:
	tile_I();
	void turnAround();
};

class tile_J :public tile
{
public:
	tile_J();
	void turnAround();
};

class tile_L :public tile
{
public:
	tile_L();
	void turnAround();
};

class tile_O :public tile
{
public:
	tile_O();
	void turnAround();
};

class tile_S :public tile
{
public:
	tile_S();
	void turnAround();
};

class tile_Z :public tile
{
public:
	tile_Z();
	void turnAround();
};

class tile_T :public tile
{
public:
	tile_T();
	void turnAround();
};