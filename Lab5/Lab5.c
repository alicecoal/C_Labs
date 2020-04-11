#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h> 

typedef struct item
{
	int digit;
	struct item* right;
	struct item* left;
} Item;

typedef struct number
{
	Item* LSD; 
	Item* MSD;
	int n;
} Number;

int check(void)
{
	int sum, flag; char a;
	flag = 0;
	while (flag == 0) {
		sum = 0; a = '0';
		while ((a <= '9') && (a >= '0')) {
			scanf("%c", &a);
			if (a == '\n') {
				break;
			}
			sum = sum * 10 + (a - '0');
		}
		if (a != '\n') {
			printf("THE ENTERED VALUE IS INVALID, PLEASE TRY AGAIN\n");
			while (a != '\n') {
				scanf("%c", &a);
			}
		}
		else {
			flag = 1;
			break;
		}
	}
	return sum;
}

void Add(Number* number, int digit)
{
	Item* p= (Item*)malloc(sizeof(Item));
	if (p == NULL) { 
		printf("Insufficient memory available\n"); return; 
	}
	p->digit = digit;
	p->right = NULL; p->left = NULL;
	if (number->LSD == NULL) number->LSD = number->MSD = p;
	else
	{
		number->MSD->right = p;
		p->left = number->MSD;
		number->MSD = p;
	}
	number->n=(number->n)+1;
}

Number Init(char* a)
{
	Number number = { NULL, NULL, 0 };
	int n;
	for (n = strlen(a) - 1; n >= 0; n--)
		Add(&number, a[n] - '0');
	return number;
}



Number Sum(Number n1, Number n2)
{
	Number sum = Init("");
	Item* p1 = n1.LSD, * p2 = n2.LSD;
	int digit, prev_carry = 0, s1, s2;
	while (p1 || p2)
	{
		if (p1)
		{
			s1 = p1->digit;
			p1 = p1->right;
		}
		else s1 = 0;
		if (p2)
		{
			s2 = p2->digit;
			p2 = p2->right;
		}
		else s2 = 0;
		digit = (s1 + s2 + prev_carry) % 10;
		prev_carry = (s1 + s2 + prev_carry) / 10;
		Add(&sum, digit);
	}
	if (prev_carry) Add(&sum, prev_carry);
	return sum;
}

void Print(Number number)
{
	Item* p = number.MSD;
	printf("The Number: ");
	while (p)
	{
		printf("%d", p->digit);
		p = p->left;
	}
	printf("\n");
}

Number Product(Number a, Number b)
{
	Number current = Init("");
	Number ans = Init("0");
	Item* p1 = a.LSD;
	Item* p2 = b.LSD;
	int digit = 0, prev_carry = 0, s1 = 0, s2 = 0, i = 0, k = 0;
	while (p1)
	{
		s1 = p1->digit;
		current = Init("");
		p2 = b.LSD;
		k = 0;
		
		while (p2)
		{
			s2 = p2->digit;
			if (k != i)
			{
				for (k = 0; k < i; k++)
				{
					Add(&current, 0);
				}
			}
			digit = (s1 * s2 + prev_carry) % 10;
			prev_carry = (s1 * s2 + prev_carry) / 10;
			Add(&current, digit);
			p2 = p2->right;
			if ((prev_carry > 0) && (p2 == NULL)) {
				Add(&current, prev_carry); prev_carry = 0;
			}
		}
		ans = Sum(ans, current);
		p1 = p1->right;
		i++;
	}
	return ans;
}



int main(void)
{
	int i, n;
	printf("Enter n: ");
	n = check();
	Number c;
	Number a = Init("1");
	Number b = Init("1");
	for (i = 2; i <= n; i++) {
		int x = i; char s[100],s1[100];
		c = Product(a, b);
		a = c;
		int k; k = 0;
		while (x > 0) {
			s1[k] = (char)((x % 10) + '0');
			x = x / 10;
			k++;
		}
		k--;
		int j;
		for (j = 0; j <= k; j++) s[j] = s1[k - j];
		s[k+1] = '\0';
		b = Init(s);
	}
	c = Product(a, b);
	Print(c);
	getch();
	return 0;
}