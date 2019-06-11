#include<stdio.h>
void posion();
void zha();
int main()
{
	int p;
	do
	{
		printf("请输入要查询的问题:\n");
		printf("主地坐标1,栅栏消耗2\n");
		scanf_s("%d", &p);
		switch (p)
		{
		case 1:posion();
			break;
		case 2:zha();
			break;
		}
		getchar();
		printf("\n有其他问题请按回车");
	} while (getchar() == '\n');
	return 0;
}