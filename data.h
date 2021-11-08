#pragma once
#define MAX 30
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

typedef struct BeverageNode {
	int bv_num;	// ��ȣ
	char bvtype[MAX]; // ��ǰ��
	int bvserving; // ������
	int kcal; // ����
	int bvprice; // ����
	int prefer; // ��ȣ��
	struct BeverageNode* link;
}BeverageNode;

typedef struct InfoHead {
	IcecreamNode* icecream_link;
	IcecreamConeNode* icecreamcone_link;
	HandPackNode* handpack_link;
	BeverageNode* beverage_link;
}InfoHead;

typedef struct Order {			// �ֹ� ����Ʈ
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