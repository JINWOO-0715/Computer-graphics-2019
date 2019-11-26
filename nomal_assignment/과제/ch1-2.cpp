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

void main(int argc, char *argv[]) // 윈도우에서 처리하는느낌
{
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0); // 윈도우의 위치지정
	glutInitWindowSize(gwidth, gheight); // 윈도우의 크기 지정
	glutCreateWindow("Example2"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutMouseFunc(Mouse);
	glutReshapeFunc(Reshape);


	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 디스플레이 모드 설정
	glutMainLoop();
}


// 윈도우 출력 함수
GLvoid drawScene(GLvoid) //gl에서 변환하기 전에 처리 
{
	glClearColor(ground_r, ground_g, ground_b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	glFlush(); // 화면에 출력하기
	glColor3f(rect_r, rect_g, rect_b);
	glRectf(rect_l, rect_t, rect_bottom, rect_right);
	glFlush(); // 화면에 출력하기
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	gwidth = w;
	gheight = h;
}
void Mouse(int button, int state, int x, int y)
{
	// 윈도우 중점을 빼준다. 0.1이 맥스니까 1000을 곱한다. 

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