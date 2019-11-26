#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"
#include <time.h>
#include <stdlib.h>

Renderer* g_Renderer[10] = { nullptr, };

size_t g_WindowSizeX = 800;
size_t g_WindowSizeY = 800;
int g_stop = 1;

void Timerfunction(int value);
void DrawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	for (int i = 0; i < 10; i++)
	{
		g_Renderer[i]->DrawScene();
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

}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'q' :
	case 'Q':
		exit(0);
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
	glutSpecialFunc(SpecialKeyInput);
	glutTimerFunc(100, Timerfunction, g_stop);
	glutMainLoop();
	for (int i = 0; i < 10; i++)
	{
		delete g_Renderer;
	}


	return 0;
}

void Timerfunction(int value)
{
	switch (value)
	{
	case 1:
		for (int i = 0; i < 10; i++)
		{
			if(g_Renderer[i]->dir == 0)
			{
				g_Renderer[i]->Triangle_left_x -= g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_left_y += g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_top_x -= g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_top_y += g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_right_x -= g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_right_y += g_Renderer[i]->speed;


				if (g_Renderer[i]->Triangle_left_x<-0.95f)
				{
					g_Renderer[i]->Triangle_left_x = g_Renderer[i]->Triangle_top_x - 0.1f;
					g_Renderer[i]->Triangle_left_y = g_Renderer[i]->Triangle_top_y + 0.1f;
					g_Renderer[i]->Triangle_right_x = g_Renderer[i]->Triangle_top_x - 0.1f;
					g_Renderer[i]->Triangle_right_y = g_Renderer[i]->Triangle_top_y - 0.1f;
					g_Renderer[i]->dir = 1;
				}

			}
			if (g_Renderer[i]->dir == 1)
			{
				g_Renderer[i]->Triangle_left_x += g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_left_y += g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_top_x += g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_top_y += g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_right_x += g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_right_y += g_Renderer[i]->speed;

				if (g_Renderer[i]->Triangle_left_y > 0.95f)
				{
					g_Renderer[i]->Triangle_left_x = g_Renderer[i]->Triangle_top_x + 0.1f;
					g_Renderer[i]->Triangle_left_y = g_Renderer[i]->Triangle_top_y + 0.1f;
					g_Renderer[i]->Triangle_right_x = g_Renderer[i]->Triangle_top_x - 0.1f;
					g_Renderer[i]->Triangle_right_y = g_Renderer[i]->Triangle_top_y + 0.1f;
					g_Renderer[i]->dir = 2;
				}
			}
			if (g_Renderer[i]->dir == 2)
			{
				g_Renderer[i]->Triangle_left_x += g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_left_y -= g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_top_x += g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_top_y -= g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_right_x += g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_right_y -= g_Renderer[i]->speed;

				if (g_Renderer[i]->Triangle_left_x > 0.95f)
				{
					g_Renderer[i]->Triangle_left_x = g_Renderer[i]->Triangle_top_x + 0.1f;
					g_Renderer[i]->Triangle_left_y = g_Renderer[i]->Triangle_top_y - 0.1f;
					g_Renderer[i]->Triangle_right_x = g_Renderer[i]->Triangle_top_x + 0.1f;
					g_Renderer[i]->Triangle_right_y = g_Renderer[i]->Triangle_top_y + 0.1f;
					g_Renderer[i]->dir = 3;
				}

			}
			if (g_Renderer[i]->dir == 3)
			{
				g_Renderer[i]->Triangle_left_x -= g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_left_y -= g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_top_x -= g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_top_y -= g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_right_x -= g_Renderer[i]->speed;
				g_Renderer[i]->Triangle_right_y -= g_Renderer[i]->speed;
				if (g_Renderer[i]->Triangle_left_y < -0.95f)
				{
					g_Renderer[i]->Triangle_left_x = g_Renderer[i]->Triangle_top_x - 0.1f;
					g_Renderer[i]->Triangle_left_y = g_Renderer[i]->Triangle_top_y - 0.1f;
					g_Renderer[i]->Triangle_right_x = g_Renderer[i]->Triangle_top_x + 0.1f;
					g_Renderer[i]->Triangle_right_y = g_Renderer[i]->Triangle_top_y - 0.1f;
					g_Renderer[i]->dir = 0;
				}

			}

		}
		glutPostRedisplay(); // 다시 그리는 함수 
		break;

	}
	
	glutTimerFunc(50, Timerfunction, g_stop);
}