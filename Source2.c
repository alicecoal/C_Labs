#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int  Strlen(const char* str) {
	int len = 0;
	while (*str)
	{
		str++;
		len++;
	}
	return len;
}


char* Strcpy(char* str, const char* a) {
	while (*str++ = *a++) {}
	return str;
}


char* Strcat(char* str, const char* a) {
	str += Strlen(str);
	while (*str++ = *a++) {}
	return str;
}

int main(void)
{
	int n, i, k, j; char ch[9]; char temp[9]; char a[1000][9]; int ind[1000], index, kol, num[1000];
	printf("Enter N and then N words, each on the next line: "); scanf("%d", &n);
	gets(ch);
	for (i = 0; i < n; i++)
	{
		k = 0; 
		gets(temp);
		j = 0;
		while (temp[j] != '\0')
		{
			a[i][j] = temp[j];
			j++;
		}
		a[i][j] = '\0';
	}
	for (i = 0; i < n; i++) {
		ind[i] = i+1;
	}
	char c[9000];
	Strcpy(c, a[0]);
	Strcat(c, " ");
	index = 1;
	kol = 0;
	num[kol] = ind[0];
	for (i = 0; i < n - 1; i++)
	{
		Strcpy(a[i], a[i + 1]);
		ind[i] = ind[i + 1];
	}
	n--;

	while (n!=0 && Strlen(c)!=0) {
		int f = 0;
		for (i = 0; i < n; i++) 
		{
			
			if (a[i][0] == c[Strlen(c) - 2] && ind[i]>index)
			{
				Strcat(c, a[i]);
				Strcat(c, " ");
				index = 1;
				kol++;
				num[kol] = ind[i];
				for (j = i; j < n - 1; j++)
				{
					Strcpy(a[j], a[j + 1]);
					ind[j] = ind[j + 1];
				}
				n--; 
				f = 1;
			}
		}
		if (f == 0)
		{
			char temp[9],temp1[9]; int cur = 0;
			int pos = Strlen(c) - 2;
			while (c[pos]!=' ' && pos>0) {
				temp1[cur] = c[pos];
				pos--;
				cur++;
			}
			for (j = 0; j < cur; j++)
				temp[j] = temp1[cur - j - 1];
			c[pos+1] = '\0';
			temp[cur] = '\0';
			for (j = 0; j <= cur; j++)
			{
				a[n][j] = temp[j];
			}
			ind[n] = num[kol]; index = num[kol];
			kol--;
			n++;
		}
	}
	if (n == 0 && c[0]==c[Strlen(c)-2]) printf("The chain is: %s\n", c);
	else printf("ERROR");
	return 0;
}