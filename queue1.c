#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;