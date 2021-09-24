#include<stdio.h>
#define MAX 20;
typedef struct Order {
	struct MList* head;
	int candle_num;
	int spoon_num;
}Order;
typedef struct MList {
	char menu_name[MAX];
	char icecream[MAX];
	char HP_icecream[6][MAX];
	int num;
	struct MList* link;
}MList;

void Ordering() {
	Order* order = (Order*)malloc(sizeof(Order));
	if(!order)
		MemoryError();
	init_Order(order);
	int type = 0;
	while (1) {
		type = Show_MenuType();
		MenuList(order, type);
		printf("1. 결제하기\n2. 더 주문하기\n");
		scanf_s("%d", &type);
		if (type == 1) {
			//만약 handpack이나 아이스크림케이크를 주문했을 경우, 집가는 시간이나 원하는 숟가락 개수, 아이스크림 케이크인경우 촛불개수 입력받기
			//계산하기
			break;
		}
	}
}
void MemoryError() {
	printf("memory assignment error");
	exit(1);
}
void init_Order(Order* order) {
	order->candle_num = 0;
	order->spoon_num = 0;
	order->head = NULL;
}

int Show_MenuType() {
	printf("원하는 항목을 선택하세요.\n");
	for (int type = 0; ;) {
		printf("***********************\n");
		printf("    1. IceCream\n");
		printf("    2. IceCreamCake\n");
		printf("    3. Beverage\n");
		printf("    4. Coffee\n");
		printf("***********************\n");
		scanf_s("%d", &type);
		if (type < 1 || type>4) {
			printf("1~4번 항목사이에서 골라주세요.\n");
			continue;
		}
		return type;
	}
}

void MenuList(Order* order, int type) {
	int IC_type = 0;
	switch (type) {
	case 1:
		IC_type = IcecreamList();
		IC_select(order, IC_type);
		break;
	case 2:
		IcecreamCakeList();
		else_select(order);
		break;
	case 3:
		BeverageList();
		else_select(order);
		break;
	case 4:
		CoffeeList();
		else_select(order);
		break;
	}
	return;
}
void store(Order* order,Mlist* node){
	if (order->head == NULL) {
		node->link = NULL;
		order->head = node;
	}
	else {
		node->link = order->head;
		order->head = node;
	}
}
int IcecreamList() {
	int type = 0, Con_type = 0, HP_type = 0, _num = 0;
	MList* node = (MList*)malloc(sizeof(MList));
	if (!node)
		MemoryError();

	printf("원하는 항목을 선택하세요.\n");
	for (; ;) {													// Con&Cup과 HandPack중 하나 선택
		printf("***********************\n");
		printf("    1. Con & Cup\n");
		printf("    2. HandPack\n");
		printf("***********************\n");
		scanf_s("%d", &type);
		if (type < 1 || type>2) {
			printf("1~4번 항목사이에서 골라주세요.\n");
			continue;
		}
		break;
	}

	printf("원하는 사이즈를 선택하세요.\n");
	if (type == 1) {
		for (; ;) {
			printf("-----------------------\n");
			printf("    1. 싱글레귤러\n");
			printf("    2. 싱글킹\n");
			printf("    3. 더블주니어\n");
			printf("    4. 더블레귤러\n");
			printf("-----------------------\n");
			scanf_s("%d", &Con_type);
			if (type < 1 || type>4) {
				printf("1~4번 항목사이에서 골라주세요.\n");
				continue;
			}
			break;
		}
		printf("몇개를 구매하실 건가요?\n");
		while () {
			scanf_s("%d", _num);								// 주문은 한개이상
			if (_num <= 0) {
				printf("한개이상 주문해주세요.\n");
				continue;
			}
			break;
		}
		switch (Con_type) {
		case 1:
			strcpy(node->menu_name, "싱글레귤러");
			node->num = _num;
			break;
		case 2:
			strcpy(node->menu_name, "싱글킹");
			node->num = _num;
			break;
		case 3:
			strcpy(node->menu_name, "더블주니어");
			node->num = _num;
			break;
		case 4:
			strcpy(node->menu_name, "더블레귤러");
			node->num = _num;
			break;
		}
		return 1;
	}
	else {
		printf("-----------------------\n");
		printf("    1. 파인트\n");
		printf("    2. 쿼터\n");
		printf("    3. 패밀리\n");
		printf("    4. 하프갤런\n");
		printf("-----------------------\n");
		return 2;
	}
	//아이스크림 리스트 나열
}

void IcecreamCakeList() {
	printf("원하는 메뉴를 선택하세요.\n");
	//아이스크림 케이크 리스트 나열
}

void BeverageList() {
	printf("원하는 메뉴를 선택하세요.\n");
	//음료수 리스트 나열
}

void CoffeeList() {
	printf("원하는 메뉴를 선택하세요.\n");
	//커피 리스트 나열
}
Order* IC_select(Order* order, int type) {
	if (type == 1) {

	}
	else {

	}
}
Order* else_select(Order* order) {
	int _num = 0;
	char name[MAX];
	int menu = 0, type = 0, spoon_num = 0, candle_num = 0;

	//만약 메뉴가 handpack인 경우 개수를 받지 않고 아이스크림만 주문받기 
	scanf_s("%d", &menu);
	MList* node = (MList*)malloc(sizeof(MList));		// 주문들을 연결리스트(스택)로 저장하기
	if (!node)
		MemoryError();
	//원하는 항목을 탐색하서 찾고 메뉴이름과 개수를 저장
	printf("원하는 개수를 입력하십시오.\n");
	scanf_s("%d", &_num);

	strcpy(node->menu_name, name);
	node->num = _num;
	if (order->head == NULL) {
		node->link = NULL;
		order->head = node;
	}
	else {
		node->link = order->head;
		order->head = node;
	}

	printf("1. 결제하기\n2. 더 주문하기\n");
	scanf_s("%d", &type);
	if (type == 1) {
		//만약 handpack이나 아이스크림케이크를 주문했을 경우, 집가는 시간이나 원하는 숟가락 개수, 아이스크림 케이크인경우 촛불개수 입력받기
		//계산하기
	}
	else 
		return;
}

int main() {
	Show_MenuType();
}
