#include<stdio.h>
#include<math.h>
void zha()
{
	double w, s, l, n;
	int a, b, p;
	printf("请输入要描述的类型:\n");
	printf("个数1，长宽2:\n");
	scanf_s("%d", &p);
	if (p == 1)
	{
		printf("请输入需要栅栏个数:");
		scanf_s("%lf", &n);
	}
	else
	{
		printf("请输入围的两边格数:");
		scanf_s("%d%d", &a, &b);
		n = 2 * (a + b) - 4;
	}
	n = ceil(n / 3) * 3;
	s = n / 3 * 2;
	w = n / 3 * 4 + ceil(s / 4) * 2;
	l = ceil(w / 4);
	printf("需要%.0f原木分解木板，需要%.0f木板，%.0f木板做木棍，需要%.0f木棍", l, w, ceil(s / 4.0) * 2, s);
}