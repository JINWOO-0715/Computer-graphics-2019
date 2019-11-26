#include "stdafx.h"

#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"


Renderer* g_Renderer = nullptr;

size_t g_WindowSizeX = 800;
size_t g_WindowSizeY = 800;
float T1_p1_x = 0.4f, T1_p1_y = 0.4f;
float T1_p2_x = 0.2f, T1_p2_y = 0.1f;
float T1_p3_x = 0.6f, T1_p3_y = 0.1f;

float T2_p1_x = -0.4f, T2_p1_y = 0.4f;
float T2_p2_x = -0.2f, T2_p2_y = 0.1f;
float T2_p3_x = -0.6f, T2_p3_y = 0.1f;

float T3_p1_x = -0.4f, T3_p1_y = -0.1f;
float T3_p2_x = -0.2f, T3_p2_y = -0.4f;
float T3_p3_x = -0.6f, T3_p3_y = -0.4f;

float T4_p1_x = 0.4f, T4_p1_y = -0.1f;
float T4_p2_x = 0.2f, T4_p2_y = -0.4f;
float T4_p3_x = 0.6f, T4_p3_y = -0.4f;

//색상
float T1_p1_r = 0.4f, T1_p1_g = 0.4f, T1_p1_b = 0.4f;
float T1_p2_r = 0.2f, T1_p2_g = 0.1f, T1_p2_b = 0.4f;
float T1_p3_r = 0.6f, T1_p3_g = 0.4f, T1_p3_b = 0.4f;

float T2_p1_r = 0.4f, T2_p1_g = 0.4f, T2_p1_b = 0.4f;
float T2_p2_r = 0.2f, T2_p2_g = 0.6f, T2_p2_b = 0.4f;
float T2_p3_r = 0.6f, T2_p3_g = 0.2f, T2_p3_b = 0.7f;

float T3_p1_r = 0.4f, T3_p1_g = 0.3f, T3_p1_b = 0.4f;
float T3_p2_r = 0.2f, T3_p2_g = 0.2f, T3_p2_b = 0.5f;
float T3_p3_r = 0.6f, T3_p3_g = 0.4f, T3_p3_b = 0.4f;

float T4_p1_r = 0.4f, T4_p1_g = 0.7f, T4_p1_b = 0.4f;
float T4_p2_r = 0.2f, T4_p2_g = 0.4f, T4_p2_b = 0.4f;
float T4_p3_r = 0.6f, T4_p3_g = 0.4f, T4_p3_b = 0.4f;

float convert_point_x(int x, float ox);
float convert_point_y(int x, float oy);
int cou(1);
int dir(0);

float tmp_x;
float tmp_y;
int g_stop(0);
float dir_size = 0.0f;
void DrawScene(void)
{


	GLfloat T_1_triShape[3][3] = {
 {T1_p1_x, T1_p1_y, 0.0f },
{ T1_p2_x, T1_p2_y, 0.0f },
{ T1_p3_x, T1_p3_y, 0.0f}
	};
	GLfloat T_2_triShape[3][3] = {
  { T2_p1_x, T2_p1_y, 0.0f }, // Red
  { T2_p2_x, T2_p2_y, 0.0f }, // Green
  { T2_p3_x, T2_p3_y, 0.0f} // Blue
	};
	GLfloat T_3_triShape[3][3] = {
  { T3_p1_x, T3_p1_y, 0.0f }, // Red
  { T3_p2_x, T3_p2_y, 0.0f }, // Green
  { T3_p3_x, T3_p3_y, 0.0f} // Blue
	};
	GLfloat T_4_triShape[3][3] = {
	  { T4_p1_x, T4_p1_y, 0.0f }, // Red
	  { T4_p2_x, T4_p2_y, 0.0f }, // Green
	  { T4_p3_x, T4_p3_y, 0.0f} // Blue
	};





	GLfloat T_1_colors[3][3] = {
		   { T1_p1_r, T1_p1_g, T1_p1_b }, // Red
		   { T1_p2_r, T1_p2_g, T1_p2_b }, // Green
		   { T1_p3_r, T1_p3_g, T1_p3_b } // Blue
	};
	GLfloat T_2_colors[3][3] = {
			 { T2_p1_r, T2_p1_g, T2_p1_b }, // Red
		   { T2_p2_r, T2_p2_g, T2_p2_b }, // Green
		   { T2_p3_r, T2_p3_g, T2_p3_b } // Blue
	};


	GLfloat T_3_colors[3][3] = {
			  { T3_p1_r, T3_p1_g, T3_p1_b }, // Red
		   { T3_p2_r, T3_p2_g, T3_p2_b }, // Green
		   { T3_p3_r, T3_p3_g, T3_p3_b } // Blue
	};



	GLfloat T_4_colors[3][3] = {
		   { T4_p1_r, T4_p1_g, T4_p1_b }, // Red
		   { T4_p2_r, T4_p2_g, T4_p2_b }, // Green
		   { T4_p3_r, T4_p3_g, T4_p3_b } // Blue
	};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, g_Renderer->T_1_VBO_PR02[0]);

	// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
	// triShape 배열의 사이즈: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), T_1_triShape, GL_STATIC_DRAW);

	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, g_Renderer->T_1_VBO_PR02[1]);

	// 변수 colors에서 버텍스 색상을 복사한다.
	// colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), T_1_colors, GL_STATIC_DRAW);


	//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, g_Renderer->T_2_VBO_PR02[0]);

	// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
	// triShape 배열의 사이즈: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), T_2_triShape, GL_STATIC_DRAW);

	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, g_Renderer->T_2_VBO_PR02[1]);

	// 변수 colors에서 버텍스 색상을 복사한다.
	// colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), T_2_colors, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, g_Renderer->T_3_VBO_PR02[0]);

	// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
	// triShape 배열의 사이즈: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), T_3_triShape, GL_STATIC_DRAW);

	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, g_Renderer->T_3_VBO_PR02[1]);

	// 변수 colors에서 버텍스 색상을 복사한다.
	// colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), T_3_colors, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, g_Renderer->T_4_VBO_PR02[0]);

	// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
	// triShape 배열의 사이즈: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), T_4_triShape, GL_STATIC_DRAW);

	//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, g_Renderer->T_4_VBO_PR02[1]);

	// 변수 colors에서 버텍스 색상을 복사한다.
	// colors 배열의 사이즈: 9 *float
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), T_4_colors, GL_STATIC_DRAW);
	g_Renderer->DrawScene();
	// g_Renderer->


	glutSwapBuffers();  // glFlush(); // 
}

void Timerfunction(int value)
{
	switch (value)
	{

	case 1:

		T1_p1_x += 0.01f;
		T1_p2_x += 0.01f;
		T1_p3_x += 0.01f;

		T2_p1_x += 0.01f;
		T2_p2_x += 0.01f;
		T2_p3_x += 0.01f;


		T3_p1_x += 0.01f;
		T3_p2_x += 0.01f;
		T3_p3_x += 0.01f;


		T4_p1_x += 0.01f;
		T4_p2_x += 0.01f;
		T4_p3_x += 0.01f;
		dir_size += 0.001f;
		glutPostRedisplay();
		if (dir_size >= 0.03f)
		{
			g_stop = 2;
			dir_size = 0.0f;
		}
		else if (g_stop == 0)
		{
			break;
		}
		else
		{
			g_stop = 1;

		}
		glutTimerFunc(10, Timerfunction, g_stop);
		break;
	case 2:
		T1_p1_y += 0.01f;
		T1_p2_y += 0.01f;
		T1_p3_y += 0.01f;

		T2_p1_y += 0.01f;
		T2_p2_y += 0.01f;
		T2_p3_y += 0.01f;

		T3_p1_y += 0.01f;
		T3_p2_y += 0.01f;
		T3_p3_y += 0.01f;

		T4_p1_y += 0.01f;
		T4_p2_y += 0.01f;
		T4_p3_y += 0.01f;
		dir_size += 0.001f;
		glutPostRedisplay();
		if (dir_size >= 0.03f)
		{
			g_stop = 3;
			dir_size = 0.0f;
		}
		else if (g_stop == 0)
		{
			break;
		}
		else
		{
			g_stop = 2;

		}
		glutTimerFunc(10, Timerfunction, g_stop);
		break;
	case 3:
		T1_p1_x -= 0.01f;
		T1_p2_x -= 0.01f;
		T1_p3_x -= 0.01f;

		T2_p1_x -= 0.01f;
		T2_p2_x -= 0.01f;
		T2_p3_x -= 0.01f;

		T3_p1_x -= 0.01f;
		T3_p2_x -= 0.01f;
		T3_p3_x -= 0.01f;

		T4_p1_x -= 0.01f;
		T4_p2_x -= 0.01f;
		T4_p3_x -= 0.01f;
		dir_size += 0.001f;
		glutPostRedisplay();
		if (dir_size >= 0.03f)
		{
			g_stop = 4;
			dir_size = 0.0f;
		}
		else if (g_stop == 0)
		{
			break;
		}
		else
		{
			g_stop = 3;

		}
		glutTimerFunc(10, Timerfunction, g_stop);
		break;
	case 4:
		T1_p1_y -= 0.01f;
		T1_p2_y -= 0.01f;
		T1_p3_y -= 0.01f;

		T2_p1_y -= 0.01f;
		T2_p2_y -= 0.01f;
		T2_p3_y -= 0.01f;

		T3_p1_y -= 0.01f;
		T3_p2_y -= 0.01f;
		T3_p3_y -= 0.01f;

		T4_p1_y -= 0.01f;
		T4_p2_y -= 0.01f;
		T4_p3_y -= 0.01f;
		dir_size += 0.001f;
		glutPostRedisplay();
		if (dir_size >= 0.03f)
		{
			g_stop = 1;
			dir_size = 0.0f;
		}
		else if (g_stop == 0)
		{
			break;
		}
		else
		{
			g_stop = 4;

		}
		glutTimerFunc(10, Timerfunction, g_stop);
		break;
		
	case 0:
		break;
	}
	
	

}
void Timerfunction_2(int value) {

}
void SpecialKeyInput(int key, int x, int y)
{
}
void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

void MouseInput(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (cou == 1)
		{
			T1_p1_x = convert_point_x(x, tmp_x);
			T1_p1_y = convert_point_y(y, tmp_y);
			T1_p2_x = convert_point_x(x, tmp_x) + 0.2f;
			T1_p2_y = convert_point_y(y, tmp_y) - 0.3f;
			T1_p3_x = convert_point_x(x, tmp_x) - 0.2f;
			T1_p3_y = convert_point_y(y, tmp_y) - 0.3f;

		}
		//t1
		if (cou == 2)
		{
			T2_p1_x = convert_point_x(x, tmp_x);
			T2_p1_y = convert_point_y(y, tmp_y);
			T2_p2_x = convert_point_x(x, tmp_x) + 0.2f;
			T2_p2_y = convert_point_y(y, tmp_y) - 0.3f;
			T2_p3_x = convert_point_x(x, tmp_x) - 0.2f;
			T2_p3_y = convert_point_y(y, tmp_y) - 0.3f;

		}
		//t2

		if (cou == 3)
		{
			T3_p1_x = convert_point_x(x, tmp_x);
			T3_p1_y = convert_point_y(y, tmp_y);
			T3_p2_x = convert_point_x(x, tmp_x) + 0.2f;
			T3_p2_y = convert_point_y(y, tmp_y) - 0.3f;
			T3_p3_x = convert_point_x(x, tmp_x) - 0.2f;
			T3_p3_y = convert_point_y(y, tmp_y) - 0.3f;


		}

		if (cou == 4)
		{
			T4_p1_x = convert_point_x(x, tmp_x);
			T4_p1_y = convert_point_y(y, tmp_y);
			T4_p2_x = convert_point_x(x, tmp_x) - 0.2f;
			T4_p2_y = convert_point_y(y, tmp_y) - 0.3f;
			T4_p3_x = convert_point_x(x, tmp_x) + 0.2f;
			T4_p3_y = convert_point_y(y, tmp_y) - 0.3f;
		}



		glutPostRedisplay(); // 다시 그리는 함수 
		cou++;
		if (cou == 5)
		{
			cou = 1;
		}

	}

}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'q':
	case 'Q':
		exit(0);
		break;
	case 'm':
	case 'M':
		g_stop = 1;
		glutTimerFunc(100, Timerfunction, g_stop);
		glFlush(); // 화면에 출력하기
		break;
	case 's':
	case 'S':
		g_stop = 0;
		glutTimerFunc(100, Timerfunction, g_stop);
		glFlush(); // 화면에 출력하기
		break;
	case 'c':
	case 'C':
		T1_p1_r = (double)rand() / RAND_MAX, T1_p1_g = (double)rand() / RAND_MAX, T1_p1_b = (double)rand() / RAND_MAX;
		T1_p2_r = (double)rand() / RAND_MAX, T1_p2_g = (double)rand() / RAND_MAX, T1_p2_b = (double)rand() / RAND_MAX;
		T1_p3_r = (double)rand() / RAND_MAX, T1_p3_g = (double)rand() / RAND_MAX, T1_p3_b = (double)rand() / RAND_MAX;

		T2_p1_r = (double)rand() / RAND_MAX, T2_p1_g = (double)rand() / RAND_MAX, T2_p1_b = (double)rand() / RAND_MAX;
		T2_p2_r = (double)rand() / RAND_MAX, T2_p2_g = (double)rand() / RAND_MAX, T2_p2_b = (double)rand() / RAND_MAX;
		T2_p3_r = (double)rand() / RAND_MAX, T2_p3_g = (double)rand() / RAND_MAX, T2_p3_b = (double)rand() / RAND_MAX;

		T3_p1_r = (double)rand() / RAND_MAX, T3_p1_g = (double)rand() / RAND_MAX, T3_p1_b = (double)rand() / RAND_MAX;
		T3_p2_r = (double)rand() / RAND_MAX, T3_p2_g = (double)rand() / RAND_MAX, T3_p2_b = (double)rand() / RAND_MAX;
		T3_p3_r = (double)rand() / RAND_MAX, T3_p3_g = (double)rand() / RAND_MAX, T3_p3_b = (double)rand() / RAND_MAX;

		T4_p1_r = (double)rand() / RAND_MAX, T4_p1_g = (double)rand() / RAND_MAX, T4_p1_b = (double)rand() / RAND_MAX;
		T4_p2_r = (double)rand() / RAND_MAX, T4_p2_g = (double)rand() / RAND_MAX, T4_p2_b = (double)rand() / RAND_MAX;
		T4_p3_r = (double)rand() / RAND_MAX, T4_p3_g = (double)rand() / RAND_MAX, T4_p3_b = (double)rand() / RAND_MAX;
		glutPostRedisplay(); // 다시 그리는 함수 

		break;
	case 'f':
	case 'F':
		g_Renderer->draw_mode += 1;
		if (g_Renderer->draw_mode == 2)
		{
			g_Renderer->draw_mode = 0;
		}
		glutPostRedisplay(); // 다시 그리는 함수 
		break;
	
	default:
		break;
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

	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;

	return 0;
}

float convert_point_x(int x, float ox)
{
	int w = g_WindowSizeX;
	int h = g_WindowSizeY;
	ox = (float)(x - (float)w / 2.0)* (float)(1.0 / (float)(w / 2.0));
	return ox;
}
float convert_point_y(int y, float oy)
{
	int w = g_WindowSizeX;
	int h = g_WindowSizeY;
	oy = -(float)(y - (float)h / 2.0)* (float)(1.0 / (float)(h / 2.0));
	return  oy;
}
