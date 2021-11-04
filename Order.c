#include<stdio.h>
#pragma warning(disable : 4996)
#define MAX 30

typedef struct IcecreamNode {
	int ic_num; // 번호
	char name[MAX]; // 제품명
	int kcal; // 열량(kcal)
	int prefer; // 제품선호도값
	struct IcecreamNode* link; // 다음 노드의 주소를 저장할 포인터 
}IcecreamNode;

typedef struct IcecreamConeNode {
	int con_num; // 번호
	char ctype[MAX]; // 콘종류
	int cserving; // 제공량(g)
	int cprice; // 가격(\)
	struct IcecreamConeNode* link;
}IcecreamConeNode;

typedef struct HandPackNode {
	int hp_num; // 번호
	char htype[MAX]; // 컵종류
	int hserving; // 제공량(g)
	int hprice; // 가격(\)
	struct HandPackNode* link;
}HandPackNode;

typedef struct BeverageNode {
	int bv_num;
	char bvtype[MAX];
	int bvserving;
	int kcal;
	int bvprice;
	int prefer;
	struct BeverageNode* link;
}BeverageNode;

typedef struct InfoHead {
	IcecreamNode* icecream_link;
	IcecreamConeNode* icecreamcone_link;
	HandPackNode* handpack_link;
	BeverageNode* beverage_link;
}InfoHead;

typedef struct Order {			// 주문 리스트
	struct MList* head;
	int spoon_num;
}Order;

typedef struct MList {
	char menu_name[MAX];
	char icecream[6][MAX];
	int num;
	int type;
	struct MList* link;
}MList;

void Ordering(InfoHead* info_head);
void MemoryError(char* message);
void init_Order(Order* order);
int Show_MenuType();
void MenuList(Order** porder, InfoHead* info_head, int type);
void store(Order** order, MList* node);
void IcecreamType(Order** porder, IcecreamNode* Icecream_info);
void IcecreamList(IcecreamNode* Icecream_info);
void BeverageList(BeverageNode* beverage_head);
void select_ConandCup(Order** porder, IcecreamNode* Icecream_info, char* icecreamtype_name, int num);
void select_Handpack(Order** porder, IcecreamNode* Icecream_info, char* icecreamtype_name, int num);
void select_beverage(Order** porder, BeverageNode* beverage_info);
void show(Order* order);
void Cal(Order* order, InfoHead* InfoHead);
IcecreamNode* makeNode_ice();
BeverageNode* makeNode_bv();
void delete_bv_menu(BeverageNode** phead, BeverageNode* remove);
BeverageNode* add_bv_menu(BeverageNode** phead);
IcecreamNode* add_icecream_menu(IcecreamNode** phead);
void delete_icecream_menu(IcecreamNode** phead, IcecreamNode* remove);
HandPackNode* makeNode_hp();
IcecreamConeNode* makeNode_con();
void Cal(Order* order, InfoHead* InfoHead);

void print_ic(IcecreamNode* head);
InfoHead* loadTxt();
void saveTxt(InfoHead* info_head);
void print_bv(BeverageNode* head);

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
			}
			break;
		}
	}
	//계산하기
	Cal(order, info_head);
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
	order->spoon_num = 0;
	order->head = NULL;
}

int Show_MenuType() {
	printf("원하는 항목을 선택하세요.\n");
	for (int type = 0; ;) {
		printf("***********************\n");
		printf("    1. IceCream\n");
		printf("    2. Beverage\n");
		printf("***********************\n");
		scanf_s("%d", &type);
		if (type < 1 || type>2) {
			printf("1~2번 항목사이에서 골라주세요.\n");
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
		select_beverage(porder, info_head->beverage_link);
		break;
	}
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
		if (i->num > 1) {
			printf("* 메뉴 : %s, 수량 : 1개\n아이스크림 종류\n", i->menu_name);
			for (int j = 0; j < i->num; j++)
				printf("%d. %s\n", j + 1, i->icecream[j]);
		}
		else if (strcmp(i->icecream[0], "no") == 0)
			printf("* 메뉴 : %s, 수량 : 1개\n", i->menu_name);
		else
			printf("* 메뉴 : %s, 아이스크림 종류 : %s, 수량 : %d개\n", i->menu_name, i->icecream[0], i->num);
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
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

char* search_ic_with_num(IcecreamNode* Icecream_info, int menu_num) {
	for (IcecreamNode* i = Icecream_info; i != NULL; i = i->link) {
		if (i->ic_num == menu_num)
			return i->name;
	}
	return NULL;
}

IcecreamNode* search_ic_with_name(IcecreamNode* phead) // 이름 검색
{
	IcecreamNode* p = phead;

	char n[30];
	printf("** 검색할 아이스크림의 이름을 입력해주세요 **\n");
	scanf_s("%s", n, sizeof(n));

	while (p != NULL)
	{
		if (strcmp(p->name, n) == 0)
			break;

		p = p->link; // 다음 노드로 이동

		if (p == NULL)
			printf("\n검색한 아이스크림 정보가 존재하지 않습니다\n\n");
	}
	return p; // 검색할 아이스크림의 이름을 가진 노드 주소값 반환
}

char* search_bv_with_num(BeverageNode* beverage_info, int menu_num) {
	for (BeverageNode* i = beverage_info; i != NULL; i = i->link) {
		if (i->bv_num == menu_num)
			return i->bvtype;
	}
	return NULL;
}

BeverageNode* search_bv_with_name(BeverageNode* phead) // 이름 검색
{
	BeverageNode* p = phead;

	char n[30];
	printf("** 검색할 음료의 이름을 입력해주세요 **\n");
	scanf_s("%s", n, sizeof(n));

	while (p != NULL)
	{
		if (strcmp(p->bvtype, n) == 0)
			break;

		p = p->link; // 다음 노드로 이동

		if (p == NULL)
			printf("\n검색한 아이스크림 정보가 존재하지 않습니다\n\n");
	}
	return p; // 검색할 아이스크림의 이름을 가진 노드 주소값 반환
}

void select_ConandCup(Order** porder, IcecreamNode* Icecream_info, char* icecreamtype_name, int num) {
	int icecream_num = 0;
	char* name;
	for (int i = 0; i < num; i++) {
		MList* node = (MList*)malloc(sizeof(MList));
		if (!node)
			MemoryError("memory assignment error");

		node->num = 1;
		node->type = 1;
		strcpy(node->menu_name, icecreamtype_name);
		printf("원하는 아이스크림 항목의 번호를 입력하세요.\n");
		print_ic(Icecream_info);

		while (1) {
			printf("=> ");
			scanf_s("%d", &icecream_num);
			name = search_ic_with_num(Icecream_info, icecream_num);
			if (icecream_num < 0 || !name) {
				printf("리스트 안에서 주문해주세요.");
				continue;
			}
			break;
		}
		strcpy(node->icecream[0], name);
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
	node->type = 2;
	(*porder)->spoon_num = -1;
	strcpy(node->menu_name, icecreamtype_name);

	for (int i = 0; i < num;) {
		print_ic(Icecream_info);
		printf("%d개의 맛을 선택하세요.\n", num - i);
		while (1) {
			printf("=> ");
			scanf_s("%d", &icecream_num);
			name = search_ic_with_num(Icecream_info, icecream_num);
			if (icecream_num < 0 || !name) {
				printf("리스트 안에서 주문해주세요.");
				continue;
			}
			break;
		}
		strcpy(node->icecream[i++], name);
	}
	printf("\n");
	store(porder, node);
}

void select_beverage(Order** porder, BeverageNode* beverage_info) {
	int num;
	int beverage_num;
	char* name = NULL;

	printf("원하는 개수를 입력하십시오.\n");
	num = input();

	for (int i = 0; i < num; i++) {
		MList* node = (MList*)malloc(sizeof(MList));
		if (!node)
			MemoryError("memory assignment error");

		node->num = 1;
		node->type = 3;
		strcpy(node->icecream[0], "no");
		printf("원하는 음료 항목의 번호를 입력하세요.\n");
		print_bv(beverage_info);

		while (1) {
			printf("=> ");
			scanf_s("%d", &beverage_num);
			name = search_bv_with_num(beverage_info, beverage_num);
			if (beverage_num < 0 || !name) {
				printf("리스트 안에서 주문해주세요.");
				continue;
			}
			break;
		}
		printf("name : %s\n", name);
		strcpy(node->menu_name, name);
		store(porder, node);
	}
}

InfoHead* loadTxt() {
	InfoHead* info_head = (InfoHead*)malloc(sizeof(info_head));
	if (!info_head)
		MemoryError("memory assignment error\n");
	IcecreamNode* icecream_head = NULL, * icecream_rear = NULL;
	IcecreamConeNode* icecreamcone_head = NULL, * icecreamcone_rear = NULL;
	HandPackNode* handpack_head = NULL, * handpack_rear = NULL;
	BeverageNode* beverage_head = NULL, * beverage_rear = NULL;

	FILE* fp = fopen("icecream_info.txt", "r");
	if (!fp)
		MemoryError("File open error\n");
	while (!feof(fp))// 파일 끝까지 읽을 동안 (끝에 도달한 경우 0 반환)
	{
		IcecreamNode* newnode = makeNode_ice();
		fscanf(fp, "%d %s %d %d", &(newnode->ic_num), newnode->name, &(newnode->kcal), &(newnode->prefer));
		if (icecream_head == NULL) {
			icecream_head = newnode;
			icecream_rear = newnode;
			newnode->link = NULL;
		}
		else {
			icecream_rear->link = newnode;
			newnode->link = NULL;
			icecream_rear = newnode;
		}
	}
	fclose(fp);

	FILE* fp1 = fopen("icecreamCone_info.txt", "r");
	if (!fp1)
		MemoryError("File open error\n");
	while (!feof(fp1))// 파일 끝까지 읽을 동안 (끝에 도달한 경우 0 반환)
	{
		IcecreamConeNode* newnode = makeNode_con();
		fscanf(fp1, "%d %s %d %d", &(newnode->con_num), newnode->ctype, &(newnode->cserving), &(newnode->cprice));
		if (icecreamcone_head == NULL) {
			icecreamcone_head = newnode;
			handpack_rear = newnode;
			newnode->link = NULL;
		}
		else {
			handpack_rear->link = newnode;
			newnode->link = NULL;
			handpack_rear = newnode;
		}
	}
	fclose(fp1);

	FILE* fp2 = fopen("HandPack_info.txt", "r");
	if (!fp2)
		MemoryError("File open error\n");
	while (!feof(fp2))// 파일 끝까지 읽을 동안 (끝에 도달한 경우 0 반환)
	{
		HandPackNode* newnode = makeNode_hp();
		fscanf(fp2, "%d %s %d %d", &(newnode->hp_num), newnode->htype, &(newnode->hserving), &(newnode->hprice));
		if (handpack_head == NULL) {
			handpack_head = newnode;
			handpack_rear = newnode;
			newnode->link = NULL;
		}
		else {
			handpack_rear->link = newnode;
			newnode->link = NULL;
			handpack_rear = newnode;
		}
	}
	fclose(fp2);

	FILE* fp3 = fopen("beverage_info.txt", "r");
	if (!fp3)
		MemoryError("File open error\n");
	while (!feof(fp3))// 파일 끝까지 읽을 동안 (끝에 도달한 경우 0 반환)
	{
		BeverageNode* newnode = makeNode_bv();
		fscanf(fp3, "%d %s %d %d %d %d", &(newnode->bv_num), newnode->bvtype, &(newnode->bvserving), &(newnode->kcal), &(newnode->bvprice), &(newnode->prefer));
		if (beverage_head == NULL) {
			beverage_head = newnode;
			beverage_rear = newnode;
			newnode->link = NULL;
		}
		else {
			beverage_rear->link = newnode;
			newnode->link = NULL;
			beverage_rear = newnode;
		}
	}
	fclose(fp3);

	info_head->icecream_link = icecream_head;
	info_head->icecreamcone_link = icecreamcone_head;
	info_head->handpack_link = handpack_head;
	info_head->beverage_link = beverage_head;

	return info_head;
}

void delete_icecream_menu(IcecreamNode** phead, IcecreamNode* remove) // 이름 검색해서 정보 삭제하기
{
	IcecreamNode* s = *phead;
	IcecreamNode* p = NULL;

	if (s == NULL) {
		printf("icecream메뉴가 존재하지 않습니다. \n");
		return;
	}
	else {
		while (s != NULL) {
			if (s == remove) {
				p->link = remove->link;
				free(remove);
				break;
			}
			p = s;
			s = s->link;
		}

		while (1)
		{
			p = p->link;
			if (!p)
				break;
			--(p->ic_num);
		}
	}
}

IcecreamNode* add_icecream_menu(IcecreamNode** phead)
{
	IcecreamNode* p = (IcecreamNode*)malloc(sizeof(IcecreamNode));
	if (!p)
		MemoryError("memory assignment error");
	IcecreamNode* pre = NULL;
	IcecreamNode* front = *phead;
	IcecreamNode* rear = *phead;

	printf("** 추가할 아이스크림의 제품명, 열량, 제품선호도값을 입력해주세요 **\n");
	fscanf(stdin, "%s %d %d", (p->name), &(p->kcal), &(p->prefer));

	while (rear != NULL)
	{
		pre = rear;
		rear = rear->link; // 다음 노드로 이동

		if (rear == NULL)
		{
			pre->link = p;
			p->link = NULL;
			p->ic_num = pre->ic_num + 1;
		}
	}
	return front;
}

BeverageNode* add_bv_menu(BeverageNode** phead)
{
	BeverageNode* p = (BeverageNode*)malloc(sizeof(BeverageNode));
	if (!p)
		MemoryError("memory assignment error");
	BeverageNode* pre = NULL;
	BeverageNode* front = *phead;
	BeverageNode* rear = *phead;

	printf("** 추가할 음료수의 제품명, 제공량, 열량, 가격, 제품선호도값을 입력해주세요 **\n");
	fscanf(stdin, "%s %d %d %d %d", (p->bvtype), &(p->bvserving), &(p->kcal), &(p->bvprice), &(p->prefer));
	while (rear != NULL)
	{
		pre = rear;
		rear = rear->link;

		if (rear == NULL)
		{
			pre->link = p;
			p->link = NULL;
			p->bv_num = pre->bv_num + 1;
		}
	}

	return front;
}

void delete_bv_menu(BeverageNode** phead, BeverageNode* remove)
{
	BeverageNode* s = *phead;
	BeverageNode* p = NULL;
	print_bv(*phead);
	if (s == NULL) {
		printf("icecream메뉴가 존재하지 않습니다. \n");
		return;
	}
	else
	{
		while (s != NULL) {
			if (s == remove) {
				p->link = remove->link;
				free(remove);
				break;
			}
			p = s;
			s = s->link;
		}

		while (1)
		{
			p = p->link;
			if (!p)
				break;
			--(p->bv_num);
		}
	}
}

IcecreamNode* makeNode_ice() {
	IcecreamNode* tmp = (IcecreamNode*)malloc(sizeof(IcecreamNode));
	if (!tmp)
		MemoryError("memory assignment error\n");
	tmp->link = NULL;
	return tmp;
}

IcecreamConeNode* makeNode_con() {
	IcecreamConeNode* tmp = (IcecreamConeNode*)malloc(sizeof(IcecreamConeNode));
	if (!tmp)
		MemoryError("memory assignment error\n");
	tmp->link = NULL;
	return tmp;
}

HandPackNode* makeNode_hp() {
	HandPackNode* tmp = (HandPackNode*)malloc(sizeof(HandPackNode));
	if (!tmp)
		MemoryError("memory assignment error\n");
	tmp->link = NULL;
	return tmp;
}

BeverageNode* makeNode_bv() {
	BeverageNode* tmp = (BeverageNode*)malloc(sizeof(BeverageNode));
	if (!tmp)
		MemoryError("memory assignment error\n");
	tmp->link = NULL;
	return tmp;
}

void print_ic(IcecreamNode* head) {
	IcecreamNode* curr = head;
	while (curr != NULL) {
		printf("%d번 %s %dkcal %d회\n", curr->ic_num, curr->name, curr->kcal, curr->prefer);
		curr = curr->link;
	}
}

void printIcInfo(IcecreamNode* head) // 노드 하나만 출력
{
	IcecreamNode* curr = head;
	printf("%d번 %s %dkcal %d회\n", curr->ic_num, curr->name, curr->kcal, curr->prefer);
	printf("\n");
}

void print_bv(BeverageNode* head) {
	BeverageNode* curr = head;
	while (curr != NULL) {
		printf("%d번 %s %dg %dkcal %d원 %d번\n", curr->bv_num, curr->bvtype, curr->bvserving, curr->kcal, curr->bvprice, curr->prefer);
		curr = curr->link;
	}
}

void printBvInfo(BeverageNode* head)
{
	BeverageNode* curr = head;
	printf("%d번 %s %dg %dkcal %d원 %d회\n", curr->bv_num, curr->bvtype, curr->bvserving, curr->kcal, curr->bvprice, curr->prefer);
	printf("\n");
}

void Cal(Order* order, InfoHead* InfoHead)
{
	int total_price = 0, money = 0, change = 0;
	int membership;
	for (MList* i = order->head; i != NULL; i = i->link) {
		switch (i->type) {
		case 1:
			for (IcecreamConeNode* j = InfoHead->icecreamcone_link; j != NULL; j = j->link) {
				if (!strcmp(i->menu_name, j->ctype)) {
					total_price += (i->num * j->cprice);
					break;
				}
			}
		case 2:
			for (HandPackNode* j = InfoHead->handpack_link; j != NULL; j = j->link) {
				if (!strcmp(i->menu_name, j->htype)) {
					total_price += (j->hprice);
					break;
				}
			}
		case 3:
			for (BeverageNode* j = InfoHead->beverage_link; j != NULL; j = j->link) {
				if (!strcmp(i->menu_name, j->bvtype)) {
					total_price += (i->num * j->bvprice);
					break;
				}
			}
		}
	}
	//멤버십 여부에 따라 파인트 30% 할인
	printf("KT 멤버십 고객이시라면 파인트를 30%%\ 할인해드립니다. KT 멤버십 고객이신가요?\n");
	membership = getYesorNo();
	if (membership == 1) {
		for (MList* i = order->head; i != NULL; i = i->link) {
			if (!strcmp(i->menu_name, "파인트")) {
				total_price -= 2500;
			}
		}
	}
	while (1) {
		printf("총 가격은 %d 원 입니다. 지불할 액수를 입력해주세요(원) : ", total_price);
		scanf_s("%d", &money);
		change = money - total_price;
		if (change >= 0) {
			printf("거스름돈은 %d 원입니다. 베스킨라빈스를 이용해주셔서 감사합니다!\n", change);
			printf("---------------------------------------------------------------\n");
			saveTxt(InfoHead);
			free(order);
			exit(1);
		}
		else {
			printf("\n금액이 부족합니다. 액수를 다시 입력해 주세요.\n");
			printf("---------------------------------------------------------------\n");
			change = 0;
		}
	}
}

int getYesorNo() // Y 또는 N의 값을 입력받는 함수
{
	int key;

	printf("(예 : Y, 아니오 : N) : ");

	while ((key = getch()) != NULL) {
		if (key == 'y' || key == 'Y') {
			puts("Y");
			return 1; // 참을 반환
		}
		else if (key == 'n' || key == 'N') {
			puts("N");
			return 0; // 거짓을 반환
		}
	}
	return -1;
}

void saveTxt(InfoHead* info_head) {
	IcecreamNode* ic = info_head->icecream_link;
	BeverageNode* bv = info_head->beverage_link;
	IcecreamNode* ic_tmp = NULL;
	BeverageNode* bv_tmp = NULL;

	FILE* fp;
	if (fopen_s(&fp, "Icecream_tmp.txt", "w") != NULL) {
		printf("It is not exist\n");
		exit(1);
	}
	else {
		while (ic != NULL) {
			fprintf(fp, "%d %s %d %d\n", ic->ic_num, ic->name, ic->kcal, ic->prefer);
			ic_tmp = ic;
			ic = ic->link;
			free(ic_tmp);
		}
	}
	fclose(fp);

	FILE* fp1;
	if (fopen_s(&fp1, "Beverage_tmp.txt", "w") != NULL) {
		printf("It is not exist\n");
		exit(1);
	}
	else {
		while (bv != NULL) {
			fprintf(fp1, "%d %s %d %d %d %d\n", bv->bv_num, bv->bvtype, bv->bvserving, bv->kcal, bv->bvprice, bv->prefer);
			bv_tmp = bv;
			bv = bv->link;
			free(bv_tmp);
		}
	}
	fclose(fp1);

}

int main(void)
{
	IcecreamNode* getInfoIc = NULL;
	BeverageNode* getInfoBv = NULL;
	IcecreamNode* editIc = NULL;
	int input;

	InfoHead* info_head = loadTxt();
	printf("===========================================\n");
	printf("** ^^어서오세요 배스킨라빈스 31입니다^^ **\n");
	printf("===========================================\n");
	printf("\n");
	do
	{
		printf("\n원하시는 번호를 눌러 선택해주세요\n");
		printf("\n");
		printf("0. 종료하기\n");
		printf("1. 아이스크림 정보 열람\n");
		printf("2. 음료 정보 열람\n");
		printf("3. 주문하기\n");
		printf("4. 아이스크림 정보 검색하기\n");
		printf("5. 음료 정보 검색하기\n");
		printf("\n");
		printf("===========================================\n");
		printf("**** 관리자 설정 ****\n");
		printf("===========================================\n");
		printf("6. 아이스크림 메뉴 추가하기\n");
		printf("7. 아이스크림 메뉴 삭제하기\n");
		printf("8. 음료 메뉴 추가하기\n");
		printf("9. 음료 메뉴 삭제하기\n");
		printf("\n");
		printf("원하시는 번호를 입력해주세요\n");
		scanf_s("%d", &input);

		switch (input)
		{
		case 0:
			printf("감사합니다^^ 종료하겠습니다\n");
			saveTxt(info_head);
			break;

		case 1:
			// 아이스크림 전체 정보 열람
			print_ic(info_head->icecream_link);
			break;

		case 2:
			// 음료 전체 정보 열람 
			print_bv(info_head->beverage_link);
			break;

		case 3:
			Ordering(info_head);
			break;

		case 4:
			// 찾고 싶은 아이스크림 정보 검색   
			getInfoIc = search_ic_with_name(info_head->icecream_link);
			printIcInfo(getInfoIc);
			break;

		case 5:
			// 찾고 싶은 음료 정보 검색   
			getInfoBv = search_bv_with_name(info_head->beverage_link);
			printBvInfo(getInfoBv);
			break;

		case 6:
			// 메뉴 추가  
			printf("** 아이스크림 정보를 추가하겠습니다 **\n");
			info_head->icecream_link = add_icecream_menu(&(info_head->icecream_link));
			printf("\n");
			print_ic(info_head->icecream_link);// ic를 매개변수로 전달해도 상관 없음.  
			break;
		case 7:
			// 메뉴 삭제 함수 
			printf("** 아이스크림 정보를 삭제하겠습니다 **\n");
			print_ic(info_head->icecream_link);
			IcecreamNode* ic_searched = search_ic_with_name(info_head->icecream_link);
			delete_icecream_menu(&info_head->icecream_link, ic_searched);
			printf("\n");
			print_ic(info_head->icecream_link);
			break;

		case 8:
			// 메뉴 추가 함수 
			printf("** 음료 정보를 추가하겠습니다 **\n");
			info_head->beverage_link = add_bv_menu(&info_head->beverage_link);
			printf("\n");
			print_bv(info_head->beverage_link);
			break;

		case 9:
			// 메뉴 삭제 함수 
			printf("** 음료 정보를 삭제하겠습니다 **\n");
			print_bv(info_head->beverage_link);
			BeverageNode* bv_searched = search_bv_with_name(info_head->beverage_link);
			delete_bv_menu(&info_head->beverage_link, bv_searched);
			printf("\n");
			print_bv(info_head->beverage_link);
			break;
		}
	} while (input != 0);

	return 0;
}