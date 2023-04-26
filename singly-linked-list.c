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

typedef struct Node { // 노드 구조체 정의
	int key; // 키값
	struct Node* link; // 노드를 가르키는 포인터 변수
} listNode;

typedef struct Head { // 헤더 구조체 정의
	struct Node* first; // 첫번째 노드를 가르키는 포인터 변수
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h); // 리스트 초기화 함수
int freeList(headNode* h);  // 리스트를 프리하는 함수

int insertFirst(headNode* h, int key); // 첫번째에 노드 삽입하는 함수
int insertNode(headNode* h, int key); // 노드 삽입 함수
int insertLast(headNode* h, int key); // 마지막에 노드 삽입하는 함수

int deleteFirst(headNode* h); // 첫번째 노드 제거 함수
int deleteNode(headNode* h, int key); // 노드 제거 함수
int deleteLast(headNode* h); // 마지막 노드 제거 함수
int invertList(headNode* h); // 리스트를 역순으로 만드는 함수

void printList(headNode* h); // 리스트 출력 함수

int main()
{
	char command; // 입력받을 명령어
	int key; // 입력받을 키
	headNode* headnode=NULL; // 실질적인 헤더를 가리킬 포인터

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
		printf("[--------------  [최상영]  	[2022041062]  --------------]\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); // 리스트 초기화 함수 호출
			break;
		case 'p': case 'P':
			printList(headnode); // 리스트 출력 함수 호출
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); // 키 입력받음
			insertNode(headnode, key); // 노드 삽입 함수 호출
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // 키 입력받음
			deleteNode(headnode, key); // 노드 제거 함수 호출
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // 키 입력받음
			insertLast(headnode, key); // 마지막에 노드 삽입하는 함수 호출
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 마지막 노드 제거 함수 호출
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // 키 입력받음
			insertFirst(headnode, key); // 첫번째에 노드 삽입하는 함수 호출
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 첫번째 노드 제거 함수 호출
			break;
		case 'r': case 'R':
			invertList(headnode); // 리스트를 역순으로 만드는 함수 호출
			break;
		case 'q': case 'Q':
			freeList(headnode); // 리스트를 프리하는 함수 호출
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 명령어 목록에 없는 것을 입력받을 시
			break;
		}

	}while(command != 'q' && command != 'Q'); // q를 입력받으면 종료

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

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적할당
	node->key = key; // 키 데이터 대입

	node->link = h->first; // 원래 첫번째 노드는 새로 대입하는 노드의 뒤에 이어줌 (아무것도 없는 빈 리스트였다면, NULL이 대입될 것이고, 결과는 문제가 없음)
	h->first = node; // 노드를 첫번째 자리에 대입

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	listNode* ptr = h->first; // 첫번째 노드를 가리킬 listNode 포인터 변수 ptr 추가

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

		node->link = ptr->link; // 삽입시킬 노드의 링크에 현 노드의 키보다 큰 키를 가진 노드, 즉 ptr의 다음 노드의 주소를 대입하고 (만약 찾지 못하고 끝까지 돌았을 경우에는 NULL이 될 것임.)
		ptr->link = node; // ptr은 원래 가리키던 노드 대신, 새로 삽입된 노드를 가리키도록 함 (만약 끝까지 돈 경우에는, 결과적으로 마지막에 삽입됨.)

		return 0;
	}

}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* ptr = h->first; // 첫번째 노드를 가리킬 listNode 포인터 변수 ptr 추가
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

		node->link = NULL; // 마지막 노드이므로 link에 NULL을 대입시키고, (사실 insertNode의 삽입 부분처럼, ptr->link로 그냥 두어도 무방하다.)
		ptr->link = node; // ptr은 원래 가리키던 노드 대신, 새로 삽입된 노드를 가리키도록 함 

		return 0;
	}
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (!h->first) // 지울 것이 없다면
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* temp = h->first; // 삭제할 노드를 가리키는 listNode 포인터 temp를 만든다
	h->first = temp->link; // 헤더의 first를 삭제할 노드의 다음 노드에 이어준다
	free(temp); // 노드를 삭제한다
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제. 앞에서부터 탐색하여, 먼저 만난 노드중 해당 키를 가진 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* ptr = h->first; // 삭제할 노드의 이전 노드를 가리킬 listNode 포인터 변수 ptr을 만든다
	
	if (!ptr) // 지울 것이 없다면
	{
		printf("nothing to delete.\n");
		return 1;
	}
	else if(ptr->key == key) // 만약 첫 노드의 키가 찾던 key 값이라면, deleteFirst 함수로 연결해준다
	{
		deleteFirst(h);
		return 0;
	}

	while(ptr->link != NULL && ptr->link->key != key) // 해당하는 key의 노드를 지워야 하므로, ptr의 다음 노드의 키가 해당하는 키이면 정지하도록 while문을 돈다. 
	{ // 그리고 만약 찾지 못했을 경우를 대비하여, 다음 노드가 NULL이면(현 노드가 마지막이면) 정지시킨다.
		ptr = ptr->link; // ptr을 계속 다음 노드로 이동시킨다
	}

	if (ptr->link == NULL) // 만약 끝까지 해당하는 key를 가진 노드를 찾지 못했다면
	{
		printf("cannot find the node for key = %d\n", key);
		return 1;
	}

	listNode* temp = ptr->link; // 지울 노드를 가리키는 listNode 포인터 temp를 만든다
	ptr->link = temp->link; // 지울 노드의 이전 노드를 가리키는 ptr의 link를 지울 노드의 다음 노드로 연결시킨다
	free(temp); // temp를 지운다

	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* ptr = h->first; // 삭제할 노드의 전 노드를 가리킬 listNode 포인터 ptr을 만든다
	if (!ptr) // 지울 것이 없다면
	{
		printf("nothing to delete.\n");
		return 1;
	}
	else if (ptr->link == NULL) // 지울 것이 첫번째 노드라면
	{
		deleteFirst(h);
		return 0;
	}

	while(ptr->link->link != NULL) // 마지막 노드를 지워야 하므로, ptr의 다다음 노드가 없을 때까지(ptr이 마지막 노드의 직전 노드를 가리킬 때까지) while문을 돈다
	{
		ptr = ptr->link; // ptr을 계속 다음 노드로 이동시킨다
	}
	free(ptr->link);
	ptr->link = NULL; // ptr의 다음 노드, 즉 마지막 노드를 지운 뒤, 오류를 막기 위해 ptr의 링크는 NULL로 만들어준다
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
 
int invertList(headNode* h) {
	listNode* one, *two, *three;
	if(h->first == NULL) // 노드가 한개도 없다면, 그냥 리턴
	{
		printf("nothing to invert...\n");
		return 1;
	}

	// 그 외 상황은 정상작동될 것임

	one = h->first; // one 포인터는 첫 노드를 가리키게 하고,
	three = one->link; // three 포인터는 그 다음(두번째) 노드,
	two = three; // two 포인터는 지금은 three 포인터와 동일하게 두번째 노드를 가리킨다.
	one->link = NULL; // 첫 노드의 다음을 NULL로 만들어준다.

	while(three != NULL) // 끝까지 돌 때까지 반복할 것이다
	{
		three = three->link; // three를 다음 노드로 이동시켜준다 (처음 진입한 반복문이라는 가정에서, 세번째 노드로 이동)
		two->link = one; // two의 link를 앞 노드로 바꾼다 (처음 진입했다는 가정에서, 두번째 노드의 다음 노드를 첫번째 노드로 바꿈)
		one = two; // 더이상 one이 가진 노드에는 접근할 필요가 없으니, one는 다음 노드인 two로 이동한다 (처음이라는 가정에서, one을 두번째 노드로 이동)
		two = three; // 이제 다음 노드의 link를 바꾸어주어야 하므로, two는 다음 노드인 three로 이동한다 (처음이라는 가정에서, 세번째 노드로 이동)
	} // 해당 과정이 계속 반복되면서, 모든 노드의 link가 자기 자신의 앞 노드를 가리키게 된다.

	h->first = one; // three는 NULL, 마찬가지로 two는 NULL를 가리키고, one은 마지막 노드를 가리키는 상황에서, h의 first를 one으로 지정해주면 리스트가 완벽하게 역순이 된다.

	return 0;
}



void printList(headNode* h) {
	int i = 0; // 노드 수를 세기 위한 변수
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // 헤더조차 없는 경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { // 모든 노드를 출력하기 위해, NULL일 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link; // 다음 노드로 이동
		i++; // 노드 수를 카운트함
	}

	printf("  items = %d\n", i); // 노드의 총 갯수
}

