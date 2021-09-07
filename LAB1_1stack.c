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
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

movie pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

movie peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}

int main(void) {
	StackType s;
	init_stack(&s);
	int movieNum;
	int movieWatched;
	printf("---보고 싶은 영화 정보목록 작성---\n");
	printf("보고 싶은 영화 수를 입력하시오: ");
	scanf("%d", &movieNum);
	printf("\n");


	for (int i = 0; i < movieNum; i++) {
		movie m;
		printf("영화제목: ");
		scanf_s("%s", &m.movieName, sizeof(m.movieName));
		printf("주연: ");
		scanf_s("%s", &m.movieChar, sizeof(m.movieChar));
		printf("개봉년도: ");
		scanf_s("%s", &m.movieYear, sizeof(m.movieYear));
		push(&s, m);
		printf("\n");
	}

	printf("-- 보고 싶은 영화 목록--\n\n");
	printf(" 영화편 수 [ ");
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
	printf("본 영화 수: ");
	scanf_s("%d", &movieWatched);
	printf("\n\n\n\n");
	printf("아직 못 본 영화 목록--\n");
	printf(" 영화편 수 [ ");
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