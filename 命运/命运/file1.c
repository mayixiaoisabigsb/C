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
	char f[100], j[3] = "��", a[3] = "��", r[3] = "Ȼ";
	printf("������������Ū���˵�����:");
	gets_s(f, 100);
	if (strstr(f,j)&&strstr(f,a)&&strstr(f,r))
	{
		printf("�����Ū��ְ�?\n");
		printf("�밴�������ֹ����������ӵ�����");
	}
	else
	{
		printf("���%s��ϲ���̶ȣ��ɸ���:", f);
		scanf_s("%d", &c);
		if (c > 0)
			printf("������Ҳ�Ǹ���ɵ�ƣ�\n");
		else
			printf("��ܴ�����\n");
		b = furtune(c);
		printf("�����۸�%s�ĳ̶ȣ��ɸ���:", f);
		scanf_s("%d", &e);
		if (e >= 0)
			if (e > b)
				printf("%s�Ǹ���ɵ�ƣ�\n", f);
			else
				printf("���������ʶ%s������TAȷʵ�Ǹ���ɵ�ƣ�\n", f);
		else
			printf("���%s���Ǹ���ɵ�ƣ�\n", f);
		printf("%s���ܲ��Ǹ���ɵ��?\n�밴�������رմ�����ֹ%s������\n", f, f);
	}
	getch();
	return 0;
}
/* PS:��һ�绹�ܲ��Ǹ���ɵ�ƣ� */