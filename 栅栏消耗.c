#include<stdio.h>
#include<math.h>
void zha()
{
	double w, s, l, n;
	int a, b, p;
	printf("������Ҫ����������:\n");
	printf("����1������2:\n");
	scanf_s("%d", &p);
	if (p == 1)
	{
		printf("��������Ҫդ������:");
		scanf_s("%lf", &n);
	}
	else
	{
		printf("������Χ�����߸���:");
		scanf_s("%d%d", &a, &b);
		n = 2 * (a + b) - 4;
	}
	n = ceil(n / 3) * 3;
	s = n / 3 * 2;
	w = n / 3 * 4 + ceil(s / 4) * 2;
	l = ceil(w / 4);
	printf("��Ҫ%.0fԭľ�ֽ�ľ�壬��Ҫ%.0fľ�壬%.0fľ����ľ������Ҫ%.0fľ��", l, w, ceil(s / 4.0) * 2, s);
}