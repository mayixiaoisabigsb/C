#include<stdio.h>
int main()
{
	char a[16], b[16], c[16];
	printf("�������ݾ���������չ��\n");
	printf("������ͼƬ�ļ���:");
	gets(a);
	printf("������ѹ���ļ���:");
	gets(b);
	printf("�����������ɵ��ļ���:");
	gets(c);
	FILE *pf;
	pf = fopen("����.bat", "wb");
	fputs("COPY ", pf);
	fputs(a, pf);
	fputs(".jpg /B + ", pf);
	fputs(b, pf);
	fputs(".rar = ", pf);
	fputs(c, pf);
	fputs(".jpg", pf);
	fclose(pf);
	return 0;
}