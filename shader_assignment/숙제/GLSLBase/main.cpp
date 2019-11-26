#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"

Renderer* g_Renderer = nullptr;
Renderer* Line = nullptr;
Renderer* slice_Line = nullptr;
size_t g_WindowSizeX = 800;
int g_stop = 1;
float spline_time = 0;
int spline_type = 0;
float spline_x_one = -1.5f;
float spline_y_one = -0.3f;

float spline_x_two = 0.0f;
float spline_y_two = 1.5f;

float spline_x_tir = 1.5f;
float spline_y_tir = -0.4f;

float spline_zero_one_x = 0.0f;
float spline_zero_one_y = 0.0f;

float spline_one_two_x = 0.0f;
float spline_one_two_y = 0.0f;

float spline_five_x[5] = { 0.0f, };
float spline_five_y[5] = { 0.0f ,};
float spline_five_connect[5] = { 0.0f, };

float tmp_x;
float tmp_y;
int tmp_count = 0;

int button = 1;
float convert_point_x(int x, float ox);
float convert_point_y(int y, float oy);
void Timerfunction(int value);
int spline_i = 0;
size_t g_WindowSizeY = 800;
int fly_speed = 100;
float angle = 0.0f;
void DrawScene(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	g_Renderer->DrawScene();
	Line->DrawScene();
	slice_Line->DrawScene();
	glutSwapBuffers();  // glFlush(); // 
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (tmp_count == 5)
		{
			tmp_count = 0;
		}
		spline_five_x[tmp_count] = convert_point_x(x, tmp_x);
		spline_five_y[tmp_count] = convert_point_y(y, tmp_y);
		slice_Line->Line_shape[0][0]= convert_point_x(x, tmp_x);
		slice_Line->Line_shape[0][1] = convert_point_y(y, tmp_y);
		tmp_count++;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		slice_Line->Line_shape[1][0] = convert_point_x(x, tmp_x);
		slice_Line->Line_shape[1][1] = convert_point_y(y, tmp_y);
	}

	printf("%f \n", spline_five_x[tmp_count]);

}

void Motion( int x, int y)
{
	slice_Line->Line_shape[1][0] = convert_point_x(x, tmp_x);
	slice_Line->Line_shape[1][1] = convert_point_y(y, tmp_y);
}
void Timerfunction(int value)
{
	switch (value)
	{
		
	case 1:

		spline_i += 1;
		spline_time = (spline_i / 100.0f);
		if (spline_i == 100)
		{
			spline_time = 0;
			spline_i = 0;
			spline_type = rand() % 2;
			g_Renderer->figure_shape = rand() % 2;
			
			spline_y_two = (float)rand() / RAND_MAX +0.8f;
		

			for (int i = 0; i < 100; i++)
			{
				spline_time = (i / 100.0f);
				spline_zero_one_x = ((1 - spline_time)*(spline_x_one))
					+ ((spline_time)*(spline_x_two));
				spline_zero_one_y = ((1 - spline_time)*(spline_y_one))
					+ ((spline_time)*(spline_y_two));


				spline_one_two_x = ((1 - spline_time)*(spline_x_two))
					+ ((spline_time)*(spline_x_tir));
				spline_one_two_y = ((1 - spline_time)*(spline_y_two))
					+ ((spline_time)*(spline_y_tir));


				Line->Line_shape[i][0] = ((1 - spline_time)*(spline_zero_one_x))
					+ ((spline_time)*(spline_one_two_x));
				Line->Line_shape[i][1] = ((1 - spline_time)*(spline_zero_one_y))
					+ ((spline_time)*(spline_one_two_y));
			}

		}
		
		if (spline_type == 0)
		{
			
			spline_zero_one_x = ((1 - spline_time)*(spline_x_one))
				+ ((spline_time)*(spline_x_two));
			spline_zero_one_y = ((1 - spline_time)*(spline_y_one))
				+ ((spline_time)*(spline_y_two));


			spline_one_two_x = ((1 - spline_time)*(spline_x_two))
				+ ((spline_time)*(spline_x_tir));
			spline_one_two_y = ((1 - spline_time)*(spline_y_two))
				+ ((spline_time)*(spline_y_tir));

			
			g_Renderer->top_point_x = ((1 - spline_time)*(spline_zero_one_x))
				+ ((spline_time)*(spline_one_two_x));
			g_Renderer->top_point_y = ((1 - spline_time)*(spline_zero_one_y))
				+ ((spline_time)*(spline_one_two_y));

		}
		else
		{
			spline_zero_one_x = ((1 - spline_time)*(spline_x_tir))
				+ ((spline_time)*(spline_x_two));
			spline_zero_one_y = ((1 - spline_time)*(spline_y_tir))
				+ ((spline_time)*(spline_y_two));

			spline_one_two_x = ((1 - spline_time)*(spline_x_two))
				+ ((spline_time)*(spline_x_one));
			spline_one_two_y = ((1 - spline_time)*(spline_y_two))
				+ ((spline_time)*(spline_y_one));


			g_Renderer->top_point_x = ((1 - spline_time)*(spline_zero_one_x))
				+ ((spline_time)*(spline_one_two_x));
			
			g_Renderer->top_point_y = ((1 - spline_time)*(spline_zero_one_y))
				+ ((spline_time)*(spline_one_two_y));

		}
		glutTimerFunc(fly_speed, Timerfunction, g_stop);

		glutPostRedisplay();
		break;
	case 2:
		for (int j = 0; j < 5; j++)
		{
			for (int i = 0; i < 100; i++)
			{
				spline_time = i / 100.0f;
				Line->Line_shape[i][0] = (((pow(-spline_time, 3)) + (2 * pow(spline_time, 2)) - (spline_time))*spline_five_x[j % 5] +
					((3 * pow(spline_time, 3)) - 5 * (pow(spline_time, 2)) + 2)* spline_five_x[(j + 1) % 5] +
					(-3 * (pow(spline_time, 3)) + (4 * pow(spline_time, 2)) + spline_time)*spline_five_x[(j + 2) % 5] +
					((pow(spline_time, 3) - (pow(spline_time, 2)))*spline_five_x[(j + 3) % 5])) / 2;
				Line->Line_shape[i][1] = (((pow(-spline_time, 3)) + (2 * pow(spline_time, 2)) - (spline_time))*spline_five_y[j % 5] +
					((3 * pow(spline_time, 3)) - 5 * (pow(spline_time, 2)) + 2)* spline_five_y[(j + 1) % 5] +
					(-3 * (pow(spline_time, 3)) + (4 * pow(spline_time, 2)) + spline_time)*spline_five_y[(j + 2) % 5] +
					((pow(spline_time, 3) - (pow(spline_time, 2)))*spline_five_y[(j + 3) % 5])) / 2;
			}
		}
		glutTimerFunc(fly_speed, Timerfunction, g_stop);
		glutPostRedisplay();
		break;
	case 3:
		break;
	}

}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'q' : //종료
	case 'Q':
		exit(0);
		glutPostRedisplay();
		break;
	case 'c':
	case 'C': // 도형 선 or 면
		g_Renderer->fill_line_shape = (g_Renderer->fill_line_shape + 1) % 2;
		glutPostRedisplay();
		break;
	case 'F': // 경로 출력 
	case 'f':
		button = (button + 1) % 2;
		if (button == 0)
		{
			Line->figure_shape = 999;
		}
		else
		{
			Line->figure_shape = 3;

		}
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		glutPostRedisplay();
		break;
	case 'y':
	case 'Y':
		glutPostRedisplay();
		break;
	case 'b':
	case 'B':
		glutPostRedisplay();
		break;
	case '+':
		if (fly_speed > 10)
		{
			fly_speed -= 1;
		}
		glutPostRedisplay();
		break;
	case '-':
		fly_speed += 1;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void SpecialKeyInput(int key, int x, int y)
{
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(g_WindowSizeX, g_WindowSizeY); // 윈도우 크기 설정
	glutCreateWindow("박진우_ComputerGraphics");
	srand(time(NULL));
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "GLEW 초기화 불가" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "GLEW 초기화 완료" << endl;
	}

	// Initialize Renderer
	g_Renderer = new Renderer(g_WindowSizeX, g_WindowSizeY);
	Line = new Renderer(g_WindowSizeX, g_WindowSizeY);
	slice_Line = new Renderer(g_WindowSizeX, g_WindowSizeY);
	Line->figure_shape = 3;
	slice_Line->figure_shape = 3;


	for (int i = 0; i < 100; i++)
	{
		spline_time = (i / 100.0f);
		spline_zero_one_x = ((1 - spline_time)*(spline_x_one))
			+ ((spline_time)*(spline_x_two));
		spline_zero_one_y = ((1 - spline_time)*(spline_y_one))
			+ ((spline_time)*(spline_y_two));


		spline_one_two_x = ((1 - spline_time)*(spline_x_two))
			+ ((spline_time)*(spline_x_tir));
		spline_one_two_y = ((1 - spline_time)*(spline_y_two))
			+ ((spline_time)*(spline_y_tir));


		Line->Line_shape[i][0] = ((1 - spline_time)*(spline_zero_one_x))
			+ ((spline_time)*(spline_one_two_x));
		Line->Line_shape[i][1] = ((1 - spline_time)*(spline_zero_one_y))
			+ ((spline_time)*(spline_one_two_y));
	}
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutTimerFunc(fly_speed, Timerfunction, g_stop);
	glutMotionFunc(Motion);
	glutMainLoop();
	delete g_Renderer , Line;

	return 0;
}

float convert_point_x(int x, float ox)
{
	int w = g_WindowSizeX;
	int h = g_WindowSizeY;
	ox = (float)(x - (float)w / 2.0)* (float)(1.0 / (float)(w / 2.0));
	return ox;
}
float convert_point_y(int y, float oy)
{
	int w = g_WindowSizeX;
	int h = g_WindowSizeY;
	oy = -(float)(y - (float)h / 2.0)* (float)(1.0 / (float)(h / 2.0));
	return  oy;
}
