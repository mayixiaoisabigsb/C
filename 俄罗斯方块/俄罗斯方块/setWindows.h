#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;

void setWindows()
{
	cout << "���ڲ����У����Ժ�......";
	SetConsoleTitle(TEXT("����˹�������"));
	//���´��뽫���ڹ̶��ο����� https://bbs.csdn.net/topics/392187129?page=1
	HWND hWnd = GetConsoleWindow(); //���cmd���ھ��
	RECT rc;
	GetWindowRect(hWnd, &rc); //���cmd���ڶ�Ӧ����
	//�ı�cmd���ڷ��
	SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	//��Ϊ����漰���߿�ı䣬�������SetWindowPos��������Ч��
	rc.left = 400;
	rc.top = 200;
	SetWindowPos(hWnd, NULL, rc.left, rc.top, 654, 438, NULL);
	system("MODE con cols=80 lines=25");
	//���´���ο����罫������� https://blog.csdn.net/nocomment_84/article/details/53992730
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
	system("cls");
}