#include<stdio.h>
void posion();
void zha();
int main()
{
	int p;
	do
	{
		printf("������Ҫ��ѯ������:\n");
		printf("��������1,դ������2\n");
		scanf_s("%d", &p);
		switch (p)
		{
		case 1:posion();
			break;
		case 2:zha();
			break;
		}
		getchar();
		printf("\n�����������밴�س�");
	} while (getchar() == '\n');
	return 0;
}