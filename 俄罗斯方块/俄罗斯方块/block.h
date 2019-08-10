#pragma once

enum tiletype { BORDER, I, J, L, O, S, Z, T };//��������
enum style { COLORFUL, COLORLESS, CLASSIC };
extern style blockstyle;

class block
{
private:
	tiletype type;//�����󷽿������
	bool active;//�Ƿ�Ϊ��Ծ����
public:
	unsigned sign;//�����ź�ϵͳ������չ����¼����Ĳ���
	unsigned sign2;//�ڶ����ź�
	void fix();//�̶�����
	void realease();//�ɶ�����
	void show();//չʾ����
	bool getActive();//���ػ�Ծ���
	tiletype getType();//���ط�����������
	block(tiletype type, bool active = 1, unsigned sign = 0, unsigned sign2 = 0);//���ͣ���Ծ���(Ĭ�ϻ�Ծ�����������·���)
};