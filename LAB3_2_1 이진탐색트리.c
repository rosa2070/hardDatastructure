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

// 순환적인 탐색 함수
TreeNode * search(TreeNode * node, int key)
{
	//이진탐색트리 탐색 연산 추가 
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
	//이진탐색트리 삽입 연산 추가 	
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

	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;

	return current;
}
// 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고 
// 새로운 루트 노드를 반환한다. 
TreeNode * delete_node(TreeNode * root, int key)
{
	//이진탐색트리 삭제  연산 추가 
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
// 전위 순회
void preorder( TreeNode *root ){
	// 전위순회 코드 추가 
	if (root != NULL) {
		printf("[%d]", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}


// 중위 순회
void inorder(TreeNode * root) {
	// 중위순회 코드 추가 
	if (root != NULL) {
		inorder(root->left);
		printf("[%d]", root->key);
		inorder(root->right);
	}
}

// 후위 순회
void postorder( TreeNode *root ){
	//후위 순회 코드 추가
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d]", root->key);
	}

}

int get_node_count(TreeNode *node)
{
	//전체 노드 수 구하는 코드추가  
	if (node == NULL)
		return 0;
	else
		return 1 + get_node_count(node->left) + get_node_count(node->right);
}

// leaf 노드(자식노드의 수 0)의 수 
int get_leaf_count(TreeNode *node)
{
		//단말 노드 수 구하는 코드 추가  
	if (node == NULL) return 0;
	if (node->left == NULL && node->right == NULL) return 1;
	else return get_leaf_count(node->left) + get_leaf_count(node->right);
}


 
int get_height(TreeNode *node)
{
	//트리의 높이 구하는 코드 추가 
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;

}


/*level order를 위한 큐 코드 */
//가능하면 별도의 파일로 만들어두고 include 하는 방법이 좋음 

// ================ 원형큐 코드 시작 =================
#define MAX_QUEUE_SIZE 100
typedef TreeNode * Element;
typedef struct { // 큐 타입
	Element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 함수
void init_queue(QueueType *q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType *q, Element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode *ptr)
{
	//레벨 순회 코드 추가 
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

	// 삽입 연산 테스트 
	printf("[삽입 연산] : 35 18  7 26 12  3 68 22 30 99");

	// 여기에 insert_node()함수를 호출하여 위에 제시된 데이터 삽입하는 코드 추가
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
	//트리 정보 출력 
	printf("\n 중위순회: ");
	inorder(root);
	printf("\n 전위순회: ");
	preorder(root);
	printf("\n 후위순회: ");
	postorder(root);
	printf("\n 레벨순회: ");
	level_order(root);
	
	printf("\n\n");
	printf("노드의 개수 = %d\n", get_node_count(root));
	printf("단말의 개수 = %d\n", get_leaf_count(root));
	printf("트리의 높이 = %d\n", get_height(root));

	
	printf("\n\n");
	// 탐색 연산 테스트 
	if (search(root, 26) != NULL)
		printf("[탐색 연산]: 성공 [%2d] \n", 26);
	else
		printf("[탐색 연산]: 실패 No[%2d] \n", 26);
		
	// 탐색 연산 테스트
	if (search(root, 25) != NULL)
		printf("[탐색 연산]: 성공 [%2d] \n", 25); 
	else
		printf("[탐색 연산]: 실패 No [%2d] \n", 25);
		
	// 삭제 연산 테스트 
	printf("\n    초기트리상태: 레벨순회: "); level_order(root);
	delete_node(root, 3);
	printf("\ncase1: < 3> 삭제: 레벨순회: "); level_order(root);
	delete_node(root, 68);
	printf("\ncase2: <68> 삭제: 레벨순회: "); level_order(root);
	delete_node(root, 18);
	printf("\ncase3: <18> 삭제: 레벨순회: "); level_order(root);
	delete_node(root, 35);
	printf("\ncase3: <35> root: 레벨순회: "); level_order(root);
	
	return 0;
}
