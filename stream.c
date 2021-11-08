#include"stream.h"
void MemoryError(char* message) {
	printf("%s", message);
	exit(1);
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
void saveTxt(InfoHead* info_head) {
	IcecreamNode* ic = info_head->icecream_link;
	BeverageNode* bv = info_head->beverage_link;
	IcecreamNode* ic_tmp = NULL;
	BeverageNode* bv_tmp = NULL;

	FILE* fp;
	if (fopen_s(&fp, "Icecream_info.txt", "w") != NULL) {
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
	if (fopen_s(&fp1, "Beverage_info.txt", "w") != NULL) {
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

char* search_ic_with_num(IcecreamNode* Icecream_info, int menu_num) {
	for (IcecreamNode* i = Icecream_info; i != NULL; i = i->link) {
		if (i->ic_num == menu_num) {
			i->prefer++;
			return i->name;
		}
	}
	return NULL;
}

IcecreamNode* search_ic_with_name(IcecreamNode* phead) // 이름 검색
{
	IcecreamNode* p = phead;
	char n[MAX];

	do
	{
		printf("** 검색할 아이스크림의 이름을 입력해주세요 **\n");
		scanf_s("%s", n, sizeof(n));

		while (p != NULL)
		{
			if (strcmp(p->name, n) == 0) // 각 노드의 데이터에 있는 이름 비교 
				return p; // 찾으면 while 문 빠져나옴
			p = p->link; // 다음 노드로 이동
		}
		if (p == NULL) // 마지막까지 갔는데 검색한 아이스크림 정보가 존재하지 않는다면 
		{
			printf("\n검색한 아이스크림 정보가 존재하지 않습니다\n\n");
			continue;
		}
	} while (p == NULL);

	return p; // 검색할 아이스크림의 이름을 가진 노드 주소값 반환
}

char* search_bv_with_num(BeverageNode* beverage_info, int menu_num) {
	for (BeverageNode* i = beverage_info; i != NULL; i = i->link) {
		if (i->bv_num == menu_num) {
			i->prefer++;
			return i->bvtype;
		}
	}
	return NULL;
}

BeverageNode* search_bv_with_name(BeverageNode* phead) // 이름 검색
{
	BeverageNode* p = phead;
	char n[MAX];

	do
	{
		printf("** 검색할 음료의 이름을 입력해주세요 **\n");
		scanf_s("%s", n, sizeof(n));

		while (p != NULL)
		{
			if (strcmp(p->bvtype, n) == 0) // 각 노드의 데이터에 있는 이름 비교 
				return p; // 찾으면 while 문 빠져나옴
			p = p->link; // 다음 노드로 이동
		}
		if (p == NULL) // 마지막까지 갔는데 검색한 음료 정보가 존재하지 않는다면 
		{
			printf("\n검색한 음료 정보가 존재하지 않습니다\n\n");
			continue;
		}
	} while (p == NULL);

	return p; // 검색할 음료의 이름을 가진 노드 주소값 반환
}
