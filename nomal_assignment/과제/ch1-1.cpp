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

	glutInitWindowPosition(0, 0); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름)
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 디스플레이 모드 설정

	glutMainLoop();
}

// 윈도우 출력 함수
GLvoid drawScene(GLvoid)
{

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'R' | 'r':
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
		glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
		glFlush(); // 화면에 출력하기
		break;
	case 'G' | 'g':
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
		glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
		glFlush(); // 화면에 출력하기
		break;
	case 'B' | 'b':
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정
		glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
		glFlush(); // 화면에 출력하기
		break;

	case 'A' | 'a':
		rand_background();
		break;
	case 'W' | 'w':
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정
		glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
		glFlush(); // 화면에 출력하기
		break;
	case 'K' | 'k':
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 바탕색을 'blue' 로 지정
		glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
		glFlush(); // 화면에 출력하기
		break;
	case 'T' | 't':
		g_stop = 1;
		glutTimerFunc(1000, TimerFunction, g_stop);
		glFlush(); // 화면에 출력하기
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
	glClearColor((double)rand() / RAND_MAX, (double)rand() / RAND_MAX, (double)rand() / RAND_MAX, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	glFlush(); // 화면에 출력하기
}

void TimerFunction(int value)
{

	switch (value)
	{
	case 1:
		rand_background();
		glFlush(); // 화면에 출력하기
		glutTimerFunc(1000, TimerFunction, g_stop);
		break;
	case 2:
		break;
	}

}