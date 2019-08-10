#pragma once
#include<string>
#include<Windows.h>
#include"block.h"
#include"tile.h"
using namespace std;

extern unsigned short shadow[4][2];
extern unsigned short difficulty;
extern bool shadowShow;
extern bool bigBlock;

class board
{
protected:
	string name;
	tile *obj;//ָ����Ϸ����Ψһ��Ծ�Ĵ󷽿�
	block *game[24][12];//��Ϸ���
	block *next[2][8][7];//�������������Ϣ������չʾ
	tile *nextobj[2];//�������󷽿�
	unsigned score;//����
	unsigned linenum;//����������
	unsigned short weight();//Ȩ�أ������Ѷ��е÷ּӳ�
	unsigned short top();//������Ϸ�巽��ѻ��Ķ�������
	unsigned short top(unsigned short column);//����ĳһ�еĶ�������
	virtual unsigned short deleteLine();//��������
	unsigned short high();//����Ŀǰ����������ظ߶�
	tile *spawnNew();//����������´󷽿�
	virtual bool mayMove(char direction);//�ж��Ƿ������ָ�������ƶ�
	virtual void printOld();//��ӡ��壬һ�������б仯��ģʽ
public:
	bool start();//��ʼ�µĴ󷽿飬�������ʧ�ܷ���false
	virtual bool end();//�󷽿���ؽ��㣬����Ϸ���ܼ�������false
	virtual void move(char direction, bool artificial = 1);//���ݷ����ƶ���任
	virtual void addScore(unsigned short number);//�������������ӷ�
	unsigned getScore();//���ط���
	unsigned getLinenum();//����������
	virtual void print();//��ӡ���
	virtual void betterPrint();//���õش�ӡ(�ܴ�̶��ϻ��������)
	virtual void printNewOnly();//ֻ��ӡ�·��鲢�һ����Χˢ�£���Ч���������
	virtual void printShadow();//����Ӱ��
	void printScore();//ֻ��ӡ����
	virtual bool spawn();//�����·��飬���ѱ�ռ��������ʧ�ܷ���false
	virtual void fix();//�̶���Ծ���飬������󷽿�ָ��������
	virtual void down();//��Ȼ����(��ʵ���������ƶ�һ��)
	void setblock(unsigned short row, unsigned short column, tiletype target = BORDER);
	bool inDanger();//����Ծ�󷽿�����򷵻�true
	bool gameover();//������ʧ����������true
	board(const string name = "����");
	virtual ~board();
};