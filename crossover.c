#include"head.h"
typedef struct Node
{
	int NO;
	struct Node *next; 
}Node;
int update_ver(int ver[][N + 1], int k);
void crossover(int *parent1, int *parent2, int *son, int k);//交叉算符
void creatlinklist(int *ver, Node **p, int *knum);//根据一组顶点的颜色创建链表，每种颜色为一个链表
int findmax(int *p, int k);//在数组p[1]到p[k]中找到最大的数的下标
void newlinklist(Node **p1, Node **p2, int *knum1, int *knum2, int *parent, int col);
void insertsonlist(Node **p1, int i, Node **pson, int k);
void listtoarray(Node **pson, int *son, int k);
void showlist(Node **p, int k);

int update_ver(int ver[][N + 1], int k)
{
	int c1, c2, i, j, l, t;
	int Newver[N + 1];
	c1 = random(P);
	c2 = random(P);
	while (c2 == c1)
		c2 = random(P);//随机找两组顶点
	crossover(ver[c1], ver[c2], Newver, k);//两组顶点进行交叉算符
	t = random(P);
	for (i = 1; i <= N; i++)
		ver[t][i] = Newver[i];
	//printf("(%d, %d)-->%d\t", c1, c2, t);
	return t;
}

void crossover(int *parent1, int *parent2, int *son, int k)
{
	int i;
	Node *p1[MAX_K + 1], *p2[MAX_K + 1], *pson[MAX_K + 1];//三组头指针
	int knum1[MAX_K + 1], knum2[MAX_K + 1];
	for (i = 1; i <= k; i++)
	{
		p1[i] = (Node*)malloc(sizeof(Node));
		p2[i] = (Node*)malloc(sizeof(Node));
		pson[i] = (Node*)malloc(sizeof(Node));
		p1[i]->next = NULL;
		p2[i]->next = NULL;
		knum1[i] = 0;
		knum2[i] = 0;
	}
	creatlinklist(parent1, p1, knum1);
	creatlinklist(parent2, p2, knum2);
	//showlist(p1, k);
	//showlist(p2, k);
	int col, j = 1;
	while (1)
	{
		col = findmax(knum1, k);
		pson[j]->next = p1[col]->next;
		newlinklist(p1, p2, knum1, knum2, parent2, col);
		if (j++ == k)
			break;
		col = findmax(knum2, k);
		pson[j]->next = p2[col]->next;
		newlinklist(p2, p1, knum2, knum1, parent1, col);
		if (j++ == k)
			break;
	}
	for (i = 1; i <= k; i++)
	{
		if (knum1[i] != 0)
			insertsonlist(p1, i, pson, k);
		if (knum2[i] != 0)
			insertsonlist(p2, i, pson, k);
	}
	//showlist(pson, k);
	listtoarray(pson, son, k);
}

void creatlinklist(int *ver, Node **p, int *knum)
{
	int i, c;
	Node *tp;
	for (i = 1; i <= N; i++)
	{
		c = ver[i];
		knum[c]++;
		tp = p[c];
		while (tp->next != NULL)
			tp = tp->next;
		tp->next = (Node*)malloc(sizeof(Node));
		tp->next->NO = i;
		tp->next->next = NULL;
	}
}

int findmax(int *p, int k)
{
	int max, maxcol, cmax, i;
	max = 0, cmax = 1;
	for (i = 1; i <= k; i++)
	{
		if (p[i] > max)
		{
			max = p[i];
			cmax = 2;
			maxcol = i;
		}
		else if (p[i] == max)
		{
			cmax++;
			if(!random(cmax))
				maxcol = i;
		}
	}
	return maxcol;
}

void newlinklist(Node **p1, Node **p2, int *knum1, int *knum2, int *parent, int col)//在parent2中删除parent1中第col个颜色的所有点
{
	int n, c;
	Node *tp1, *tp2;
	knum1[col] = 0;//parent1中颜色col的点数变为0
	tp1 = p1[col]->next;
	while (tp1 != NULL)
	{
		n = tp1->NO;
		c = parent[n];
		knum2[c]--;
		tp2 = p2[c];
		while (1)
		{
			if (tp2->next->NO == n)
			{
				tp2->next = tp2->next->next;
				break;
			}
			else
				tp2 = tp2->next;
		}
		tp1 = tp1->next;
	}
	p1[col]->next = NULL;
}

void insertsonlist(Node **p1, int i, Node **pson, int k)//将parent中剩余的点随机加到son中任意一个独立集中
{
	Node *tp1, *tp2;
	tp1 = p1[i]->next;
	int j = random(k) + 1;
	tp2 = pson[j];
	while (tp2->next != NULL)
		tp2 = tp2->next;
	tp2->next = tp1;
}

void listtoarray(Node **pson, int *son, int k)
{
	int i, n;
	Node *tp;
	for (i = 1; i <= k; i++)
	{
		tp = pson[i]->next;
		while (tp != NULL)
		{
			n = tp->NO;
			son[n] = i;
			tp = tp->next;
		}
	}
}

void showlist(Node **p, int k)
{
	int i;
	Node *tp;
	for (i = 1; i <= k; i++)
	{
		printf("%d----", i);
		tp = p[i]->next;
		while (tp != NULL)
		{
			printf("%d ", tp->NO);
			tp = tp->next;
		}
		printf("\n");
	}
}