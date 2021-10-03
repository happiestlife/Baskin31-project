#include<stdio.h>
#define MAX 20

typedef struct IcecreamNode {		// 아이스크림 종류
	int ic_num; // 번호	
	char name[30]; // 제품명
	int kcal; // 열량(kcal)
	int prefer; // 제품선호도값
	struct IcecreamNode* link; // 다음 노드의 주소를 저장할 포인터 
}IcecreamNode;

typedef struct IcecreamConeNode {	// 콘 종류
	int con_num; // 번호
	char ctype[30]; // 콘종류
	int cserving; // 제공량(g)
	int cprice; // 가격(\)
	struct IcecreamConeNode* link;
}IcecreamConeNode;

typedef struct HandPackNode {		// hadnpack 종류
	int hp_num; // 번호
	char htype[30]; // 컵종류
	int hserving; // 제공량(g)
	int hprice; // 가격(\)
	struct HandPackNode* link;
}HandPackNode;

typedef struct BeverageNode {		// 음료수 종류
	int bv_num;
	char name[32];
	int kcal;
	int prefer;
	struct BeverageNode* link;
}BeverageNode;

typedef struct BeveragePriceNode {	// 음료수 가격 정보
	int con_num;
	char ctype[30];
	int cserving;
	int cprice;
	struct BaverageConeNode* link;
}BeveragePriceNode;

typedef struct Order {				// 총주문내역
	struct MList* head;
	int candle_num;
	int spoon_num;
}Order;

typedef struct MList {				// 개별주문내역
	char menu_name[MAX];
	char icecream[6][MAX];
	int num; int hp;
	struct MList* link;
}MList;

typedef struct All_InfoHead {
	//아이스크림 케이크, 커피, 음료수 파일열어 연결리스트를 만들면 그 head를 가르킨다.
}InfoHead;
typedef struct menu_info {
	IcecreamNode* icecream_link;
	BeverageNode*
};
void Ordering(InfoHead* info_head);
void MemoryError(char* message);
void init_Order(Order* order);
int Show_MenuType();
void MenuList(Order** porder, InfoHead* info_head, int type);
void store(Order** order, MList* node);
void IcecreamType(Order** porder, IcecreamNode* Icecream_info);
void IcecreamList(IcecreamNode* Icecream_info);
void IcecreamCakeList();
void BeverageList();
void CoffeeList();
void select_ConandCup(Order** porder, IcecreamNode* Icecream_info, char* icecreamtype_name, int num);
void select_Handpack(Order** porder, IcecreamNode* Icecream_info, char* icecreamtype_name, int num);
void select_else(Order** porder);
void show(Order* order);
void Cal(Order* order);
IcecreamNode* makeNode();
void print_ic(IcecreamNode* head);
IcecreamNode* loadTxt();
InfoHead* uploade();

void Ordering(InfoHead* info_head) {
	Order* order = (Order*)malloc(sizeof(Order));
	if (!order)
		MemoryError("memory assignment error");
	init_Order(order);
	int type = 0, type2 = 0;
	while (1) {
		type = Show_MenuType();
		MenuList(&order, info_head, type);	//메뉴보고 원하는 항목 선택하기
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
	Cal(order);
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

void MemoryError(char* message) {
	printf("%s", message);
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

void MenuList(Order** porder, InfoHead* info_head, int type) {
	int IC_type = 0;
	switch (type) {
	case 1:
		IcecreamType(porder, info_head->icecream_link);
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
void connect(IcecreamNode** phead, IcecreamNode* newnode) // 연결리스트 연결
{
	// phead가 참조하는 객체 = head 노드

	if (*phead == NULL)
		*phead = newnode; // head노드가 참조하고 있는 객체는 newnode가 참조하고 있는 객체로 바꾸기
	else {
		newnode->link = *phead;
		*phead = newnode;
	}
}
void show(Order* order) {
	printf("~~~~~~~~~~~~~~~~~~~~주문내역~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (MList* i = order->head; i != NULL; i = i->link) {
		if (i->num > 1) {
			printf("메뉴 : %s, 수량 : 1개\n※아이스크림 종류\n", i->menu_name);
			for (int j = 0; j < i->num; j++)
				printf("%d. %s\n", j + 1, i->icecream[j]);
		}
		else
			printf("메뉴 : %s, 아이스크림 종류 : %s\n", i->menu_name, i->icecream[0]);
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void IcecreamType(Order** porder, IcecreamNode* Icecream_info) {
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
		else if (Con_type == 3)	strcpy(icecreamtype_name, "더블주니어");
		else strcpy(icecreamtype_name, "더블레귤러");

		select_ConandCup(porder, Icecream_info, icecreamtype_name, _num);
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

		select_Handpack(porder, Icecream_info, icecreamtype_name, _num);
	}
}

void IcecreamList(IcecreamNode* Icecream_info) {
	printf("-----------------------------\n");
	print_ic(Icecream_info);
}

void IcecreamCakeList() {
	printf("원하는 메뉴를 선택하세요.\n");
	//아이스크림 케이크 리스트 나열
}

void BeverageList() {
	printf("원하는 메뉴를 선택하세요.\n");
	//음료수 리스트 나열
}

void DessertList() {
	printf("원하는 메뉴를 선택하세요.\n");
	//커피 리스트 나열
}

char* search(IcecreamNode* Icecream_info, int menu_num) {
	for (IcecreamNode* i = Icecream_info; i != NULL; i = i->link) {
		if (i->ic_num == menu_num)
			return i->name;
	}
	return NULL;
}

void select_ConandCup(Order** porder, IcecreamNode* Icecream_info, char* icecreamtype_name, int num) {
	int icecream_num = 0;
	char* name = NULL;
	for (int i = 0; i < num; i++) {
		MList* node = (MList*)malloc(sizeof(MList));
		if (!node)
			MemoryError("memory assignment error");

		strcpy(node->menu_name, icecreamtype_name);
		node->num = 1;
		printf("원하는 아이스크림 항목의 번호를 입력하세요.\n");
		IcecreamList(Icecream_info);

		while (1) {
			printf("=> ");
			scanf_s("%d", &icecream_num);
			name = search(Icecream_info, icecream_num);
			if (icecream_num < 0 || !name) {
				printf("리스트 안에서 주문해주세요.");
				continue;
			}
			break;
		}
		printf("\n");
		strcpy(node->icecream[i], name);
		store(porder, node);
	}
}
void select_Handpack(Order** porder, IcecreamNode* Icecream_info, char* icecreamtype_name, int num) {
	int icecream_num = 0;
	char* name = NULL;
	MList* node = (MList*)malloc(sizeof(MList));
	if (!node)
		MemoryError("memory assignment error");
	node->num = num;
	(*porder)->spoon_num = -1;
	strcpy(node->menu_name, icecreamtype_name);

	for (int i = 0; i < num; i++) {
		printf("%d개의 맛을 선택하세요.\n", num);
		IcecreamList(Icecream_info);
		while (1) {
			printf("=> ");
			scanf_s("%d", &icecream_num);
			name = search(Icecream_info, icecream_num);
			if (icecream_num < 0 || !name) {
				printf("리스트 안에서 주문해주세요.");
				continue;
			}
			break;
		}
		strcpy(node->icecream[i], name);
	}
	printf("\n");
	store(porder, node);
}

void select_else(Order** porder) {
	int num;
	char* name = NULL;
	MList* node = (MList*)malloc(sizeof(MList));		// 주문들을 연결리스트(스택)로 저장하기
	if (!node)
		MemoryError("memory assignment error");
	//원하는 항목을 탐색하서 찾고 메뉴이름과 개수를 저장

	printf("원하는 개수를 입력하십시오.\n");
	num = input();

	strcpy(node->menu_name, name);
	node->num = num;

	store(porder, node);
}
/*
void Cal(Order* order)
{
	int total_price = 0;
	for (MList* i = order->head; i != NULL; i = i->link) { // 메뉴 이름에 따라 가격 계산
		if (strcmp(i->menu_name, "싱글레귤러") == 0) total_price += 3200;
		else if (strcmp(i->menu_name, "싱글킹") == 0) total_price += 4000;
		else if (strcmp(i->menu_name, "더블주니어") == 0) total_price += 4300;
		else if (strcmp(i->menu_name, "더블레귤러") == 0) total_price += 6200;
		else if (strcmp(i->menu_name, "파인트") == 0) total_price += 8200;
		else if (strcmp(i->menu_name, "쿼터") == 0) total_price += 15500;
		else if (strcmp(i->menu_name, "패밀리") == 0) total_price += 22000;
		else if (strcmp(i->menu_name, "하프갤런") == 0) total_price += 26500;
	}
	// 멤버십 여부에 따라 파인트 30% 할인
	int membership;
	printf("KT 멤버십 고객이시라면 파인트를 30%%\ 할인해드립니다. KT 멤버식 고객이신가요?\n");
	printf("(예 : 1, 아니오 : 0) : ");
	scanf_s("%d", &membership);
	if (membership == 1) {
		for (MList* i = order->head; i != NULL; i = i->link) {
			if (strcmp(i->menu_name, "파인트") == 0) total_price -= 2500;
		}
	}
	printf("총 가격은 %d 원 입니다. 베스킨라빈스를 찾아주셔서 감사합니다!\n", total_price);
	printf("---------------------------------------------------------------\n");
	exit(1);
}*/

IcecreamNode* loadTxt() {
	IcecreamNode* head = NULL;

	FILE* fp = fopen("icecream_info.txt", "r");
	if (!fp)
		MemoryError("File open error\n");
	while (!feof(fp))// 파일 끝까지 읽을 동안 (끝에 도달한 경우 0 반환)
	{
		IcecreamNode* newnode = makeNode();
		fscanf(fp, "%d %s %d %d \n", &(newnode->ic_num), newnode->name, &(newnode->kcal), &(newnode->prefer));
		connect(&head, newnode);
	}
	return head;
}

void print_ic(IcecreamNode* head) {
	IcecreamNode* curr = head;
	while (curr != NULL) {
		printf("%d %s %d %d\n", curr->ic_num, curr->name, curr->kcal, curr->prefer);
		curr = curr->link;
	}
}

IcecreamNode* makeNode() {
	IcecreamNode* tmp = (IcecreamNode*)malloc(sizeof(IcecreamNode));
	if (!tmp)
		MemoryError("memory assignment error\n");
	tmp->link = NULL;
	return tmp;
}

InfoHead* uploade() {
	InfoHead* info_head = (InfoHead*)malloc(sizeof(info_head));
	if (!info_head)
		MemoryError("memory assignment error\n");
	IcecreamNode* Icecream_info = loadTxt();
	//나머지 항목들의 파일 불러오기

	info_head->icecream_link = Icecream_info;
	//나머지 링크 걸어주기

	return info_head;
}
int main() {
	InfoHead* info_head = uploade();
	Ordering(info_head);
}