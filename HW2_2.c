#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert_last(ListNode* head, int value)
{
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;
	if (head == NULL)
		head = p;
	else {
		while (temp->link != NULL) {
			temp = temp->link;
		}
		temp->link = p;
	}
	return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

ListNode* delete_last(ListNode* head)
{
	ListNode* temp = head;
	ListNode* prevTemp=NULL;
	ListNode* removed;
	if (head == NULL) error("������ �׸��� ����");
	if (temp->link == NULL)
	{
		removed = temp;
		temp->link = NULL;
		free(removed);
		return NULL;

	}
	else
	{
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		removed = temp;
		prevTemp->link = NULL;
		free(removed);
		return head;
	}
}

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}

ListNode* reverse(ListNode* head)
{
	ListNode* p, * q, * r;
	p = head;
	q = NULL;
	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

ListNode* concat(ListNode* head1, ListNode* head2)
{
	ListNode* p;
	if (head1 == NULL) return head2;
	else if (head2 == NULL) return head1;
	else {
		p = head1;
		while (p->link != NULL)
			p = p->link;
		p->link = head2;
		return head1;
	}
}

//(A)
int is_in_list(ListNode* head, element item)
{
	ListNode* p;
	p = head;
	while (p != NULL) {
		if (p->data == item)
			return 1;
		p = p->link;
	}
	return 0;
}

int get_length(ListNode* head)
{
	int len = 0;
	ListNode* p;
	for (p = head; p != NULL; p = p->link)
		len++;
	return len;

}

int get_total(ListNode* head)
{
	int total = 0;
	ListNode* p;
	for (p = head; p != NULL; p = p->link)
		total += p->data;
	return total;
}

element get_entry(ListNode* head, int pos)
{
	int len = 0;
	ListNode* p;
	for (p = head; p != NULL; p = p->link) {
		if (pos == len) {
			return p->data;
		}
		len++;
	}


}

ListNode* delete_by_key(ListNode* head, int key)
{
	ListNode* temp = head;
	ListNode* prevTemp = NULL;
	ListNode* removed;
	if (head == NULL) error("������ �׸��� ����");
	while (temp->data != key) {
		prevTemp = temp;
		temp = temp->link;
	}
	removed = temp;
	prevTemp->link = removed->link;
	free(removed);
	return head;
	
}

ListNode* insert_pos(ListNode* head, int pos, element value)
{
	int len = 0;
	ListNode* p;
	ListNode* newNode;
	if (pos == 0) {
			ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
			newNode->data = value;
			newNode->link = head;
			head = newNode;
			return head;
	}
	len++;
	for (p = head; p != NULL; p = p->link) {
		if (pos == len) {
			ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
			newNode->data = value;
			newNode->link = p->link;
			p->link = newNode;
			return head;
		}
		len++;
	}

}

ListNode* delete_pos(ListNode* head, int pos)
{
	ListNode* temp= head;
	ListNode* removed;
	ListNode* prevTemp = NULL;
	if (head == NULL) error("������ �׸��� ����");
	if (pos == 0) {
		removed = head;
		head = removed->link;
		free(removed);
		return head;
	}
	for (int i = 0; i < pos; i++) {
		prevTemp = temp;
		temp = temp->link;
	}
	removed = temp;
	prevTemp->link = removed->link;
	free(removed);
	return head;

}

int main(void)
{
	ListNode* list1 = NULL, * list2 = NULL, * list3;

	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	printf("list1 = ");
	print_list(list1);

	//list1�� �� �� ��带 ����
	list1 = delete_first(list1);
	printf("list1 = ");
	print_list(list1);

	//list2 = 11->22->33->44�� �����
	list2 = insert_first(list2, 11);
	list2 = insert_last(list2, 22);
	list2 = insert_last(list2, 33);
	list2 = insert_last(list2, 44);
	printf("list2 = ");
	print_list(list2);

	//list2�� �� �� ��带 ����
	delete_last(list2);
	printf("list2 = ");
	print_list(list2);

	//list2�� �������� �ٲ� ����Ʈ�� list3�� ����Ű�� �Ѵ�.
	list3 = reverse(list2);
	printf("list3 = ");
	print_list(list3);

	//list1�� list3�� ���ļ� list1�� ����Ű�� �Ѵ�.
	list1 = concat(list1, list3);
	printf("list1 = ");
	print_list(list1);

	//(A) ����: ���⼭���ʹ� list1�� ����Ͽ� �Լ����� �׽�Ʈ����
	printf("\n- �� ���Ĵ� list1�� ����� �Լ��� �׽�Ʈ-\n");
	printf("10�� list1�� %s\n", is_in_list(list1, 10) ? "�ֽ��ϴ�" : "�����ϴ�");
	printf("25�� list1�� %s\n", is_in_list(list1, 25) ? "�ֽ��ϴ�" : "�����ϴ�");
	printf("list1�� ��� �� = %d\n", get_length(list1));
	printf("list1�� ��� ������ ���� �� = %d\n", get_total(list1));
	printf("�� ��° ��忡 �ִ� �����ʹ� %d�Դϴ�\n", get_entry(list1, 2));
	delete_by_key(list1, 33);
	printf("list1 = ");
	print_list(list1);
	insert_pos(list1, 3, 40);
	printf("list1 = ");
	print_list(list1);
	delete_pos(list1, 3);
	printf("list1 = ");
	print_list(list1);

}


