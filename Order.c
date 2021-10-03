#include<stdio.h>
#define MAX 20

typedef struct IcecreamNode {		// ���̽�ũ�� ����
	int ic_num; // ��ȣ	
	char name[30]; // ��ǰ��
	int kcal; // ����(kcal)
	int prefer; // ��ǰ��ȣ����
	struct IcecreamNode* link; // ���� ����� �ּҸ� ������ ������ 
}IcecreamNode;

typedef struct IcecreamConeNode {	// �� ����
	int con_num; // ��ȣ
	char ctype[30]; // ������
	int cserving; // ������(g)
	int cprice; // ����(\)
	struct IcecreamConeNode* link;
}IcecreamConeNode;

typedef struct HandPackNode {		// hadnpack ����
	int hp_num; // ��ȣ
	char htype[30]; // ������
	int hserving; // ������(g)
	int hprice; // ����(\)
	struct HandPackNode* link;
}HandPackNode;

typedef struct BeverageNode {		// ����� ����
	int bv_num;
	char name[32];
	int kcal;
	int prefer;
	struct BeverageNode* link;
}BeverageNode;

typedef struct BeveragePriceNode {	// ����� ���� ����
	int con_num;
	char ctype[30];
	int cserving;
	int cprice;
	struct BaverageConeNode* link;
}BeveragePriceNode;

typedef struct Order {				// ���ֹ�����
	struct MList* head;
	int candle_num;
	int spoon_num;
}Order;

typedef struct MList {				// �����ֹ�����
	char menu_name[MAX];
	char icecream[6][MAX];
	int num; int hp;
	struct MList* link;
}MList;

typedef struct All_InfoHead {
	//���̽�ũ�� ����ũ, Ŀ��, ����� ���Ͽ��� ���Ḯ��Ʈ�� ����� �� head�� ����Ų��.
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
		MenuList(&order, info_head, type);	//�޴����� ���ϴ� �׸� �����ϱ�
		show(order);	// �ֹ���������
		printf("\n***********************\n1. �����ϱ�\n2. �� �ֹ��ϱ�\n***********************\n");
		scanf_s("%d", &type2);
		if (type2 == 1) {
			if (order->spoon_num == -1) {
				printf("���ϴ� ������ ������ �Է��ϼ���.\n");
				order->spoon_num = input();
				if (order->candle_num == -1) {
					printf("���ϴ� ���� ���� �Է��ϼ���.\n");
					order->candle_num = input();
				}
			}
			break;
		}
	}
	//����ϱ�
	Cal(order);
}

int input() {
	int num = 0;
	while (1) {
		scanf_s("%d", &num);
		if (num <= 0) {
			printf("�Ѱ��̻� �ֹ����ּ���.\n");
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
	printf("���ϴ� �׸��� �����ϼ���.\n");
	for (int type = 0; ;) {
		printf("***********************\n");
		printf("    1. IceCream\n");
		printf("    2. IceCreamCake\n");
		printf("    3. Beverage\n");
		printf("    4. Coffee\n");
		printf("***********************\n");
		scanf_s("%d", &type);
		if (type < 1 || type>4) {
			printf("1~4�� �׸���̿��� ����ּ���.\n");
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
void connect(IcecreamNode** phead, IcecreamNode* newnode) // ���Ḯ��Ʈ ����
{
	// phead�� �����ϴ� ��ü = head ���

	if (*phead == NULL)
		*phead = newnode; // head��尡 �����ϰ� �ִ� ��ü�� newnode�� �����ϰ� �ִ� ��ü�� �ٲٱ�
	else {
		newnode->link = *phead;
		*phead = newnode;
	}
}
void show(Order* order) {
	printf("~~~~~~~~~~~~~~~~~~~~�ֹ�����~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (MList* i = order->head; i != NULL; i = i->link) {
		if (i->num > 1) {
			printf("�޴� : %s, ���� : 1��\n�ؾ��̽�ũ�� ����\n", i->menu_name);
			for (int j = 0; j < i->num; j++)
				printf("%d. %s\n", j + 1, i->icecream[j]);
		}
		else
			printf("�޴� : %s, ���̽�ũ�� ���� : %s\n", i->menu_name, i->icecream[0]);
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void IcecreamType(Order** porder, IcecreamNode* Icecream_info) {
	int type = 0, Con_type = 0, Handpack_type = 0, _num = 0;
	char icecreamtype_name[MAX];
	printf("���ϴ� �׸��� �����ϼ���.\n");
	while (1) {													// Con&Cup�� HandPack�� �ϳ� ����
		printf("***********************\n");
		printf("    1. Con & Cup\n");
		printf("    2. HandPack\n");
		printf("***********************\n");
		scanf_s("%d", &type);
		if (type < 1 || type>2) {
			printf("1~4�� �׸���̿��� ����ּ���.\n");
			continue;
		}
		break;
	}

	printf("���ϴ� ����� �����ϼ���.\n");
	if (type == 1) {
		while (1) {
			printf("-----------------------\n");
			printf("    1. �̱۷��ַ�\n");
			printf("    2. �̱�ŷ\n");
			printf("    3. �����ִϾ�\n");
			printf("    4. �����ַ�\n");
			printf("-----------------------\n");
			scanf_s("%d", &Con_type);
			if (Con_type < 1 || Con_type>4) {
				printf("1~4�� �׸���̿��� ����ּ���.\n\n");
				continue;
			}
			break;
		}

		printf("��� �����Ͻ� �ǰ���?\n");
		_num = input();

		if (Con_type == 1) strcpy(icecreamtype_name, "�̱۷��ַ�");
		else if (Con_type == 2) strcpy(icecreamtype_name, "�̱�ŷ");
		else if (Con_type == 3)	strcpy(icecreamtype_name, "�����ִϾ�");
		else strcpy(icecreamtype_name, "�����ַ�");

		select_ConandCup(porder, Icecream_info, icecreamtype_name, _num);
	}
	else {
		while (1) {
			printf("-----------------------\n");
			printf("    1. ����Ʈ\n");
			printf("    2. ����\n");
			printf("    3. �йи�\n");
			printf("    4. ��������\n");
			printf("-----------------------\n");
			scanf_s("%d", &Handpack_type);
			if (Handpack_type < 1 || Handpack_type>4) {
				printf("1~4�� �׸���̿��� ����ּ���.\n\n");
				continue;
			}
			break;
		}
		if (Handpack_type == 1) {
			strcpy(icecreamtype_name, "����Ʈ");
			_num = 3;
		}
		else if (Handpack_type == 2) {
			strcpy(icecreamtype_name, "����");
			_num = 4;
		}
		else if (Handpack_type == 3) {
			strcpy(icecreamtype_name, "�йи�");
			_num = 5;
		}
		else {
			strcpy(icecreamtype_name, "��������");
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
	printf("���ϴ� �޴��� �����ϼ���.\n");
	//���̽�ũ�� ����ũ ����Ʈ ����
}

void BeverageList() {
	printf("���ϴ� �޴��� �����ϼ���.\n");
	//����� ����Ʈ ����
}

void DessertList() {
	printf("���ϴ� �޴��� �����ϼ���.\n");
	//Ŀ�� ����Ʈ ����
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
		printf("���ϴ� ���̽�ũ�� �׸��� ��ȣ�� �Է��ϼ���.\n");
		IcecreamList(Icecream_info);

		while (1) {
			printf("=> ");
			scanf_s("%d", &icecream_num);
			name = search(Icecream_info, icecream_num);
			if (icecream_num < 0 || !name) {
				printf("����Ʈ �ȿ��� �ֹ����ּ���.");
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
		printf("%d���� ���� �����ϼ���.\n", num);
		IcecreamList(Icecream_info);
		while (1) {
			printf("=> ");
			scanf_s("%d", &icecream_num);
			name = search(Icecream_info, icecream_num);
			if (icecream_num < 0 || !name) {
				printf("����Ʈ �ȿ��� �ֹ����ּ���.");
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
	MList* node = (MList*)malloc(sizeof(MList));		// �ֹ����� ���Ḯ��Ʈ(����)�� �����ϱ�
	if (!node)
		MemoryError("memory assignment error");
	//���ϴ� �׸��� Ž���ϼ� ã�� �޴��̸��� ������ ����

	printf("���ϴ� ������ �Է��Ͻʽÿ�.\n");
	num = input();

	strcpy(node->menu_name, name);
	node->num = num;

	store(porder, node);
}
/*
void Cal(Order* order)
{
	int total_price = 0;
	for (MList* i = order->head; i != NULL; i = i->link) { // �޴� �̸��� ���� ���� ���
		if (strcmp(i->menu_name, "�̱۷��ַ�") == 0) total_price += 3200;
		else if (strcmp(i->menu_name, "�̱�ŷ") == 0) total_price += 4000;
		else if (strcmp(i->menu_name, "�����ִϾ�") == 0) total_price += 4300;
		else if (strcmp(i->menu_name, "�����ַ�") == 0) total_price += 6200;
		else if (strcmp(i->menu_name, "����Ʈ") == 0) total_price += 8200;
		else if (strcmp(i->menu_name, "����") == 0) total_price += 15500;
		else if (strcmp(i->menu_name, "�йи�") == 0) total_price += 22000;
		else if (strcmp(i->menu_name, "��������") == 0) total_price += 26500;
	}
	// ����� ���ο� ���� ����Ʈ 30% ����
	int membership;
	printf("KT ����� ���̽ö�� ����Ʈ�� 30%%\ �����ص帳�ϴ�. KT ����� ���̽Ű���?\n");
	printf("(�� : 1, �ƴϿ� : 0) : ");
	scanf_s("%d", &membership);
	if (membership == 1) {
		for (MList* i = order->head; i != NULL; i = i->link) {
			if (strcmp(i->menu_name, "����Ʈ") == 0) total_price -= 2500;
		}
	}
	printf("�� ������ %d �� �Դϴ�. ����Ų��󽺸� ã���ּż� �����մϴ�!\n", total_price);
	printf("---------------------------------------------------------------\n");
	exit(1);
}*/

IcecreamNode* loadTxt() {
	IcecreamNode* head = NULL;

	FILE* fp = fopen("icecream_info.txt", "r");
	if (!fp)
		MemoryError("File open error\n");
	while (!feof(fp))// ���� ������ ���� ���� (���� ������ ��� 0 ��ȯ)
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
	//������ �׸���� ���� �ҷ�����

	info_head->icecream_link = Icecream_info;
	//������ ��ũ �ɾ��ֱ�

	return info_head;
}
int main() {
	InfoHead* info_head = uploade();
	Ordering(info_head);
}