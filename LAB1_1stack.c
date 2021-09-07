#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#pragma warning(disable: 4996)

typedef struct {
	char movieName[30];
	char movieChar[30];
	char movieYear[10];
}movie;
typedef struct {
	movie data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}


void push(StackType* s, movie item) {
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

movie pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

movie peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}

int main(void) {
	StackType s;
	init_stack(&s);
	int movieNum;
	int movieWatched;
	printf("---���� ���� ��ȭ ������� �ۼ�---\n");
	printf("���� ���� ��ȭ ���� �Է��Ͻÿ�: ");
	scanf("%d", &movieNum);
	printf("\n");


	for (int i = 0; i < movieNum; i++) {
		movie m;
		printf("��ȭ����: ");
		scanf_s("%s", &m.movieName, sizeof(m.movieName));
		printf("�ֿ�: ");
		scanf_s("%s", &m.movieChar, sizeof(m.movieChar));
		printf("�����⵵: ");
		scanf_s("%s", &m.movieYear, sizeof(m.movieYear));
		push(&s, m);
		printf("\n");
	}

	printf("-- ���� ���� ��ȭ ���--\n\n");
	printf(" ��ȭ�� �� [ ");
	printf("%d", movieNum);
	printf("]-\n\n");

	for (int i = 0; i < movieNum; i++) {
		printf("       ");
		printf("%-20s", s.data[i].movieName);
		printf("       ");
		printf("%-20s", s.data[i].movieChar);
		printf("       ");
		printf("%-15s", s.data[i].movieYear);
		printf("\n");
	}
	printf("\n\n");
	printf("�� ��ȭ ��: ");
	scanf_s("%d", &movieWatched);
	printf("\n\n\n\n");
	printf("���� �� �� ��ȭ ���--\n");
	printf(" ��ȭ�� �� [ ");
	printf("%d", movieNum - movieWatched);
	printf("]-\n\n");



	for (int i = 0; i < movieWatched; i++) {
		pop(&s);
	}


	for (int i = 0; i < movieNum - movieWatched; i++) {
		printf("       ");
		printf("%-20s", s.data[i].movieName);
		printf("       ");
		printf("%-20s", s.data[i].movieChar);
		printf("       ");
		printf("%-15s", s.data[i].movieYear);
		printf("\n");
	}






}