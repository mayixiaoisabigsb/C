#include<stdio.h>
int main()
{
	char a[16], b[16], c[16];
	printf("以下内容均不输入扩展名\n");
	printf("请输入图片文件名:");
	gets(a);
	printf("请输入压缩文件名:");
	gets(b);
	printf("请输入新生成的文件名:");
	gets(c);
	FILE *pf;
	pf = fopen("运行.bat", "wb");
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