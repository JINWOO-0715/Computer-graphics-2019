#include<stdio.h>
#include<iostream>

struct point
{
	int x;
	int y;
	int z;
	bool check = false;

	void init(int _x, int _y, int _z, bool _check)
	{
		x = _x;
		y = _y;
		z = _z;
		check = _check;
	}



};
point p[10];
void print_list();
void show_menu();


int main()
{
	int x;
	int y;
	int z;
	char menu;
	int delete_point = 0; // 큐
	int make_point = -1;
	int pos = 0;// 스택
	point tmp[11];

	while (1)
	{


		printf("%d \t %d %d\n", pos, make_point, delete_point);
		print_list();
		show_menu();


		std::cin >> menu;
		switch (menu)
		{
			if (pos == -1)
			{
				pos = 0;
			}
			else if (make_point == -1)
			{
				make_point = 0;
			}
		case '+':
			printf("x y z 를 입력하세요 \n");
			scanf("%d", &x);
			scanf("%d", &y);
			scanf("%d", &z);
			p[pos].init(x, y, z, true);
			pos++;
			break;
		case '-':
			printf("맨위에서 리스트를 삭제합니다 \n");
			if (pos != -1)
			{
				pos--;
				p[pos].init(0, 0, 0, false);
			
			}
			else
			{
				printf("지울게 없습니다 \n");
			}



			break;
		case 'e':
		
			printf("x y z 를 입력하세요 \n");
			scanf("%d", &x);
			scanf("%d", &y);
			scanf("%d", &z);
	

			if (delete_point==0&& make_point==-1)
			{
				for (int i = 0; i < pos; i++)
				{
					p[i + 1] = p[i];
				}
				p[delete_point].init(x, y, z, true);
			
	
			}
			else
			{
			
				p[make_point].init(x, y, z, true);
				make_point--;
				delete_point--;

			}
		
			if (p[0].check == true)
			{
				pos++;

			}


			break;
		case 'd':

			printf("맨 아래에서 리스트를 삭제합니다 \n");
			if (p[delete_point].check ==true)
			{
				p[delete_point].init(0, 0, 0, false);
				delete_point++;
				make_point++;
			}
			else
			{
				printf("지울게 없습니다 \n");
			}

			break;
		case 'l':
			print_list();
			break;
		case 'c':
			break;
		case 'm':

			break;
		case 'n':
			break;
		case 'q':
			exit(0);
			break;

		}

	}
	rewind(stdin);


}
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
	for (int i = 0; i < 10; i++)
	{
		if (p[i].check == true)

			printf(" %d | %d %d %d \n ", i, p[i].x, p[i].y, p[i].z);

		else
		{
			printf( "%d | 비었다 \n", i);
		}
	}

}
