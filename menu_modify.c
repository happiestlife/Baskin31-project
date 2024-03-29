#include"menu_modify.h"
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