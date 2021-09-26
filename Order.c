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
		MenuList(&order, type);	//�޴����� ���ϴ� �׸� �����ϱ�
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
	printf("~~~~~~~~~�ֹ�����~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	for (MList* i = order->head; i != NULL; i = i->link) {
		if (i->hp == 1) {
			printf("�޴� : %s, ���� : 1��\n���̽�ũ�� ����\n", i->menu_name);
			for (int j = 0; j < i->num; j++)
				printf("%d. %s\n", j + 1, i->icecream[j]);
		}
		else
			printf("�޴� : %s, ���̽�ũ�� ���� : %s ���� : %d��\n", i->menu_name, i->icecream[0], i->num);
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void IcecreamType(Order** porder) {
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
		else if (Con_type == 2)	strcpy(icecreamtype_name, "�����ִϾ�");
		else strcpy(icecreamtype_name, "�����ַ�");

		select_ConandCup(porder, icecreamtype_name, _num);
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

		select_Handpack(porder, icecreamtype_name, _num);
	}
}

void IcecreamList() {

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

void select_ConandCup(Order** porder, char* icecreamtype_name, int num) {
	int icecream_num = 0;
	for (int i = 0; i < num; i++) {
		MList* node = (MList*)malloc(sizeof(MList));
		if (!node)
			MemoryError();
		strcpy(node->menu_name, icecreamtype_name);
		node->num = 1;
		printf("���ϴ� ���̽�ũ�� �׸��� ��ȣ�� �Է��ϼ���.\n");
		IcecreamList();

		while (1) {
			scanf_s("%d", &icecream_num);
			if (icecream_num < 0) {
				printf("����Ʈ �ȿ��� �ֹ����ּ���.");
				continue;
			}
			break;
		}
		//���Ͽ��� num�� �˻��Ͽ� �´� �׸��� �̸��� �ִ´�.
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
	printf("%d���� ���� �����ϼ���.\n", num);
	for (int i = 0; i < num;) {
		IcecreamCakeList();
		while (1) {
			scanf_s("%d", &icecream_num);
			if (icecream_num < 0) {
				printf("����Ʈ �ȿ��� �ֹ����ּ���.");
				continue;
			}
			break;
		}
		//���Ͽ��� num�� �˻��Ͽ� �´� �׸��� �̸��� �ִ´�.
		//strcpy(node->icecream[i], --);
		i++;
		printf("%d�� ���ҽ��ϴ�.\n\n", num - i);
	}
	store(porder, node);
}

void select_else(Order** porder) {
	int num;
	char* name = NULL;
	MList* node = (MList*)malloc(sizeof(MList));		// �ֹ����� ���Ḯ��Ʈ(����)�� �����ϱ�
	if (!node)
		MemoryError();
	//���ϴ� �׸��� Ž���ϼ� ã�� �޴��̸��� ������ ����

	printf("���ϴ� ������ �Է��Ͻʽÿ�.\n");
	num = input();

	strcpy(node->menu_name, name);
	node->num = num;

	store(porder, node);
}

int main() {
	//Show_MenuType();
	Ordering();
}
