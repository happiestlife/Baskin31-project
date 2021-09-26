#include<stdio.h>
#define MAX 20
typedef struct Order {
	struct MList* head;
	int candle_num;
	int spoon_num;
}Order;
typedef struct MList {
	char menu_name[MAX];
	char icecream[6][MAX];
	int num; int hp;
	struct MList* link;
}MList;

void Ordering();
void MemoryError();
void init_Order(Order* order);
int Show_MenuType();
void MenuList(Order** porder, int type);
void store(Order** order, MList* node);
void IcecreamType(Order** porder);
void IcecreamList();
void IcecreamCakeList();
void BeverageList();
void CoffeeList();
void select_ConandCup(Order** porder, char* icecreamtype_name, int num);
void select_Handpack(Order** porder, char* icecreamtype_name, int num);
void select_else(Order** porder);
void show(Order* order);

void Ordering() {
	Order* order = (Order*)malloc(sizeof(Order));
	if (!order)
		MemoryError();
	init_Order(order);
	int type = 0, type2 = 0;
	while (1) {
		type = Show_MenuType();
		MenuList(&order, type);	//메뉴보고 원하는 항목 선택하기
		show(order);	// 주문내역보기
		printf("\n***********************\n1. 결제하기\n2. 더 주문하기\n***********************\n");
		scanf_s("%d", &type2);
		if (type2 == 1) {
			if (order->spoon_num == -1) {
				printf("원하는 숟가락 개수를 입력하세요.\n");
				order->spoon_num = input();
				if (order->candle_num == -1) {
					printf("원하는 초의 수를 입력하세요.\n");
					order->candle_num = input();
				}
			}
			break;
		}
	}
	//계산하기
}

int input() {
	int num = 0;
	while (1) {
		scanf_s("%d", &num);
		if (num <= 0) {
			printf("한개이상 주문해주세요.\n");
			continue;
		}
		break;
	}
	return num;
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

void MenuList(Order** porder, int type) {
	int IC_type = 0;
	switch (type) {
	case 1:
		IcecreamType(porder);
		break;
	case 2:
		IcecreamCakeList();
		select_else(porder);
		break;
	case 3:
		BeverageList();
		select_else(porder);
		break;
	case 4:
		CoffeeList();
		select_else(porder);
		break;
	}
	return;
}

void store(Order** order, MList* node) {
	if ((*order)->head == NULL) {
		node->link = NULL;
		(*order)->head = node;
	}
	else {
		node->link = (*order)->head;
		(*order)->head = node;
	}
}

void show(Order* order) {
	printf("~~~~~~~~~주문내역~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (MList* i = order->head; i != NULL; i = i->link) {
		if (i->hp == 1) {
			printf("메뉴 : %s, 수량 : 1개\n아이스크림 종류\n", i->menu_name);
			for (int j = 0; j < i->num; j++)
				printf("%d. %s\n", j + 1, i->icecream[j]);
		}
		else
			printf("메뉴 : %s, 아이스크림 종류 : %s 수량 : %d개\n", i->menu_name, i->icecream[0], i->num);
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void IcecreamType(Order** porder) {
	int type = 0, Con_type = 0, Handpack_type = 0, _num = 0;
	char icecreamtype_name[MAX];
	printf("원하는 항목을 선택하세요.\n");
	while (1) {													// Con&Cup과 HandPack중 하나 선택
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
		while (1) {
			printf("-----------------------\n");
			printf("    1. 싱글레귤러\n");
			printf("    2. 싱글킹\n");
			printf("    3. 더블주니어\n");
			printf("    4. 더블레귤러\n");
			printf("-----------------------\n");
			scanf_s("%d", &Con_type);
			if (Con_type < 1 || Con_type>4) {
				printf("1~4번 항목사이에서 골라주세요.\n\n");
				continue;
			}
			break;
		}

		printf("몇개를 구매하실 건가요?\n");
		_num = input();

		if (Con_type == 1) strcpy(icecreamtype_name, "싱글레귤러");
		else if (Con_type == 2) strcpy(icecreamtype_name, "싱글킹");
		else if (Con_type == 2)	strcpy(icecreamtype_name, "더블주니어");
		else strcpy(icecreamtype_name, "더블레귤러");

		select_ConandCup(porder, icecreamtype_name, _num);
	}
	else {
		while (1) {
			printf("-----------------------\n");
			printf("    1. 파인트\n");
			printf("    2. 쿼터\n");
			printf("    3. 패밀리\n");
			printf("    4. 하프갤런\n");
			printf("-----------------------\n");
			scanf_s("%d", &Handpack_type);
			if (Handpack_type < 1 || Handpack_type>4) {
				printf("1~4번 항목사이에서 골라주세요.\n\n");
				continue;
			}
			break;
		}
		if (Handpack_type == 1) {
			strcpy(icecreamtype_name, "파인트");
			_num = 3;
		}
		else if (Handpack_type == 2) {
			strcpy(icecreamtype_name, "쿼터");
			_num = 4;
		}
		else if (Handpack_type == 3) {
			strcpy(icecreamtype_name, "패밀리");
			_num = 5;
		}
		else {
			strcpy(icecreamtype_name, "하프갤런");
			_num = 6;
		}

		select_Handpack(porder, icecreamtype_name, _num);
	}
}

void IcecreamList() {

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

void select_ConandCup(Order** porder, char* icecreamtype_name, int num) {
	int icecream_num = 0;
	for (int i = 0; i < num; i++) {
		MList* node = (MList*)malloc(sizeof(MList));
		if (!node)
			MemoryError();
		strcpy(node->menu_name, icecreamtype_name);
		node->num = 1;
		printf("원하는 아이스크림 항목의 번호를 입력하세요.\n");
		IcecreamList();

		while (1) {
			scanf_s("%d", &icecream_num);
			if (icecream_num < 0) {
				printf("리스트 안에서 주문해주세요.");
				continue;
			}
			break;
		}
		//파일에서 num을 검색하여 맞는 항목의 이름을 넣는다.
		//strcpy(head->icecream[i], --);

		store(porder, node);
	}
}
void select_Handpack(Order** porder, char* icecreamtype_name, int num) {
	int icecream_num = 0;
	MList* node = (MList*)malloc(sizeof(MList));
	if (!node)
		MemoryError();
	node->hp = 1;
	node->num = num;
	(*porder)->spoon_num = -1;
	strcpy(node->menu_name, icecreamtype_name);
	printf("%d개의 맛을 선택하세요.\n", num);
	for (int i = 0; i < num;) {
		IcecreamCakeList();
		while (1) {
			scanf_s("%d", &icecream_num);
			if (icecream_num < 0) {
				printf("리스트 안에서 주문해주세요.");
				continue;
			}
			break;
		}
		//파일에서 num을 검색하여 맞는 항목의 이름을 넣는다.
		//strcpy(node->icecream[i], --);
		i++;
		printf("%d개 남았습니다.\n\n", num - i);
	}
	store(porder, node);
}

void select_else(Order** porder) {
	int num;
	char* name = NULL;
	MList* node = (MList*)malloc(sizeof(MList));		// 주문들을 연결리스트(스택)로 저장하기
	if (!node)
		MemoryError();
	//원하는 항목을 탐색하서 찾고 메뉴이름과 개수를 저장

	printf("원하는 개수를 입력하십시오.\n");
	num = input();

	strcpy(node->menu_name, name);
	node->num = num;

	store(porder, node);
}

int main() {
	//Show_MenuType();
	Ordering();
}
