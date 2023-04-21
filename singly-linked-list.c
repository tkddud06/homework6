/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

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

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0; // 정상종료를 표시하기 위해 return 0으로 바꾸었습니다
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
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
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* ptr = h->first;

	if(!ptr || key < ptr->key) // 만약 첫번째 노드의 키가 입력받은 key보다 크거나, 리스트가 빈 경우에는 첫번째 노드 삽입 함수로 연결
	{
		insertFirst(h, key);
		return 0;
	}
	else
	{

		listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적할당
		node->key = key; // 키 데이터 대입
		while((ptr->link != NULL) && !(ptr->link->key > key)) // 다음 노드가 없어서 어쩔수 없이 넣어야 하거나, 다음 노드의 키보다 입력받은 키가 작을시에(즉. 넣어야 하는 상황일 시에) 정지
		{ // 그렇지 않으면 ptr을 계속 다음 노드로 이동시킴
			ptr = ptr->link;
		}

		node->link = ptr->link; // 삽입시킬 노드의 링크에 현 노드의 키보다 큰 키를 가진 노드, 즉 ptr의 다음 노드의 주소를 대입하고 (만약 찾지 못하고 끝까지 돌았을 경우에는 NULL)
		ptr->link = node; // ptr은 원래 가리키던 노드 대신, 새로 삽입된 노드를 가리키도록 함

		return 0;
	}

}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* ptr = h->first;
	if(!ptr) // 만약 리스트가 빈 경우에는 첫번째 노드 삽입 함수로 연결
	{
		insertFirst(h, key);
		return 0;
	}
	else
	{
		listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적할당
		node->key = key; // 키 데이터 대입

		while(ptr->link != NULL) // 마지막에 넣어야 하므로, ptr의 다음 노드가 없을 때까지 while문을 돈다
		{
			ptr = ptr->link; // ptr을 계속 다음 노드로 이동시킨다
		}

		node->link = NULL; // 마지막 노드이므로 link에 NULL을 대입시키고,
		ptr->link = node; // ptr은 원래 가리키던 노드 대신, 새로 삽입된 노드를 가리키도록 함

		return 0;
	}
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* temp = h->first; // 삭제할 노드를 가리키는 listNode 포인터 temp를 만든다
	h->first = temp->link; // 헤더의 first를 삭제할 노드의 다음 노드에 이어준다
	free(temp); // 노드를 삭제한다
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제. 앞에서부터 탐색하여, 먼저 만난 노드중 해당 키를 가진 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* ptr = h->first; // 삭제할 노드의 전 노드를 가리킬 listNode 포인터 ptr을 만든다
	if(ptr->key == key) // 만약 첫 노드의 키가 찾던 key 값이라면, deleteFirst 함수로 연결해준다
	{
		deleteFirst(h);
		return 0;
	}
	else
	{
		while(ptr->link != NULL && ptr->link->key != key) // 해당하는 key의 노드를 지워야 하므로, ptr의 다음 노드의 키가 해당하는 키이면 정지하도록 while문을 돈다. 그리고 만약 찾지 못했을 경우를 염두하여, 다음 노드가 NULL이면(현 노드가 마지막이면) 정지시킨다
		{
			ptr = ptr->link; // ptr을 계속 다음 노드로 이동시킨다
		}

		if (ptr->link == NULL) // 만약 해당하는 key를 가진 노드를 찾지 못했다면
		{
			printf("해당하는 노드를 찾지 못했습니다.\n");
			return 1;
		}

		listNode* temp = ptr->link; // 지울 노드를 가리키는 listNode 포인터 temp를 만든다
		ptr->link = temp->link; // 지울 노드의 이전 노드를 가리키는 ptr의 link를 지울 노드의 다음 노드로 연결시킨다
		free(temp); // temp를 지운다

		return 0;
	}

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* ptr = h->first; // 삭제할 노드의 전 노드를 가리킬 listNode 포인터 ptr을 만든다
	while(ptr->link->link != NULL) // 마지막 노드를 지워야 하므로, ptr의 다다음 노드가 없을 때까지(ptr이 마지막 노드의 직전 노드를 가리킬 때까지) while문을 돈다
	{
		ptr = ptr->link; // ptr을 계속 다음 노드로 이동시킨다
	}
	free(ptr->link);
	ptr->link = NULL; // ptr의 다음 노드, 즉 마지막 노드를 지운 뒤, ptr의 링크는 NULL로 만들어준다
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
 
int invertList(headNode* h) {
	listNode* one, *two, *three;
	if(h->first == NULL) // 노드가 한개도 없다면, 그냥 리턴
	{
		printf("리스트가 비었습니다.\n");
		return 1;
	}

	// 그 외 상황은 정상작동될 것임

	one = h->first;
	three = one->link;
	two = three;
	one->link = NULL;

	while(three != NULL)
	{
		three = three->link;
		two->link = one;
		one = two;
		two = three;
	}

	h->first = one;

	return 0;
}



void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

