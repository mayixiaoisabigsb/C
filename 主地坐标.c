#include<stdio.h>
void posion()
{
	float x1, x2, y1, y2, z1, z2, x, y, z;
	printf("��������ʼ����������:");
	scanf_s("%f%f%f", &x1, &y1, &z1);
	printf("������Ŀ������������:");
	scanf_s("%f%f%f", &x2, &y2, &z2);
	printf("��������ʼ�½�����:");
	scanf_s("%f%f%f", &x, &y, &z);
	printf("Ŀ���½�����Ϊ:");
	printf("%f %f %f", x + (x2 - x1) / 8, y + y2 - y1, z + (z2 - z1) / 8);
}