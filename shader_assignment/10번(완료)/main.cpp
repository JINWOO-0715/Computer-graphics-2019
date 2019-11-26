#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"
#include <math.h>
Renderer* g_Renderer = nullptr;
int k = 0;
size_t g_WindowSizeX = 800;
size_t g_WindowSizeY = 800;
int co = 0;
int g_stop = 3;
int move_1 = 0;
int move_2 = 0;
float angle = 0.0f;
void DrawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// g_Renderer->
	
	g_Renderer->DrawScene();
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

void Timerfunction(int value)
{
	switch (value)
	{
	case 1:
		k += 1;
		angle = k * 3.141592 / 180;
		g_Renderer->move_size_x = 0.5f * cos(angle);
		g_Renderer->move_size_z = 0.5f * sin(angle);
		if (move_1 == 1)
		{
			g_Renderer->angle_size += 1.0f;
		}
		glutPostRedisplay();
		glutTimerFunc(50, Timerfunction, g_stop);
		break;
	case 2:
		g_Renderer->angle_size += 1.0f;	
		if (move_2 == 1)
		{
			k += 1;
			angle = k * 3.141592 / 180;
			g_Renderer->move_size_x = 0.5f * cos(angle);
			g_Renderer->move_size_z = 0.5f * sin(angle);
			
			
		}
		glutPostRedisplay();
		glutTimerFunc(50, Timerfunction, g_stop);
		break;
	case 3:
		g_Renderer->angle_size = 1.0f;
		g_Renderer->move_size_x = 0.0f;
		g_Renderer->move_size_y = 0.0f;
		g_Renderer->move_size_z = 0.0f;
		g_Renderer->spin_sign = 0;
		move_2 = 0;
		move_1 = 0;
		glutPostRedisplay();
		break;
	}

}

void KeyInput(unsigned char key, int x, int y)
{


	switch (key)
	{
	case 'q' :
	case 'Q':
		glutPostRedisplay();
		break;
	case 'c':
	case 'C':
		g_stop = 3;
		break;
	case 'r':
	case 'R':
		g_stop = 1;
		move_2 = (move_2 + 1) % 2;
		glutTimerFunc(10, Timerfunction, g_stop);
		break;
	case 'y':
	case 'Y':
		g_stop = 2;
		move_1 = (move_1 + 1) % 2;
		glutTimerFunc(100, Timerfunction, g_stop);

		break;
	case 'W':
	case 'w':
		g_Renderer->draw_type= (g_Renderer->draw_type + 1) % 2;
		glutPostRedisplay();
		break;
	case '1':
		g_Renderer->shape_type = 1;
		glutPostRedisplay();
		break;
	case '2':
		g_Renderer->shape_type = 2;
		glutPostRedisplay();
		break;
	case '3':
		g_Renderer->shape_type = 3;
		glutPostRedisplay();
		break;
	case '4':
		g_Renderer->shape_type = 4;
		glutPostRedisplay();
		break;
	case '5':
		g_Renderer->shape_type = 5;
		glutPostRedisplay();
		break;
	default:
		break;
	}
	printf("%d %d", move_1, move_2);
}

void SpecialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT)
	{
		g_Renderer->move_size_x += 0.05f;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_LEFT)
	{
		g_Renderer->move_size_x -= 0.05f;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_UP)
	{
		g_Renderer->move_size_y += 0.05f;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_DOWN)
	{
		g_Renderer->move_size_y -= 0.05f;
		glutPostRedisplay();
	}
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
	glutTimerFunc(10, Timerfunction, g_stop);
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

	return 0;
}

