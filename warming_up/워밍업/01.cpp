#include <stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
//j =  가로
//i= 세로
void print_hang(int hang[][3]);
int add(int hang[][3], int yeol[][3]);
int minus(int hang[][3], int yeol[][3]);
int multiple(int hang[][3], int yeol[][3]);
int det(int a[][3]);
void four_det(int hang[][3]);

int main()
{
	int hang[3][3];
	int yeol[3][3];

	srand(time(NULL));
	char menu;
	for (int i = 0; i < 3; i++)

	{
		for (int j = 0; j < 3; j++)
		{
			hang[i][j] = rand() % 2;
		}
	}
	for (int i = 0; i < 3; i++)

	{
		for (int j = 0; j < 3; j++)
		{
			yeol[i][j] = rand() % 2;
		}
	}
	
	while (1)
	{
		for (int i = 0; i < 3; i++)

		{
			for (int j = 0; j < 3; j++)
			{
				hang[i][j] = rand() % 2;
			}
		}
		for (int i = 0; i < 3; i++)

		{
			for (int j = 0; j < 3; j++)
			{
				yeol[i][j] = rand() % 2;
			}
		}
		printf("M/m:행렬의 곱셈 A/a:행렬의 덧셈 D/d :행렬의 뺄셈 R/r:행렬식의 값 H/h:3X3 행렬을 4X4 행렬로 변환 Q/q:프로그램 종료 \n");
		scanf_s("%c", &menu);

		switch (menu)
		{
		case 'a':
		case 'A': // 행열 덧셈
			print_hang(hang);
			printf("\n");
			print_hang(yeol);
			printf("\n");
			add(hang, yeol);
		break;
		case 'm':
		case 'M':// 행열 곱셈
			print_hang(hang);
			printf("\n");
			print_hang(yeol);
			printf("\n");
			multiple(hang, yeol);
	
			break;
		case 'd':
		case 'D': // 행열 뺄셈
			print_hang(hang);
			printf("\n");
			print_hang(yeol);
			printf("\n");
			minus(hang, yeol);
			break;
		case 'R':
		case 'r': // 행렬식 구하기
			print_hang(hang);
			printf("\n");
			printf("%d \n",det(hang));
			break;
		case 'h':
		case 'H':
			four_det(hang);
			break;
		case 'q':
		case 'Q':
			printf("프로그램을 종료합니다 \n");
			exit(0);
			break;
		}
	

	}


	
}

void print_hang(int hang[][3])
{
	for (int i = 0; i < 3; i++)

	{
		for (int j = 0; j < 3; j++)
		{
			printf(" %d ", hang[i][j]);

		}
		printf("\n");
	}
}
int add(int hang[][3], int yeol[][3])
{
	int add[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			add[i][j] = hang[i][j] + yeol[i][j];
		}
	}

	print_hang(add);
	return 0;
}

int minus(int hang[][3], int yeol[][3])
{
	int add[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			add[i][j] = hang[i][j] - yeol[i][j];
		}
	}

	print_hang(add);
	return 0;
}

int multiple(int hang[][3], int yeol[][3])
{
	int multiple[3][3] = { 0, };

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				multiple[i][j] += hang[i][k] * yeol[k][j];
			}

		}
	}

	print_hang(multiple);
	return 0;
}

int det(int a[][3])
{
	int det;
	det = a[0][0] * (a[1][1] * a[2][2] - a[2][1] * a[1][2])

		- a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0])

		+ a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]);

	
	return det;
}

void four_det(int hang[][3])
{
	int four[4][4] = { 0, };
	int f_det = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			four[i][j] = hang[i][j];
		}
	}
	four[3][3] = 1;


	int cofa_1[3][3] = { 0, };
	int cofa_2[3][3] = { 0, };
	int cofa_3[3][3] = { 0, };
	int cofa_4[3][3] = { 0, };

	cofa_1[0][0] = four[1][0];
	cofa_1[0][1] = four[1][2];
	cofa_1[0][2] = four[1][3];

	cofa_1[1][0] = four[2][0];
	cofa_1[1][1] = four[2][2];
	cofa_1[1][2] = four[2][3];

	cofa_1[2][0] = four[3][0];
	cofa_1[2][1] = four[3][2];
	cofa_1[2][2] = four[3][3];


	cofa_2[0][0] = four[0][0];
	cofa_2[0][1] = four[0][2];
	cofa_2[0][2] = four[0][3];

	cofa_2[1][0] = four[2][0];
	cofa_2[1][1] = four[2][2];
	cofa_2[1][2] = four[2][3];

	cofa_2[2][0] = four[3][0];
	cofa_2[2][1] = four[3][2];
	cofa_2[2][2] = four[3][3];



	cofa_3[0][0] = four[0][0];
	cofa_3[0][1] = four[0][2];
	cofa_3[0][2] = four[0][3];

	cofa_3[1][0] = four[1][0];
	cofa_3[1][1] = four[1][2];
	cofa_3[1][2] = four[1][3];

	cofa_3[2][0] = four[3][0];
	cofa_3[2][1] = four[3][2];
	cofa_3[2][2] = four[3][3];


	cofa_4[0][0] = four[0][0];
	cofa_4[0][1] = four[0][2];
	cofa_4[0][2] = four[0][3];

	cofa_4[1][0] = four[1][0];
	cofa_4[1][1] = four[1][2];
	cofa_4[1][2] = four[1][3];

	cofa_4[2][0] = four[2][0];
	cofa_4[2][1] = four[2][2];
	cofa_4[2][2] = four[2][3];



	f_det = four[0][1] * pow(-1, (2 + 1))*det(cofa_1) +
		four[1][1] * pow(-1, (2 + 2))*det(cofa_2) +
		four[2][1] * pow(-1, (2 + 3))*det(cofa_3) +
		four[3][1] * pow(-1, (2 + 4))*det(cofa_4);




	print_hang(hang);
	printf("\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf(" %d ", four[i][j]);
		}
		printf("\n");
	}
	printf("%d \n", f_det);

}





