#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"

Renderer* g_Renderer[10] = { nullptr, };

size_t g_WindowSizeX = 800;
size_t g_WindowSizeY = 800;
float m_x;
float m_y;
int g_stop(0);
int mouse_count = 0;
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

void Timerfunction(int value);

void DrawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < 10; i++)
	{
		if (g_Renderer[i]->draw_sign == true)
		{
			g_Renderer[i]->DrawScene();
		}
	}
	// g_Renderer->

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
		g_Renderer[mouse_count]->draw_sign = true;
		g_Renderer[mouse_count]->circle_x = convert_point_x(x, m_x);
	    g_Renderer[mouse_count]->circle_y= convert_point_y(y, m_y);
		g_stop = 1;
		for (int i = 0; i < 20; i++)
		{
			printf("%f \n", g_Renderer[mouse_count]->circle_y);

		}
		mouse_count++;
		if (mouse_count == 10)
		{
			mouse_count = 0;
		}
		glutPostRedisplay(); // 다시 그리는 함수 
	}
}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		for (int i = 0; i < 10; i++)
		{
			g_Renderer[i]->draw_mode = 0;
			glutPostRedisplay(); // 다시 그리는 함수 
		}
	
		break;
	case '2':
		for (int i = 0; i < 10; i++)
		{
			g_Renderer[i]->draw_mode = 1;
			glutPostRedisplay(); // 다시 그리는 함수 
		}
	
		break;
	case 'q' :
	case 'Q':
		exit(0);
		break;
	default:
		break;
	}
}

void Timerfunction(int value)
{
	switch (value)
	{
	case 1:
		for (int i = 0; i < 10; i++)
		{
			if ((g_Renderer[i]->draw_sign == true) && (g_Renderer[i]->circle_radian < 0.6f))
			{
				g_Renderer[i]->circle_radian += 0.01f;
				glutPostRedisplay(); // 다시 그리는 함수 
			}
			if (g_Renderer[i]->circle_radian > 0.59f)
			{
				g_Renderer[i]->draw_sign = false;
				g_Renderer[i]->circle_radian = 0.0f;

			}

			
		}
	
	
		break;

	}
	glutTimerFunc(10, Timerfunction, g_stop);
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
	for (int i = 0; i < 10; i++)
	{
		g_Renderer[i] = new Renderer(g_WindowSizeX, g_WindowSizeY);

	}


	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutTimerFunc(100, Timerfunction, g_stop);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();
	for (int i = 0; i < 10; i++)
	{
		delete g_Renderer[i];

	}
	


	return 0;
}

