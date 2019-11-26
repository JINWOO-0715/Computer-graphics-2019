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
	printf("+ ����Ʈ�� �� ������ �Է�\n");
	printf("- ����Ʈ�� �� ������ ����\n");
	printf("e ����Ʈ�� �� �Ʒ����� �Է�\n");
	printf("d ����Ʈ�� �� �Ʒ����� ����\n");
	printf("l ����Ʈ�� ���� ��� \n");
	printf("c ����Ʈ�� ����\n");
	printf("m �������� ���� �� ���� ��ǥ ���\n");
	printf("n �������� ���� ������ ���� ��ǥ ���\n");
	printf("q ����\n");


}
void print_list() // ������ �Ʒ��� ���
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
	
		printf("%d  | x : %d  y: %d  z:%d  �Ÿ� \n", i, index->x, index->y, index->z);
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