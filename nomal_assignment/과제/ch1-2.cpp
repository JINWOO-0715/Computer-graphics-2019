#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include<gl/glut.h>
#include<stdio.h>
#include<time.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void TimerFunction(int value);

int gwidth = 800;
int gheight = 800;
float rect_r = 0.1f, rect_g = 0.34f, rect_b = 0.5f;
float rect_l = -0.2f, rect_t = -0.2f, rect_bottom = 0.2f, rect_right = 0.2f;
int _rect_l = 320, _rect_t = 320, _rect_b = 480, _rect_r = 480;

float ground_r = 0.6f, ground_g = 0.6f, ground_b = 0.0f;
void Mouse(int button, int state, int x, int y);

void main(int argc, char *argv[]) // �����쿡�� ó���ϴ´���
{
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0); // �������� ��ġ����
	glutInitWindowSize(gwidth, gheight); // �������� ũ�� ����
	glutCreateWindow("Example2"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // ���÷��� ��� ����
	glutMainLoop();
}


// ������ ��� �Լ�
GLvoid drawScene(GLvoid) //gl���� ��ȯ�ϱ� ���� ó�� 
{
	glClearColor(ground_r, ground_g, ground_b, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	glFlush(); // ȭ�鿡 ����ϱ�
	glColor3f(rect_r, rect_g, rect_b);
	glRectf(rect_l, rect_t, rect_bottom, rect_right);
	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	gwidth = w;
	gheight = h;
}
void Mouse(int button, int state, int x, int y)
{
	// ������ ������ ���ش�. 0.1�� �ƽ��ϱ� 1000�� ���Ѵ�. 

	printf("(%d),(%d)\n", x, y);
	printf("(%d),(%d)\n", _rect_l, _rect_t);


	if (x > 320 && x < 480 && y > 320 && y < 480)
	{

		rect_r = (double)rand() / RAND_MAX;
		rect_g = (double)rand() / RAND_MAX;
		rect_b = (double)rand() / RAND_MAX;


	}
	else
	{

		ground_r = (double)rand() / RAND_MAX;
		ground_g = (double)rand() / RAND_MAX;
		ground_b = (double)rand() / RAND_MAX;

	}

}