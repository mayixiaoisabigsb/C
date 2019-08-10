#pragma once
#include"board.h"
using namespace std;

enum { SCORE, LINE, DIFFICULTY };
enum mode { NONE, NORMAL, MOVE, GRAVITY, LASER, DELAY, GUSH, CHASM, FROZEN, DARKNESS, DEVIDE };

class gameboard
{
private:
	unsigned scores[11][3][11];//�������а�(ǰ10��)
	board *mainboard;//һ����Ϸ���
	long speed;//�����ٶ�
	bool music;//�Ƿ�������
	bool sound;//�Ƿ�����Ч
	mode current;//��ǰģʽ
	void rScores();//���÷������а�
	void gameStart();//��ʼ����Ϸ
	bool playing();//�󷽿�����У�������̶���������false
	bool gameover();//��Ϸ�������û��Ƿ����¿�ʼ��Ϸ
	void showScores(mode gamemode);//չʾ���а�
	void save();//�������а����ļ�(D���µ�TetrisScores.bat)
	char beginning();//��ʼ���棬����ѡ��
	mode selectMode(bool gameing = 0);//ѡ��ģʽ���棬����ģʽ
	bool selectGame();//ѡ����Ϸ���棬�����Ƿ�ʼ��Ϸ
	void settings(bool gameing = 0);//����
	void help(mode gamemode);//����
	void updateShow(bool gameing = 0);//������־
public:
	void menu();//��ʼ������Ϸ����
	gameboard();//���ȡ�ļ��е����а��޸��Լ������а����û�о�ȫ����
};