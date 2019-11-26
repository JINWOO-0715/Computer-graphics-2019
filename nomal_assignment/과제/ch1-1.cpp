#include <GL/freeglut.h>
#include <gl/glut.h>
#include<time.h>
#include <stdio.h>
#include<stdlib.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void rand_background();
void TimerFunction(int value);

int g_stop = 0;

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("Example2"); // ������ ���� (������ �̸�)
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // ���÷��� ��� ����

	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'R' | 'r':
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // �������� 'blue' �� ����
		glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
		glFlush(); // ȭ�鿡 ����ϱ�
		break;
	case 'G' | 'g':
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // �������� 'blue' �� ����
		glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
		glFlush(); // ȭ�鿡 ����ϱ�
		break;
	case 'B' | 'b':
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� 'blue' �� ����
		glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
		glFlush(); // ȭ�鿡 ����ϱ�
		break;

	case 'A' | 'a':
		rand_background();
		break;
	case 'W' | 'w':
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // �������� 'blue' �� ����
		glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
		glFlush(); // ȭ�鿡 ����ϱ�
		break;
	case 'K' | 'k':
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'blue' �� ����
		glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
		glFlush(); // ȭ�鿡 ����ϱ�
		break;
	case 'T' | 't':
		g_stop = 1;
		glutTimerFunc(1000, TimerFunction, g_stop);
		glFlush(); // ȭ�鿡 ����ϱ�
		break;
	case 'S' | 's':

		g_stop = 2;
		glutTimerFunc(1000, TimerFunction, g_stop);

		glutKeyboardFunc(Keyboard);
		break;
	case 'Q' | 'q':
		exit(0);
		break;


	}

}
void rand_background()
{
	srand(time(NULL));
	glClearColor((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	glFlush(); // ȭ�鿡 ����ϱ�
}

void TimerFunction(int value)
{

	switch (value)
	{
	case 1:
		rand_background();
		glFlush(); // ȭ�鿡 ����ϱ�
		glutTimerFunc(1000, TimerFunction, g_stop);
		break;
	case 2:
		break;
	}

}