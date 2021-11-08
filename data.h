#pragma once
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
	int bv_num;	// 번호
	char bvtype[MAX]; // 제품명
	int bvserving; // 제공량
	int kcal; // 열량
	int bvprice; // 가격
	int prefer; // 선호도
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