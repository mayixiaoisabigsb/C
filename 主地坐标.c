#include<stdio.h>
void posion()
{
	float x1, x2, y1, y2, z1, z2, x, y, z;
	printf("请输入起始主世界坐标:");
	scanf_s("%f%f%f", &x1, &y1, &z1);
	printf("请输入目标主世界坐标:");
	scanf_s("%f%f%f", &x2, &y2, &z2);
	printf("请输入起始下界坐标:");
	scanf_s("%f%f%f", &x, &y, &z);
	printf("目标下界坐标为:");
	printf("%f %f %f", x + (x2 - x1) / 8, y + y2 - y1, z + (z2 - z1) / 8);
}