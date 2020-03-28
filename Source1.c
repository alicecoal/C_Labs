#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 128
char* Strcpy(char* str, const char* a) {
	while (*str++ = *a++) {}
	return str;
}

int Strcmp(char* str, char* a) {
	while (*str && *a) {
		if (*str == *a) {
			str++;
			a++;
			continue;
		}
		if (*str < *a) return -1;
		else return 1;
	}
	if (!(*str) && !(*a)) return 0;
	if (*a) return -1;
	else return 1;
}


int main(void)
{
	int i, n, j, kol[40] = { 0 }, k, cur; n = 0;
	char* p; char a[40][MAX], b[40][MAX]; char str[MAX], temp[MAX];
	FILE* fp;
	fp = fopen("Text.txt", "r");
	if (!fp) exit(1);
	while (fgets(str, MAX, fp) != NULL) {
		i = 0; k = 0;
		while (str[i] != '\0')
		{
			if (str[i] == ' ' || str[i] == '\n')
			{
				temp[k] = '\0';
				cur = 0;
				while (temp[cur] != '\0')
				{
					a[n][cur] = temp[cur];
					cur++;
				}
				a[n][cur] = '\0';
				n++;
				k = 0;
				i++;
				continue;
			}
			temp[k++] = str[i];
			i++;
		}
	}
	for (i = 0; i < n - 1; i++)
	{
		if (kol[i] == 0) {
			for (j = i + 1; j < n; j++)
			{
				if (Strcmp(a[i], a[j]) == 0) {
					kol[i] = 1;
					kol[j] = 1;
				}
			}
		}
	}
	for (i = 0; i < n; i++) {
		if (kol[i] == 0) {
			cur = 0;
			while (a[i][cur] != '\0')
			{
				b[k][cur] = a[i][cur];
				cur++;
			}
			b[k][cur] = '\0';
			k++;
		}
	}
	for (i = 0; i < k - 1; i++)
	{
		for (j = i + 1; j < k; j++)
		{
			if (Strcmp(b[i], b[j]) > 0)
			{
				Strcpy(temp, b[i]);
				Strcpy(b[i], b[j]);
				Strcpy(b[j], temp);
			}
		}
	}
	for (i = 0; i < k; i++)
	{
		printf("%s ", b[i]);
	}
	return 0;
}
