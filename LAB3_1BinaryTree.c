#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#pragma warning(disable: 4996)

typedef struct TreeNode {
	char data;
	struct TreeNode* left, * right;
}TreeNode;

void inorder(TreeNode* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[%c]", root->data);
		inorder(root->right);

	}
}

void preorder(TreeNode* root) {
	if (root != NULL) {
		printf("[%c]", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(TreeNode* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%c]", root->data);
	}
}

// ============= 원형큐 코드 시작 ========================
#define MAX_QUEUE_SIZE 100
typedef TreeNode* element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
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

void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode* ptr)
{
	QueueType q;

	init_queue(&q);

	if (ptr == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf("[%c]", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}

int get_node_count(TreeNode* node)
{
	if (node == NULL)
		return 0;
	else
		return 1 + get_node_count(node->left) + get_node_count(node->right);
}

get_leaf_count(TreeNode* node)
{
	if (node == NULL) return 0;
	if (node->left == NULL && node->right == NULL) return 1;
	else return get_leaf_count(node->left) + get_leaf_count(node->right);
}

int get_height(TreeNode* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}


TreeNode n1 = { 'D', NULL, NULL };
TreeNode n2 = { 'E', NULL, NULL };
TreeNode n3 = { 'F', NULL, NULL };
TreeNode n4 = { 'B', &n1, &n2 };
TreeNode n5 = { 'C', &n3, NULL };
TreeNode n6 = { 'A', &n4, &n5 };
TreeNode* root = &n6;

int main(void)
{
	printf("중위 순회: ");
	inorder(root);
	printf("\n");

	printf("전위 순회: ");
	preorder(root);
	printf("\n");

	printf("후위 순회: ");
	postorder(root);
	printf("\n");

	printf("레벨 순회: ");
	level_order(root);
	printf("\n");

	printf("노드의 개수 = %d\n", get_node_count(root));
	printf("단말의 개수 = %d\n", get_leaf_count(root));
	printf("트리의 높이 = %d\n", get_height(root));

	return 0;
}