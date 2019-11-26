#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"

Renderer* g_Renderer = nullptr;
Renderer* T_Renderer = nullptr;
Renderer* line = nullptr;
size_t g_WindowSizeX = 800;
int g_stop = 0;
int g_stop_rotate = 0;
size_t g_WindowSizeY = 800;
int co = 0;
int k = 0;
float angle = 0.0f;
void DrawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	printf("%d , %d\n4 ", g_Renderer->shape, T_Renderer->shape);

	g_Renderer->DrawScene();
	T_Renderer->DrawScene();
	line->DrawScene();

	glutSwapBuffers();  // glFlush(); // 
}

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void MouseInput(int button, int state, int x, int y)
{

}

void Timerfunction(int value)
{
	switch (value)
	{
	case 1:
		g_Renderer->angle_size += 1.0f;
		glutPostRedisplay();
		glutTimerFunc(50, Timerfunction, g_stop);
		break;
	case 2:

		T_Renderer->angle_size_x += 1.0f;
		glutPostRedisplay();
		glutTimerFunc(50, Timerfunction, g_stop);
		break;
	case 3:
		k += 1;
		angle = k * 3.141592 / 180;
		g_Renderer->move_size_x =  0.5f * cos(angle);
		g_Renderer->move_size_z = 0.5f * sin(angle);
		T_Renderer->move_size_x =  0.5f * cos(angle);
		T_Renderer->move_size_z = 0.5f * -sin(angle);

		glutPostRedisplay();
		glutTimerFunc(50, Timerfunction, g_stop);

		break;
	}

}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 's' :
	case 'S':
		g_stop = 4;
		glutTimerFunc(50, Timerfunction, g_stop);
		glutPostRedisplay();
		glutPostRedisplay();
		break;
	case 'c':
	case 'C':
		g_Renderer->shape = (g_Renderer->shape+1)%2;
		T_Renderer->shape = (T_Renderer->shape+1)%2;
		glutPostRedisplay();
		break;
	case 'x':
	case 'X':
		g_stop= 2;
		glutTimerFunc(50, Timerfunction, g_stop);
		glutPostRedisplay();
		break;
	case 'h':
	case 'H':
		co++;
		co = co % 2;
		
		if (co == 1)
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			printf("%d", co);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
			printf("%d", co);
		}
		glutPostRedisplay();
		break;
	case 'y':
	case 'Y':
		g_stop = 1;
		glutTimerFunc(50, Timerfunction, g_stop);
		glutPostRedisplay();
		break;
	case 'b':
	case 'B':
		g_stop = 3;
		glutTimerFunc(50, Timerfunction, g_stop);
		glutPostRedisplay();
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
	T_Renderer = new Renderer(g_WindowSizeX, g_WindowSizeY);
	line = new Renderer(g_WindowSizeX, g_WindowSizeY);

	g_Renderer->shape = 1;
	T_Renderer->shape = 0;
	g_Renderer->transform_type = 1;
	T_Renderer->transform_type = 0;


	line->shape = 55;
	line->transform_type = 55;
	line->draw_line = true;

	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	delete T_Renderer;
	delete line;
	return 0;
}

