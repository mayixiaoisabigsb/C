#include<stdio.h>
#include<string.h>
int furtune(int a)
{
	if (a > 0)
		return -1;
	else
		return a;
}
int main()
{
	int b, c, e, s = 1;
	char f[100], j[3] = "贾", a[3] = "超", r[3] = "然";
	printf("请输入你想玩弄的人的名字:");
	gets_s(f, 100);
	if (strstr(f,j)&&strstr(f,a)&&strstr(f,r))
	{
		printf("你敢玩弄你爸爸?\n");
		printf("请按任意键终止你这个臭儿子的生命");
	}
	else
	{
		printf("你对%s的喜欢程度（可负）:", f);
		scanf_s("%d", &c);
		if (c > 0)
			printf("看来你也是个大傻逼！\n");
		else
			printf("你很聪明！\n");
		b = furtune(c);
		printf("你想欺负%s的程度（可负）:", f);
		scanf_s("%d", &e);
		if (e >= 0)
			if (e > b)
				printf("%s是个大傻逼！\n", f);
			else
				printf("你根本不认识%s！但是TA确实是个大傻逼！\n", f);
		else
			printf("你跟%s都是个大傻逼！\n", f);
		printf("%s还能不是个大傻逼?\n请按任意键或关闭窗口终止%s的生命\n", f, f);
	}
	getch();
	return 0;
}
/* PS:马一骁还能不是个大傻逼？ */