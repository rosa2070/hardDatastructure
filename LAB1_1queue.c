#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 6
#pragma warning(disable: 4996)


typedef struct {
	char movieName[50];
	char movieChar[50];
	char movieYear[30];
}movie;
typedef struct {
	movie data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void queue_print(QueueType* q)
{
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("       %-20s", q->data[i].movieName);
			printf("       %-20s", q->data[i].movieChar);
			printf("       %-20s", q->data[i].movieYear);
			printf("\n");
			if (i == q->rear)
				break;
		} while (i != q->front);
	}

}


void enqueue(QueueType* q, movie item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

movie dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

movie peek(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front) % MAX_QUEUE_SIZE];
}

int main(void)
{
	QueueType queue;
	init_queue(&queue);
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
		enqueue(&queue, m);
		printf("\n");
	}

	printf("-- ���� ���� ��ȭ ���--\n\n");
	printf(" ��ȭ�� �� [ ");
	printf("%d", movieNum);
	printf("]-\n\n");

	queue_print(&queue);

	printf("\n\n");
	printf("�� ��ȭ ��: ");
	scanf_s("%d", &movieWatched);
	printf("\n\n\n\n");
	printf("���� �� �� ��ȭ ���--\n");
	printf(" ��ȭ�� �� [ ");
	printf("%d", movieNum - movieWatched);
	printf("]-\n\n");


	for (int i = 0; i < movieWatched; i++)
	{
		dequeue(&queue);
	}

	queue_print(&queue);


}