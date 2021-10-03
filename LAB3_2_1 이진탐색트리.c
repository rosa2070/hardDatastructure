#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef int element;
typedef struct TreeNode {
	element key;
	struct TreeNode *left, *right;
} TreeNode;

// ��ȯ���� Ž�� �Լ�
TreeNode * search(TreeNode * node, int key)
{
	//����Ž��Ʈ�� Ž�� ���� �߰� 
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

TreeNode * new_node(int item)
{
	TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp; 
}

TreeNode * insert_node(TreeNode * node, int key)
{
	//����Ž��Ʈ�� ���� ���� �߰� 	
	if (node == NULL) return new_node(key);
	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);
	return node;
}

TreeNode * min_value_node(TreeNode * node)
{
	TreeNode * current = node;

	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;

	return current;
}
// ���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ� 
// ���ο� ��Ʈ ��带 ��ȯ�Ѵ�. 
TreeNode * delete_node(TreeNode * root, int key)
{
	//����Ž��Ʈ�� ����  ���� �߰� 
	if (root == NULL) return root;
	if (key < root->key)
		root->left = delete_node(root->left, key);
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		TreeNode* temp = min_value_node(root->right);
		root->key = temp->key;
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}
// ���� ��ȸ
void preorder( TreeNode *root ){
	// ������ȸ �ڵ� �߰� 
	if (root != NULL) {
		printf("[%d]", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}


// ���� ��ȸ
void inorder(TreeNode * root) {
	// ������ȸ �ڵ� �߰� 
	if (root != NULL) {
		inorder(root->left);
		printf("[%d]", root->key);
		inorder(root->right);
	}
}

// ���� ��ȸ
void postorder( TreeNode *root ){
	//���� ��ȸ �ڵ� �߰�
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d]", root->key);
	}

}

int get_node_count(TreeNode *node)
{
	//��ü ��� �� ���ϴ� �ڵ��߰�  
	if (node == NULL)
		return 0;
	else
		return 1 + get_node_count(node->left) + get_node_count(node->right);
}

// leaf ���(�ڽĳ���� �� 0)�� �� 
int get_leaf_count(TreeNode *node)
{
		//�ܸ� ��� �� ���ϴ� �ڵ� �߰�  
	if (node == NULL) return 0;
	if (node->left == NULL && node->right == NULL) return 1;
	else return get_leaf_count(node->left) + get_leaf_count(node->right);
}


 
int get_height(TreeNode *node)
{
	//Ʈ���� ���� ���ϴ� �ڵ� �߰� 
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;

}


/*level order�� ���� ť �ڵ� */
//�����ϸ� ������ ���Ϸ� �����ΰ� include �ϴ� ����� ���� 

// ================ ����ť �ڵ� ���� =================
#define MAX_QUEUE_SIZE 100
typedef TreeNode * Element;
typedef struct { // ť Ÿ��
	Element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���� ���� ���� �Լ�
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ���� �Լ�
void enqueue(QueueType *q, Element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode *ptr)
{
	//���� ��ȸ �ڵ� �߰� 
	QueueType q;

	init_queue(&q);

	if (ptr == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf("[%d]", ptr->key);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}


int main(void)
{
	TreeNode * root = NULL;
	TreeNode * tmp = NULL;

	// ���� ���� �׽�Ʈ 
	printf("[���� ����] : 35 18  7 26 12  3 68 22 30 99");

	// ���⿡ insert_node()�Լ��� ȣ���Ͽ� ���� ���õ� ������ �����ϴ� �ڵ� �߰�
	root = insert_node(root, 35);
	root = insert_node(root, 18);
	root = insert_node(root, 7);
	root = insert_node(root, 26);
	root = insert_node(root, 12);
	root = insert_node(root, 3);
	root = insert_node(root, 68);
	root = insert_node(root, 22);
	root = insert_node(root, 30);
	root = insert_node(root, 99);

	 
	printf("\n"); 
	//Ʈ�� ���� ��� 
	printf("\n ������ȸ: ");
	inorder(root);
	printf("\n ������ȸ: ");
	preorder(root);
	printf("\n ������ȸ: ");
	postorder(root);
	printf("\n ������ȸ: ");
	level_order(root);
	
	printf("\n\n");
	printf("����� ���� = %d\n", get_node_count(root));
	printf("�ܸ��� ���� = %d\n", get_leaf_count(root));
	printf("Ʈ���� ���� = %d\n", get_height(root));

	
	printf("\n\n");
	// Ž�� ���� �׽�Ʈ 
	if (search(root, 26) != NULL)
		printf("[Ž�� ����]: ���� [%2d] \n", 26);
	else
		printf("[Ž�� ����]: ���� No[%2d] \n", 26);
		
	// Ž�� ���� �׽�Ʈ
	if (search(root, 25) != NULL)
		printf("[Ž�� ����]: ���� [%2d] \n", 25); 
	else
		printf("[Ž�� ����]: ���� No [%2d] \n", 25);
		
	// ���� ���� �׽�Ʈ 
	printf("\n    �ʱ�Ʈ������: ������ȸ: "); level_order(root);
	delete_node(root, 3);
	printf("\ncase1: < 3> ����: ������ȸ: "); level_order(root);
	delete_node(root, 68);
	printf("\ncase2: <68> ����: ������ȸ: "); level_order(root);
	delete_node(root, 18);
	printf("\ncase3: <18> ����: ������ȸ: "); level_order(root);
	delete_node(root, 35);
	printf("\ncase3: <35> root: ������ȸ: "); level_order(root);
	
	return 0;
}
