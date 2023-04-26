/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node { // ��� ����ü ����
	int key; // Ű��
	struct Node* link; // ��带 ����Ű�� ������ ����
} listNode;

typedef struct Head { // ��� ����ü ����
	struct Node* first; // ù��° ��带 ����Ű�� ������ ����
} headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h); // ����Ʈ �ʱ�ȭ �Լ�
int freeList(headNode* h);  // ����Ʈ�� �����ϴ� �Լ�

int insertFirst(headNode* h, int key); // ù��°�� ��� �����ϴ� �Լ�
int insertNode(headNode* h, int key); // ��� ���� �Լ�
int insertLast(headNode* h, int key); // �������� ��� �����ϴ� �Լ�

int deleteFirst(headNode* h); // ù��° ��� ���� �Լ�
int deleteNode(headNode* h, int key); // ��� ���� �Լ�
int deleteLast(headNode* h); // ������ ��� ���� �Լ�
int invertList(headNode* h); // ����Ʈ�� �������� ����� �Լ�

void printList(headNode* h); // ����Ʈ ��� �Լ�

int main()
{
	char command; // �Է¹��� ��ɾ�
	int key; // �Է¹��� Ű
	headNode* headnode=NULL; // �������� ����� ����ų ������

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		printf("[--------------  [�ֻ�]  	[2022041062]  --------------]\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); // ����Ʈ �ʱ�ȭ �Լ� ȣ��
			break;
		case 'p': case 'P':
			printList(headnode); // ����Ʈ ��� �Լ� ȣ��
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); // Ű �Է¹���
			insertNode(headnode, key); // ��� ���� �Լ� ȣ��
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // Ű �Է¹���
			deleteNode(headnode, key); // ��� ���� �Լ� ȣ��
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // Ű �Է¹���
			insertLast(headnode, key); // �������� ��� �����ϴ� �Լ� ȣ��
			break;
		case 'e': case 'E':
			deleteLast(headnode); // ������ ��� ���� �Լ� ȣ��
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // Ű �Է¹���
			insertFirst(headnode, key); // ù��°�� ��� �����ϴ� �Լ� ȣ��
			break;
		case 't': case 'T':
			deleteFirst(headnode); // ù��° ��� ���� �Լ� ȣ��
			break;
		case 'r': case 'R':
			invertList(headnode); // ����Ʈ�� �������� ����� �Լ� ȣ��
			break;
		case 'q': case 'Q':
			freeList(headnode); // ����Ʈ�� �����ϴ� �Լ� ȣ��
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // ��ɾ� ��Ͽ� ���� ���� �Է¹��� ��
			break;
		}

	}while(command != 'q' && command != 'Q'); // q�� �Է¹����� ����

	return 0; // �������Ḧ ǥ���ϱ� ���� return 0���� �ٲپ����ϴ�
}

headNode* initialize(headNode* h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // ���ο� ��� �����Ҵ�
	node->key = key; // Ű ������ ����

	node->link = h->first; // ���� ù��° ���� ���� �����ϴ� ����� �ڿ� �̾��� (�ƹ��͵� ���� �� ����Ʈ���ٸ�, NULL�� ���Ե� ���̰�, ����� ������ ����)
	h->first = node; // ��带 ù��° �ڸ��� ����

	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	listNode* ptr = h->first; // ù��° ��带 ����ų listNode ������ ���� ptr �߰�

	if(!ptr || key < ptr->key) // ���� ù��° ����� Ű�� �Է¹��� key���� ũ�ų�, ����Ʈ�� �� ��쿡�� ù��° ��� ���� �Լ��� ����
	{
		insertFirst(h, key);
		return 0;
	}
	else
	{

		listNode* node = (listNode*)malloc(sizeof(listNode)); // ���ο� ��� �����Ҵ�
		node->key = key; // Ű ������ ����
		while((ptr->link != NULL) && !(ptr->link->key > key)) // ���� ��尡 ��� ��¿�� ���� �־�� �ϰų�, ���� ����� Ű���� �Է¹��� Ű�� �����ÿ�(��. �־�� �ϴ� ��Ȳ�� �ÿ�) ����
		{ // �׷��� ������ ptr�� ��� ���� ���� �̵���Ŵ
			ptr = ptr->link;
		}

		node->link = ptr->link; // ���Խ�ų ����� ��ũ�� �� ����� Ű���� ū Ű�� ���� ���, �� ptr�� ���� ����� �ּҸ� �����ϰ� (���� ã�� ���ϰ� ������ ������ ��쿡�� NULL�� �� ����.)
		ptr->link = node; // ptr�� ���� ����Ű�� ��� ���, ���� ���Ե� ��带 ����Ű���� �� (���� ������ �� ��쿡��, ��������� �������� ���Ե�.)

		return 0;
	}

}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* ptr = h->first; // ù��° ��带 ����ų listNode ������ ���� ptr �߰�
	if(!ptr) // ���� ����Ʈ�� �� ��쿡�� ù��° ��� ���� �Լ��� ����
	{
		insertFirst(h, key);
		return 0;
	}
	else
	{
		listNode* node = (listNode*)malloc(sizeof(listNode)); // ���ο� ��� �����Ҵ�
		node->key = key; // Ű ������ ����

		while(ptr->link != NULL) // �������� �־�� �ϹǷ�, ptr�� ���� ��尡 ���� ������ while���� ����
		{
			ptr = ptr->link; // ptr�� ��� ���� ���� �̵���Ų��
		}

		node->link = NULL; // ������ ����̹Ƿ� link�� NULL�� ���Խ�Ű��, (��� insertNode�� ���� �κ�ó��, ptr->link�� �׳� �ξ �����ϴ�.)
		ptr->link = node; // ptr�� ���� ����Ű�� ��� ���, ���� ���Ե� ��带 ����Ű���� �� 

		return 0;
	}
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (!h->first) // ���� ���� ���ٸ�
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* temp = h->first; // ������ ��带 ����Ű�� listNode ������ temp�� �����
	h->first = temp->link; // ����� first�� ������ ����� ���� ��忡 �̾��ش�
	free(temp); // ��带 �����Ѵ�
	return 0;
}


/**
 * list���� key�� ���� ��� ����. �տ������� Ž���Ͽ�, ���� ���� ����� �ش� Ű�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	listNode* ptr = h->first; // ������ ����� ���� ��带 ����ų listNode ������ ���� ptr�� �����
	
	if (!ptr) // ���� ���� ���ٸ�
	{
		printf("nothing to delete.\n");
		return 1;
	}
	else if(ptr->key == key) // ���� ù ����� Ű�� ã�� key ���̶��, deleteFirst �Լ��� �������ش�
	{
		deleteFirst(h);
		return 0;
	}

	while(ptr->link != NULL && ptr->link->key != key) // �ش��ϴ� key�� ��带 ������ �ϹǷ�, ptr�� ���� ����� Ű�� �ش��ϴ� Ű�̸� �����ϵ��� while���� ����. 
	{ // �׸��� ���� ã�� ������ ��츦 ����Ͽ�, ���� ��尡 NULL�̸�(�� ��尡 �������̸�) ������Ų��.
		ptr = ptr->link; // ptr�� ��� ���� ���� �̵���Ų��
	}

	if (ptr->link == NULL) // ���� ������ �ش��ϴ� key�� ���� ��带 ã�� ���ߴٸ�
	{
		printf("cannot find the node for key = %d\n", key);
		return 1;
	}

	listNode* temp = ptr->link; // ���� ��带 ����Ű�� listNode ������ temp�� �����
	ptr->link = temp->link; // ���� ����� ���� ��带 ����Ű�� ptr�� link�� ���� ����� ���� ���� �����Ų��
	free(temp); // temp�� �����

	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* ptr = h->first; // ������ ����� �� ��带 ����ų listNode ������ ptr�� �����
	if (!ptr) // ���� ���� ���ٸ�
	{
		printf("nothing to delete.\n");
		return 1;
	}
	else if (ptr->link == NULL) // ���� ���� ù��° �����
	{
		deleteFirst(h);
		return 0;
	}

	while(ptr->link->link != NULL) // ������ ��带 ������ �ϹǷ�, ptr�� �ٴ��� ��尡 ���� ������(ptr�� ������ ����� ���� ��带 ����ų ������) while���� ����
	{
		ptr = ptr->link; // ptr�� ��� ���� ���� �̵���Ų��
	}
	free(ptr->link);
	ptr->link = NULL; // ptr�� ���� ���, �� ������ ��带 ���� ��, ������ ���� ���� ptr�� ��ũ�� NULL�� ������ش�
	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
 
int invertList(headNode* h) {
	listNode* one, *two, *three;
	if(h->first == NULL) // ��尡 �Ѱ��� ���ٸ�, �׳� ����
	{
		printf("nothing to invert...\n");
		return 1;
	}

	// �� �� ��Ȳ�� �����۵��� ����

	one = h->first; // one �����ʹ� ù ��带 ����Ű�� �ϰ�,
	three = one->link; // three �����ʹ� �� ����(�ι�°) ���,
	two = three; // two �����ʹ� ������ three �����Ϳ� �����ϰ� �ι�° ��带 ����Ų��.
	one->link = NULL; // ù ����� ������ NULL�� ������ش�.

	while(three != NULL) // ������ �� ������ �ݺ��� ���̴�
	{
		three = three->link; // three�� ���� ���� �̵������ش� (ó�� ������ �ݺ����̶�� ��������, ����° ���� �̵�)
		two->link = one; // two�� link�� �� ���� �ٲ۴� (ó�� �����ߴٴ� ��������, �ι�° ����� ���� ��带 ù��° ���� �ٲ�)
		one = two; // ���̻� one�� ���� ��忡�� ������ �ʿ䰡 ������, one�� ���� ����� two�� �̵��Ѵ� (ó���̶�� ��������, one�� �ι�° ���� �̵�)
		two = three; // ���� ���� ����� link�� �ٲپ��־�� �ϹǷ�, two�� ���� ����� three�� �̵��Ѵ� (ó���̶�� ��������, ����° ���� �̵�)
	} // �ش� ������ ��� �ݺ��Ǹ鼭, ��� ����� link�� �ڱ� �ڽ��� �� ��带 ����Ű�� �ȴ�.

	h->first = one; // three�� NULL, ���������� two�� NULL�� ����Ű��, one�� ������ ��带 ����Ű�� ��Ȳ����, h�� first�� one���� �������ָ� ����Ʈ�� �Ϻ��ϰ� ������ �ȴ�.

	return 0;
}



void printList(headNode* h) {
	int i = 0; // ��� ���� ���� ���� ����
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // ������� ���� ���
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { // ��� ��带 ����ϱ� ����, NULL�� ������ �ݺ�
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link; // ���� ���� �̵�
		i++; // ��� ���� ī��Ʈ��
	}

	printf("  items = %d\n", i); // ����� �� ����
}

