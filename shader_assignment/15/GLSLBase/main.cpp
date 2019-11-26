#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"

Renderer* Rectangle_top_Renderer = nullptr;
Renderer* Rectangle_Renderer = nullptr;
Renderer* Rectangle_front_Renderer = nullptr;
size_t g_WindowSizeX = 800;
size_t g_WindowSizeY = 800;
void DrawScene(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	if (Rectangle_Renderer->shape== 0)
	{

		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_Renderer->VBO_PR02[0]);
		// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
		// triShape 배열의 사이즈: 9 * floatWDXW
		glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(GLfloat), Rectangle_Renderer->Rectangle_shape, GL_STATIC_DRAW);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_Renderer->VBO_PR02[1]);

		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(GLfloat), Rectangle_Renderer->Rectangle_color, GL_STATIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_Renderer->VBO_PR02[0]);
		// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
// triShape 배열의 사이즈: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 18 * 3 * sizeof(GLfloat), Rectangle_Renderer->Piramid_shape, GL_STATIC_DRAW);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_Renderer->VBO_PR02[1]);

		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 18 * 3 * sizeof(GLfloat), Rectangle_Renderer->Piramid_color, GL_STATIC_DRAW);
	}
	if (Rectangle_top_Renderer->shape == 0)
	{

		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_top_Renderer->VBO_PR02[0]);
		// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
		// triShape 배열의 사이즈: 9 * floatWDXW
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Rectangle_top_Renderer->Rectangle_top_shape, GL_STATIC_DRAW);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_top_Renderer->VBO_PR02[1]);
		
		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Rectangle_top_Renderer->Rectangle_color, GL_STATIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_top_Renderer->VBO_PR02[0]);
		// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
// triShape 배열의 사이즈: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 18 * 3 * sizeof(GLfloat), Rectangle_Renderer->Piramid_shape, GL_STATIC_DRAW);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_Renderer->VBO_PR02[1]);

		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 18 * 3 * sizeof(GLfloat), Rectangle_Renderer->Piramid_color, GL_STATIC_DRAW);
	}
	if (Rectangle_front_Renderer->shape == 0)
	{

		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_front_Renderer->VBO_PR02[0]);
		// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
		// triShape 배열의 사이즈: 9 * floatWDXW
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Rectangle_front_Renderer->Rectangle_front_shape, GL_STATIC_DRAW);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_front_Renderer->VBO_PR02[1]);

		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Rectangle_top_Renderer->Rectangle_color, GL_STATIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_front_Renderer->VBO_PR02[0]);
		// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
// triShape 배열의 사이즈: 9 * float
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Rectangle_front_Renderer->Piramid_shape, GL_STATIC_DRAW);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, Rectangle_Renderer->VBO_PR02[1]);

		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Rectangle_front_Renderer->Piramid_color, GL_STATIC_DRAW);
	}
	Rectangle_Renderer->DrawScene();
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
	Rectangle_top_Renderer->DrawScene();
	Rectangle_front_Renderer->DrawScene();
	// Rectangle_Renderer->


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

	case 't' :
	case 'T':
		Rectangle_Renderer->shape = 0;
		Rectangle_top_Renderer->press_t = true;
		g_stop = 2;

		glutTimerFunc(50, Timerfunction, g_stop);

		glutPostRedisplay();
	
		break;
	case 'f':
	case 'F':
		Rectangle_front_Renderer->press_f = true;
		g_stop = 3;

		glutTimerFunc(50, Timerfunction, g_stop);

		glutPostRedisplay();

		break;
	case 'c':
	case 'C':
		Rectangle_Renderer->shape = (Rectangle_Renderer->shape + 1) % 2;
		glutPostRedisplay();
		break;
	case 'y':
	case 'Y':
		g_stop = (g_stop+1)%2;
		glutTimerFunc(50, Timerfunction, g_stop);
		glutPostRedisplay();
		break;
	case 'O':
	case 'o':
		glutPostRedisplay();
		break;
	case 'P':
	case 'p':
		Rectangle_Renderer->projection_type = (Rectangle_Renderer->projection_type + 1) % 2;
		Rectangle_top_Renderer->projection_type = (Rectangle_top_Renderer->projection_type + 1) % 2;
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
	Rectangle_Renderer = new Renderer(g_WindowSizeX, g_WindowSizeY);
	Rectangle_top_Renderer = new Renderer(g_WindowSizeX, g_WindowSizeY);
	Rectangle_front_Renderer = new Renderer(g_WindowSizeX, g_WindowSizeY);
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete Rectangle_Renderer , Rectangle_top_Renderer , Rectangle_front_Renderer;

	return 0;
}

void Timerfunction(int value)
{
	switch (value)
	{
	case 3:
		Rectangle_front_Renderer->angle_size_x += 1.0f;
		glutPostRedisplay();
		glutTimerFunc(50, Timerfunction, g_stop);
		break;
	case 2:
		Rectangle_top_Renderer->angle_size_x +=1.0f;
		glutPostRedisplay();
		glutTimerFunc(50, Timerfunction, g_stop);
		break;
	case 1:
		Rectangle_Renderer->angle_size += 1.0f;
		Rectangle_top_Renderer->angle_size += 1.0f;
		Rectangle_front_Renderer->angle_size += 1.0f;
		glutPostRedisplay();
		glutTimerFunc(50, Timerfunction, g_stop);
		break;

	}

}
