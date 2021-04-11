/*
 * singly linked list
 *
 *  Data Structures
 *  Department of Computer Science
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
}headNode;


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
	headNode* headnode = NULL;

	do {
		printf("[----- [고승현] [2016039086] -----]\n");
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

		switch (command) {
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

	} while (command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 * 처음에 넣기위해서 노드를 만들고 h를 이용해서 처음 노드의 주소를 만든 노드의link값으로 연결
 * h->first에는 새로만든 노드의 주소값을 저장해준다.
 */
int insertFirst(headNode* h, int key) {
	
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
/*이런 경우는 포인터 변수가 3개가 필요하다
select:생성한 노드와 키값을 비교할 노드를 지정할 포인터변수
prevoew:노드의 삽입을 위해 select바로 이전 노드의 주소를 저장하고 있는 포인터변수
node:지정된 key값으로 저장할 노드의 주소를 저장할 포인터변수
select를 이용하여 노드와 만든노드의 key값을 비교하면서 적절한 위치에 노드를 삽입하고
preview의 link에는 새로운 노드의 주소를 할당하고 새로운 노드의 link에는 select노드의 주소를 할당한다*/
int insertNode(headNode* h, int key) {
	listNode* select = h->first;
	listNode* preview = NULL;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;
	if (h->first == NULL) {
		h->first = node;
		return 0;
	}
	if (node->key <= select->key) {
		node->link = select;
		h->first = node;
		return 0;
	}
	for (; select; select = select->link) {
		if (node->key <= select->key) {
			node->link = select;
			preview->link = node;
			break;
		}
		preview = select;
	}
	if (node->link == NULL) {
		preview->link = node;
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 * 노드를 key값을 저장해서 하나를 동적할당을 이용해서 만든다
 *마지막에 노드를 추가하므로 포인터 변수를 이용해서 가장 마지막의
 * 노드를 찾고 해당 노드의 link와 생성한 노드를 연결해준다
 */
int insertLast(headNode* h, int key) {
	listNode* select;
	listNode* node;
	select = h->first;
	node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;
	while (1) {
		if (select->link == NULL)
			break;
		else
			select = select->link;
	}
	select->link = node;

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 * 첫번쨰 노드가 없는 경우 바로 리턴한다
 * 그게 아니고 노드가 한개만 있는경우 해당 노드를
 * free하고 리턴한다
 * 그것도 아니면 노드가2개이상 존재하므로 가장 마지막 노드로 
 * 포인터를 이동시키고 해당 노드를 free해준다
 */
int deleteFirst(headNode* h) {
	listNode* select;
	select = h->first;
	if (h->first == NULL) {
		printf("no data\n");
		return 0;
	}
	if (select->link == NULL) {
		free(select);
		h->first = NULL;
	}
	else {
		h->first = select->link;
		free(select);
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 * 노드가 없는 경우는 바로 리턴해준다
 * 제거의 경우는 select를 이용해서 입력받은 key값과 동일한 노드를 찾고
 * 해당 노드와 해당 이전노드의 주소를 저장하는 preview를 이용하여 select다음
 * 노드와 preview의 link를 연결해주고 select를 free해서 해당 노드를 메모리에서
 * 해제해준다
 */
int deleteNode(headNode* h, int key) {
	listNode* select = h->first;
	listNode* preview = NULL;
	if (h->first == NULL)
		return 0;
	if (key == select->key) {
		deleteFirst(h);
		return 0;
	}
	else {
		for (; select; select = select->link) {
			if (key == select->key) {
				preview->link = select->link;
				free(select);
				break;
			}
			preview = select;
		}
		if (select == NULL) {
			printf("no such data\n");
		}
	}
	return 0;

}

/**
 * list의 마지막 노드 삭제
 * 일단 노드가 아무것도 없는 경우 처리해주고
 * 마지막 노드의 조건 마지막 노드의 link는 null임을 
 * 사용해서 select포인터 변수를 마지막 노드까지 이동시키고 
 마지막 노드의 데이터를 free시킨다 그리고 이전노드의 link의 
 주소를 null즉 이전노드를 마지막 노드로 설정해준다.
 */
int deleteLast(headNode* h) {
	if (h->first == NULL)
		return 0;
	listNode* select = h->first;
	listNode* preview = NULL;
	for (; select; select = select->link) {
		if (select->link == NULL) {
			free(select);
			preview->link = NULL;
			break;
		}
		preview = select;
	}
	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 * 리스트를 역순으로 배치하기 위해서 포인터변수 3개를 추가로 선언
 * middle: 노드의 연결을 바꿀포인터
 * next:middle의 노드를 바꾸는 경우 middle다음 노드를 지칭하기위함
 * preview:middle의 link와 역으로 연결할 노드를 지칭하는 포인터
 * 반복으로 수행후 마지막 노드의 연결을 수정하면 next는 null이고 
 * middle와 preview는 같은 노드를 지칭하게 되고 해당 노드와 h->first를
 * 연결을 해줘야 역순으로 연결이 완료된다.
 */
int invertList(headNode* h) {
	listNode* next = h->first;;
	listNode* middle=NULL;
	listNode* preview=NULL;
	if (h->first == NULL)
		return 0;
	while (next != NULL) {
		middle = next;
		next = next->link;
		middle->link = preview;
		preview = middle;
		if (next == NULL) {
			h->first = preview;
		}

	}
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

