#pragma once
#include<iostream>
#include<Windows.h>
using namespace std;

void setWindows()
{
	cout << "窗口布局中，请稍后......";
	SetConsoleTitle(TEXT("俄罗斯方块革命"));
	//以下代码将窗口固定参考网络 https://bbs.csdn.net/topics/392187129?page=1
	HWND hWnd = GetConsoleWindow(); //获得cmd窗口句柄
	RECT rc;
	GetWindowRect(hWnd, &rc); //获得cmd窗口对应矩形
	//改变cmd窗口风格
	SetWindowLongPtr(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
	//因为风格涉及到边框改变，必须调用SetWindowPos，否则无效果
	rc.left = 400;
	rc.top = 200;
	SetWindowPos(hWnd, NULL, rc.left, rc.top, 654, 438, NULL);
	system("MODE con cols=80 lines=25");
	//以下代码参考网络将光标隐藏 https://blog.csdn.net/nocomment_84/article/details/53992730
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
	system("cls");
}