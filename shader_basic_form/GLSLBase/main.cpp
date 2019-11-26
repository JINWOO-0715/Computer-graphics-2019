#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"

Renderer* g_Renderer = nullptr;

size_t g_WindowSizeX = 800;
size_t g_WindowSizeY = 800;

void DrawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(g_WindowSizeX, g_WindowSizeY); // ������ ũ�� ����
	glutCreateWindow("������_ComputerGraphics");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "GLEW �ʱ�ȭ �Ұ�" << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		cout << "GLEW �ʱ�ȭ �Ϸ�" << endl;
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

