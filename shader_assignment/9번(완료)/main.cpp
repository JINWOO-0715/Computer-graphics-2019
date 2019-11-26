#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"

Renderer* g_Renderer = nullptr;

size_t g_WindowSizeX = 800;
size_t g_WindowSizeY = 800;
int co = 0;
void DrawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g_Renderer->DrawScene();
	// g_Renderer->
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glEnd();

	glutSwapBuffers();  // glFlush(); // 
}
int g_stop = 0;
void Timerfunction(int value);
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
		glutPostRedisplay();
		break;
	case 'c':
	case 'C':
		g_Renderer->shape = 0;
		glutPostRedisplay();
		break;
	case 'p':
	case 'P':
		g_Renderer->shape = 1;
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
		g_stop = (g_stop + 1) % 2;
		glutTimerFunc(50, Timerfunction, g_stop);

		glutPostRedisplay();
		break;
	case 'W':
	case 'w':
		g_Renderer->line_type++;
		g_Renderer->line_type = g_Renderer->line_type %2;
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
	glutTimerFunc(10, Timerfunction, g_stop);
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

	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

	return 0;
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

	}

}
