#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <String.h>
#include <stdlib.h>
#include <math.h>
#define MAX_LEN 10// �ַ�������
#define MAX_SIZE 30// ջ������Ԫ�ظ���
//����Ӻ���
struct QUEUE
{
	int nMaxSize;
	int nCount;
	int nFront; // ��ͷ
	int nRear; // ��β
	char szQueue[MAX_SIZE][MAX_LEN];
};
//����ջ����
struct STACK
{
	int nMaxSize;
	int nTop; // ջ��
	char szStack[MAX_SIZE][MAX_LEN];
};
// ��ʼ�����к���
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
	char x[MAX_LEN]; // ���ʽ
	char op[MAX_LEN]; // ȡ��ջ��
	char num1[MAX_LEN], num2[MAX_LEN]; // ����������
	char chResult[MAX_LEN]; // ������
	struct QUEUE q1;// ��������
	struct QUEUE* q;
	struct STACK OS;//���� OS ջ�� NS ջ�����г�ʼ��
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
	printf("�������ԡ�����Ϊ��β�ı��ʽ\n");
	do//������ʽ
	{
		scanf("%s", x);
		if (x[0] != ';')printf("next\n");
		InQueue(q, x);
	} while (x[0] != ';');
	printf("���ʽΪ \n");
	while (true)
	{
		if (q->nCount != 0)
		{
			OutQueue(q, x);
			printf("%s", x);
		} if
			(isdigit(x[0])) // ����Ϊ����
			PushStack(n, x);
		else // ���������
		{
			GetTopStack(o, op); // ��� OS ջ�������
			if (x[0] == ';' && op[0] == ';') // ���롯;���������ʽ
			{
				printf("\n ����� ");
				break;
			} if(Priority(x) > Priority(op)) //����������ȼ��� ջ�������
			{
				PushStack(o, x); continue;
			}
			while ((Priority(x) <= Priority(op)) && Priority(op)) //��������ȼ�<=ջ�������
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
//���ַ���ѹ�����
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
//���ַ���ѹ��
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
//��ʼ��ջ
void InitStack(STACK* s, int nMaxSize)
{
	s->nMaxSize = nMaxSize;
	s->nTop = 0;
}
//���ַ���ѹ��ջ��
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
//���ַ���ѹ��
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
//���ջ��ָʾ��
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
} int isdigit(char x)//�ж��ַ�
{
	if (x >= '0' && x <= '9')
		return 1;
	return 0;
} int Priority(char* op) //��ò����������ȼ�
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
void Compute(char* num1, char* num2, char* op, char* chResult)//������ʽ��ֵ
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