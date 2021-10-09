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
	int num;
	struct MList* link;
}MList;

typedef struct IcecreamNode {
	int ic_num; // ��ȣ
	char name[MAX]; // ��ǰ��
	int kcal; // ����(kcal)
	int prefer; // ��ǰ��ȣ����
	struct IcecreamNode* link; // ���� ����� �ּҸ� ������ ������ 
}IcecreamNode;

typedef struct IcecreamConeNode {
	int con_num; // ��ȣ
	char ctype[MAX]; // ������
	int cserving; // ������(g)
	int cprice; // ����(\)
	struct IcecreamConeNode* link;
}IcecreamConeNode;

typedef struct HandPackNode {
	int hp_num; // ��ȣ
	char htype[MAX]; // ������
	int hserving; // ������(g)
	int hprice; // ����(\)
	struct HandPackNode* link;
}HandPackNode;

typedef struct InfoHead {
	IcecreamNode* icecream_link;
	IcecreamConeNode* icecreamcone_link;
	HandPackNode* handpack_link;
	//���̽�ũ�� ����ũ, Ŀ��, ����� ���Ͽ��� ���Ḯ��Ʈ�� ����� �� head�� ����Ų��.
}InfoHead;

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
InfoHead* loadTxt();

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
	//Cal(order);
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

void show(Order* order) {
	printf("~~~~~~~~~�ֹ�����~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (MList* i = order->head; i != NULL; i = i->link) {
		if (i->num > 1) {
			printf("* �޴� : %s, ���� : 1��\n���̽�ũ�� ����\n", i->menu_name);
			for (int j = 0; j < i->num; j++)
				printf("%d. %s\n", j + 1, i->icecream[j]);
		}
		else
			printf("�޴� : %s, ���̽�ũ�� ���� : %s, ���� : %d��\n", i->menu_name, i->icecream[0], i->num);
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

void CoffeeList() {
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
	char* name;
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
	(*porder)->spoon_num = -1;
	strcpy(node->menu_name, icecreamtype_name);

	for (int i = 0; i < num;) {
		IcecreamList(Icecream_info);
		printf("%d���� ���� �����ϼ���.\n", num - i);
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
		strcpy(node->icecream[i++], name);
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
	printf(total_price);
	for (MList* i = order->head; i != NULL; i = i->link) { // �޴� �̸��� ���� ���� ���
		if (strcmp(i->menu_name, "�̱۷��ַ�") == 0) total_price += i->num * 3200;
		else if (strcmp(i->menu_name, "�̱�ŷ") == 0) total_price += i->num * 4000;
		else if (strcmp(i->menu_name, "�����ִϾ�") == 0) total_price += i->num * 4300;
		else if (strcmp(i->menu_name, "�����ַ�") == 0) total_price += i->num * 6200;
		else if (strcmp(i->menu_name, "����Ʈ") == 0) total_price += i->num * 8200;
		else if (strcmp(i->menu_name, "����") == 0) total_price += i->num * 15500;
		else if (strcmp(i->menu_name, "�йи�") == 0) total_price += i->num * 22000;
		else if (strcmp(i->menu_name, "��������") == 0) total_price += i->num * 26500;
	}
	printf(total_price);
	// ����� ���ο� ���� ����Ʈ 30% ����
	char membership;
	printf("KT ����� ���̽ö�� ����Ʈ�� 30%%\ �����ص帳�ϴ�. KT ����� ���̽Ű���?\n");
	printf("(�� : Y, �ƴϿ� : N) : ");
	scanf_s("%s", &membership);
	if (strcmp(membership, "Y") == 0 || strcmp(membership, "y") == 0) {
		for (MList* i = order->head; i != NULL; i = i->link) {
			if (strcmp(i->menu_name, "����Ʈ") == 0) total_price -= (i->num * 2500);
		}
	}
	printf("�� ������ %d �� �Դϴ�. ����Ų��󽺸� ã���ּż� �����մϴ�!\n", total_price);
	printf("---------------------------------------------------------------\n");
	exit(1);
}
*/

InfoHead* loadTxt() {
	InfoHead* info_head = (InfoHead*)malloc(sizeof(info_head));
	if (!info_head)
		MemoryError("memory assignment error\n");
	IcecreamNode* icecream_head = NULL;
	IcecreamConeNode* icecreamcone_head = NULL;
	HandPackNode* handpack_head = NULL;

	FILE* fp = fopen("icecream_info.txt", "r");
	if (!fp)
		MemoryError("File open error\n");
	while (!feof(fp))// ���� ������ ���� ���� (���� ������ ��� 0 ��ȯ)
	{
		IcecreamNode* newnode = makeNode();
		fscanf(fp, "%d %s %d %d \n", &(newnode->ic_num), newnode->name, &(newnode->kcal), &(newnode->prefer));
		if (icecream_head == NULL)
			icecream_head = newnode;
		else {
			newnode->link = icecream_head;
			icecream_head = newnode;
		}
	}
	fclose(fp);

	FILE* fp1 = fopen("icecreamCone_info.txt", "r");
	if (!fp1)
		MemoryError("File open error\n");
	while (!feof(fp1))// ���� ������ ���� ���� (���� ������ ��� 0 ��ȯ)
	{
		IcecreamConeNode* newnode1 = makeNode();
		fscanf(fp1, "%d %s %d %d \n", &(newnode1->con_num), newnode1->ctype, &(newnode1->cserving), &(newnode1->cprice));
		printf("%d %s %d %d\n", newnode1->con_num, newnode1->ctype, newnode1->cserving, newnode1->cprice);
		if (icecreamcone_head == NULL)
			icecreamcone_head = newnode1;
		else {
			newnode1->link = icecreamcone_head;
			icecreamcone_head = newnode1;
		}
	}
	fclose(fp1);


	FILE* fp2 = fopen("HandPack_info.txt", "r");
	if (!fp2)
		MemoryError("File open error\n");
	while (!feof(fp2))// ���� ������ ���� ���� (���� ������ ��� 0 ��ȯ)
	{
		HandPackNode* newnode = makeNode();
		fscanf(fp2, "%d %s %d %d \n", &(newnode->hp_num), newnode->htype, &(newnode->hserving), &(newnode->hprice));
		if (handpack_head == NULL)
			handpack_head = newnode;
		else {
			newnode->link = handpack_head;
			handpack_head = newnode;
		}
	}
	fclose(fp2);

	info_head->icecream_link = icecream_head;
	info_head->icecreamcone_link = icecreamcone_head;
	info_head->handpack_link = handpack_head;

	IcecreamConeNode* curr = info_head->icecreamcone_link;
	while (curr != NULL) {
		printf("%d %s %d %d\n", curr->con_num, curr->ctype, curr->cserving, curr->cprice);
		curr = curr->link;
	}

	return info_head;
}

void print_ic(IcecreamNode* head) {
	IcecreamNode* curr = head;
	while (curr != NULL) {
		printf("%d %s %d %d\n", curr->ic_num, curr->name, curr->kcal, curr->prefer);
		curr = curr->link;
	}
}

void print_ic2(IcecreamConeNode* head) {
	IcecreamConeNode* curr = head;
	while (curr != NULL) {
		printf("%d %s %d %d\n", curr->con_num, curr->ctype, curr->cserving, curr->cprice);
		curr = curr->link;
	}
}

void print_ic3(HandPackNode* head) {
	HandPackNode* curr = head;
	while (curr != NULL) {
		printf("%d %s %d %d\n", curr->hp_num, curr->htype, curr->hserving, curr->hprice);
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

int main() {
	InfoHead* info_head = loadTxt();
	//print_ic(info_head->icecream_link);
	printf("\n");
	//print_ic2(info_head->icecreamcone_link);
	printf("\n");
	//print_ic3(info_head->handpack_link);
	//Ordering(info_head);
}