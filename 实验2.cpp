#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <String.h>
#include <stdlib.h>
#include <math.h>
#define MAX_LEN 10// 字符串长度
#define MAX_SIZE 30// 栈或队最大元素个数
//构造队函数
struct QUEUE
{
	int nMaxSize;
	int nCount;
	int nFront; // 队头
	int nRear; // 队尾
	char szQueue[MAX_SIZE][MAX_LEN];
};
//构造栈函数
struct STACK
{
	int nMaxSize;
	int nTop; // 栈顶
	char szStack[MAX_SIZE][MAX_LEN];
};
// 初始化队列函数
void InitQueue(QUEUE* q, int nMaxSize);
void InQueue(QUEUE* q, char* data);
void OutQueue(QUEUE* q, char* data);
void InitStack(STACK* s, int nMaxSize);
void PushStack(STACK* s, char* data);
void PopStack(STACK* s, char* data);
void GetTopStack(STACK* s, char* data);
int isdigit(char x);
int Priority(char* op);
void Compute(char* num1, char* num2, char* op, char* chResult);

int main()
{
	char x[MAX_LEN]; // 表达式
	char op[MAX_LEN]; // 取得栈顶
	char num1[MAX_LEN], num2[MAX_LEN]; // 两个操作数
	char chResult[MAX_LEN]; // 运算结果
	struct QUEUE q1;// 声明队列
	struct QUEUE* q;
	struct STACK OS;//声明 OS 栈和 NS 栈并进行初始化
	struct STACK NS;
	struct STACK* o;
	struct STACK* n;
	q = &q1;
	o = &OS;
	n = &NS;
	InitStack(o, 20);
	InitStack(n, 20);
	InitQueue(q, 20);
	int i = 0;
	int j = 0;
	int k = 0;
	printf("请输入以‘；’为结尾的表达式\n");
	do//输入表达式
	{
		scanf("%s", x);
		if (x[0] != ';')printf("next\n");
		InQueue(q, x);
	} while (x[0] != ';');
	printf("表达式为 \n");
	while (true)
	{
		if (q->nCount != 0)
		{
			OutQueue(q, x);
			printf("%s", x);
		} if
			(isdigit(x[0])) // 输入为数字
			PushStack(n, x);
		else // 输入运算符
		{
			GetTopStack(o, op); // 获得 OS 栈顶运算符
			if (x[0] == ';' && op[0] == ';') // 输入’;’结束表达式
			{
				printf("\n 结果是 ");
				break;
			} if(Priority(x) > Priority(op)) //运算符的优先级〉 栈顶运算符
			{
				PushStack(o, x); continue;
			}
			while ((Priority(x) <= Priority(op)) && Priority(op)) //运算符优先级<=栈顶运算符
			{
				PopStack(n, num1);
				PopStack(n, num2);
				PopStack(o, op);
				Compute(num2, num1, op, chResult);
				PushStack(n, chResult);
				GetTopStack(o, op);
			} PushStack(o, x);
		}
	} PopStack(n, chResult);
	printf("%s\n", chResult);
	return 0;
}
void InitQueue(QUEUE* q, int nMaxSize)
{
	q->nMaxSize = nMaxSize;
	q->nCount = 0;
	q->nFront = 0;
	q->nRear = 0;
}
//将字符串压入队中
void InQueue(QUEUE* q, char* data)
{
	if (q->nCount == q->nMaxSize)
	{
		printf("The Queue is full!\n"); return;
	}
	strcpy(q->szQueue[q->nRear], data);
	if (q->nRear++ == MAX_SIZE)
		q->nRear = 0;
	q->nCount++;
}
//将字符串压出
void OutQueue(QUEUE* q, char* data)
{
	if (q->nCount == 0)
	{
		printf("The Queue is empty!\n"); return;
	}
	strcpy(data, q->szQueue[q->nFront]);
	if (q->nFront++ == MAX_SIZE)
		q->nFront = 0;
	q->nCount--;
}
//初始化栈
void InitStack(STACK* s, int nMaxSize)
{
	s->nMaxSize = nMaxSize;
	s->nTop = 0;
}
//将字符串压入栈中
void PushStack(STACK* s, char* data)
{
	char* p;
	if (s->nTop < s->nMaxSize)
	{
		p = s->szStack[s->nTop];
		strcpy(p, data);
		s->nTop++;
	}
	else
	{
		printf("The stack overflow!\n");
		return;
	}
}
//将字符串压出
void PopStack(STACK* s, char* data)
{
	char* p;
	if (s->nTop == 0)
	{
		printf("stack is empty!\n");
		return;
	}
	else
	{
		p = s->szStack[--s->nTop];
		strcpy(data, p);
	}
}
//获得栈顶指示符
void GetTopStack(STACK* s, char* data)
{
	char* p;
	char a[10] = { 0 };
	if (s->nTop == 0)
	{
		a[0] = ';';
		strcpy(data, a);
	}
	else
	{
		p = s->szStack[s->nTop - 1];
		strcpy(data, p);
	}
} int isdigit(char x)//判断字符
{
	if (x >= '0' && x <= '9')
		return 1;
	return 0;
} int Priority(char* op) //获得操作符的优先级
{
	int nPriority = 0;
	switch (op[0])
	{
	case '^':
		nPriority = 3;
		break;
	case '*':
	case '/':
		nPriority = 2;
		break;
	case '+':
	case '-':
		nPriority = 1;
		break;
	case ';':
		nPriority = 0;
	} return nPriority;
}
void Compute(char* num1, char* num2, char* op, char* chResult)//计算表达式的值
{
	double fNum1, fNum2;
	double fResult = 0;
	fNum1 = atof(num1);
	fNum2 = atof(num2);
	switch (op[0])
	{
	case '^':
		fResult = pow(fNum1, fNum2);
		break;
	case '*':
		fResult = fNum1 * fNum2;
		break;
	case '/':
		fResult = fNum1 / fNum2;
		break;
	case '+':
		fResult = fNum1 + fNum2;
		break;
	case '-':
		fResult = fNum1 - fNum2;
		break;
	} sprintf(chResult, "%.4f", fResult);
	return;
}