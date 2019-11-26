#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10
typedef struct _POINT
{

	int x;
	int y;
	int z;
	bool check;

	struct _POINT  *next;
	struct _POINT  *prev;

}point;
typedef struct _List
{
	point * head;
	point * tail;

}List;

int size = 10;
List *list;

void show_menu()
{
	printf("+ 리스트의 맨 위에서 입력\n");
	printf("- 리스트의 맨 위에서 삭제\n");
	printf("e 리스트의 맨 아래에서 입력\n");
	printf("d 리스트의 맨 아래에서 삭제\n");
	printf("l 리스트의 길이 출력 \n");
	printf("c 리스트를 비운다\n");
	printf("m 원점에서 가장 먼 점의 좌표 출력\n");
	printf("n 원점에서 가장 가까운먼 점의 좌표 출력\n");
	printf("q 종료\n");


}
void print_list() // 위에서 아래로 출력
{


}
List *list_insert(List *list, point *target)
{
	if (list->head->next == list->tail)
	{
		target->next = list->tail;
		list->tail->prev = target;
	
		target->prev = list->head;
		list->head->next = target;
		return list;
	}

	else
	{
		point *index = list->head;
		while (index->next != list->tail)

		{
			index = index->next;
		}
		target->next = list->tail;
		list->tail->prev = target;
		index->next = target;
		target->prev = index;
		return list;
	}

}
List *Listnit(List *list, point *p)
{
	list = (List*)malloc(sizeof(List));
	list->head = (point*)malloc(sizeof(point));
	list->tail = (point*)malloc(sizeof(point));

	list->head->next = list->tail;
	list->head->prev = list->tail;

	list->tail->next = list->head;
	list->tail->prev = list->head;
	for (int i = 0; i < 10; i++)
	{
		if (p != nullptr)
		{
			list_insert(list, &p[i]);
		}
		
	}
	return list;
}


void printall(List *list)
{
	point *index = list->head->next;	
	int i = 0;
	while (index != list->tail)
	{
	
		printf("%d  | x : %d  y: %d  z:%d  거리 \n", i, index->x, index->y, index->z);
		index = index->next;
		i++;
	}
}
int main()
{
	int menu = 0;
	point *p = (point *)malloc(sizeof(point) * 10);
	for (int i = 0; i < 10; i++)
	{
		p[i].x = 0;
		p[i].y = 0;
		p[i].z = 0;
		p[i].check = false;
	}
	int a = 0;

	list =Listnit(list, p);
	printall(list);

	
	return 0;
	free(p);
}