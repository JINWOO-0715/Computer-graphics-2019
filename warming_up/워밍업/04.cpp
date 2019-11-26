#include <stdio.h>
#include <time.h>
#include<stdlib.h>
#include <string.h>
#include<iostream>

struct Point 
{
	int left;
	int right;
	int top;
	int bottom;

	int x;
	int y;


};
bool check_rectangle(Point &num1, Point &num2);
bool check_circle(Point &num1, Point &num2);

int main()
{
	Point num1;
	Point num2;

	srand(time(NULL));
	
	num1.bottom=400;
	num1.left = 100;
	num1.right = 300;
	num1.top = 100;


	num2.bottom = 500;
	num2.left = 400;
	num2.right = 500;
	num2.top = 400;
/*	num1.bottom= rand() % 501;
	num1.left = rand() % 501;
	num1.right = rand() % 501;
	num1.top = rand() % 501;

	num2.bottom = rand() % 501;
	num2.left = rand() % 501;
	num2.right = rand() % 501;
	num2.top = rand() % 501;

	*/

	char menu;
	for(;;)
	{

		std::cout << "1.사각형 * 사각형 2.사각형 * 원"<<std::endl;
		std::cout << " 이동 왼쪽:a 아래:s 위:w 오른쪽d" << std::endl;
		std::cout << "모양 1 : " << num1.left <<" "<< num1.top<< "   " << num1 .right<< " " << num1 .bottom<< std::endl;
		std::cout << "모양 2 : " << num2.left << " "<<num2.top << "   " << num2.right << " " << num2.bottom << std::endl;

		std::cin >> menu;
		if (menu == '1')
		{
			std::cout << "  사각형&&사각형"<<std::endl;
			if (check_rectangle(num1, num2))
			{
				std::cout << "충돌입니다" << std::endl;
			}
			else
			{
				std::cout << "아직 안했어요" << std::endl;

			}
		}
		if (menu == '2')
		{
			std::cout << "  사각형&&원" << std::endl;
			if (check_rectangle(num1, num2))
			{
				std::cout << "충돌입니다" << std::endl;
			}
		}
		if (menu == 'a' || menu == 'A')
		{


			num2.left -= 60;
			num2.right-= 60;
			


		}
		if (menu == 'd' || menu == 'D')
		{
	
			num2.left += 60;
			num2.right += 60;
		
		}
		if (menu == 's' || menu == 'S')
		{
		
			num2.top += 60;
			num2.bottom += 60;
	
		}
		if (menu == 'w' || menu == 'W')
		{

			num2.top -= 60;
			num2.bottom -= 60;
		
		}
		
	
	}


	return 0;

	
}
//num2가 움직이는애 
bool check_rectangle(Point &num1, Point &num2)
{
	if ((num1.right >= num2.left) && (num2.right >= num1.left) && (num1.top <= num2.bottom)&&  (num1.bottom >= num2.top))
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool check_circle(Point &num1, Point &num2)
{

	// 넘1 사각형 넘2 원 

	Point cir;
	cir.x = abs(num2.right - num2.left);
	cir.y = abs(num2.top - num2.bottom);
	int radian = abs(num2.right - num2.left);

	if ()
	{

	}

	else
	{
		return false;
	}
}