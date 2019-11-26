#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <gl/glew.h>
#include <gl/freeglut.h>

#include "glm\glm\glm.hpp"
#include "glm\glm\ext.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freeglut.lib")

using namespace std;

class Renderer
{
private:
	bool m_Initialized = false;

	size_t m_WindowSizeX = 0;
	size_t m_WindowSizeY = 0;

public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(const char* fileName, string* target);
	void AddShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType);
	GLuint CompileShaders(const char* vertexShaderFileName, const char* fragmentShaderFileName);
	void Renderer::CreateVertexBufferObjects(GLuint& VAO, GLuint* VBO);


	// 여기서부터 작성하고 집어넣을 것
private:

public:
	void DrawScene();

public:
	GLuint VAO_PR02, VBO_PR02[2];
	unsigned int num;
	GLuint T_1_VAO_PR02, T_1_VBO_PR02[8];
	GLuint TriangleShader = 0;
	int shape = 0;
	bool press_t = false;
	bool press_f = false;
	int line_type = 0;
	float angle_size = 0.0f;
	float angle_size_x = 0.0f;
	int projection_type = 1;
	int top_rectangle = 0;

	/*
	0, 3, 1, 3, 2, 1, // 뒤
		2, 6, 1, 6, 5, 1,// 오

		0, 1, 5, 4, 0, 5,// 밑
		6, 7, 5, 5, 7, 4,//   앞
		0, 4, 7, 3, 0, 7,//왼

		6, 3, 7, 6, 2, 3// 위 */

	const GLfloat Rectangle_shape[24][3] = {
	{-0.5f, -0.5f, -0.5f}, //0
	{-0.5f, 0.5f, -0.5f},//3
	{0.5f, -0.5f, -0.5f},//1

	{-0.5f, 0.5f, -0.5f},//3
	{0.5f, 0.5f, -0.5f},//2
	{0.5f, -0.5f, -0.5f},//1


	{0.5f, 0.5f, -0.5f},//2
	{0.5f, 0.5f, 0.5f},//6/
	{0.5f, -0.5f, -0.5f},//1

	{0.5f, 0.5f, 0.5f},//6/
	{0.5f, -0.5f, 0.5f},//5/
	{0.5f, -0.5f, -0.5f},//1

	{-0.5f, -0.5f, -0.5f}, //0
	{0.5f, -0.5f, -0.5f},//1
	{0.5f, -0.5f, 0.5f},//5/

	{-0.5f, -0.5f, 0.5f},//4
	{-0.5f, -0.5f, -0.5f}, //0
	{0.5f, -0.5f, 0.5f},//5/



	{-0.5f, -0.5f, -0.5f}, //0
	{-0.5f, -0.5f, 0.5f},//4
	{-0.5f, 0.5f, 0.5f},//7

	{-0.5f, 0.5f, -0.5f},//3
	{-0.5f, -0.5f, -0.5f}, //0
	{-0.5f, 0.5f, 0.5f},//7



	};
	const GLfloat Rectangle_top_shape[6][3] =
	{
	{0.5f, 0.5f, 0.5f},//6/
	{-0.5f, 0.5f, -0.5f},//3
	{-0.5f, 0.5f, 0.5f},//7

	{0.5f, 0.5f, 0.5f},//6/
	{0.5f, 0.5f, -0.5f},//2
	{-0.5f, 0.5f, -0.5f},//3
	};
	const GLfloat Rectangle_front_shape[6][3] =
	{
	{0.5f, 0.5f, 0.5f},//6/
	{ -0.5f, 0.5f, 0.5f },//7
	{ 0.5f, -0.5f, 0.5f },//5/

	{ 0.5f, -0.5f, 0.5f },//5/
	{ -0.5f, 0.5f, 0.5f },//7
	{ -0.5f, -0.5f, 0.5f },//4
	};


	const GLfloat Rectangle_color[36][3] = {
	{1.0f, 0.5f, 0.5f}, //0
	{1.0f, 0.5f, 0.5f},//3
	{1.0f, 0.5f, 0.5f},//1

	{1.0f, 0.5f, 0.5f} ,//3
	{1.0f, 0.5f, 0.5f},//2
	{1.0f, 0.5f, 0.5f},//1

	{0.5f, 0.5f, 1.0f},//2
	{0.5f, 0.5f, 1.0f},//6/
	{0.5f, 0.5f, 1.0f},//1

	{0.5f, 0.5f, 1.0f},//6/
	{0.5f, 0.5f, 1.0f},//5/
	{0.5f, 0.5f, 1.0f},//1

	{0.0f, 1.0f, 0.5f}, //0
	{0.0f, 1.0f, 0.5f},//1
	{0.0f, 1.0f, 0.5f},//5/

	{0.5f, 1.0f, 0.5f},//4
	{0.5f, 1.0f, 0.5f}, //0
	{0.5f, 1.0f, 0.5f},//5/

	{1.0f, 1.0f, 0.5f},//6/
	{1.0f, 1.0f, 0.5f},//7
	{1.0f, 1.0f, 0.5f},//5/

	{1.0f, 1.0f, 0.5f},//5/
	{1.0f, 1.0f, 0.5f},//7
	{1.0f, 1.0f, 0.5f},//4


	{0.0f, 1.0f, 0.1f}, //0
	{0.0f, 1.0f, 0.1f},//4
	{0.0f, 1.0f, 0.1f},//7

	{0.0f, 1.0f, 0.1f},//3
	{0.0f, 1.0f,0.1f}, //0
	{0.0f, 1.0f, 0.1f},//7

	{0.5f, 0.5f, 0.5f},//6/
	{0.5f, 0.5f, 0.5f},//3
	{0.5f, 0.5f, 0.5f},//7

	{0.5f, 0.5f, 0.5f},//6/
	{0.5f, 0.5f, 0.5f},//2
	{0.5f, 0.5f, 0.5f},//3
	};

	/*4,0,1,
4,3,2,

4,2,0,
4,1,3,

0,2,1,
2,3,1
*/
	const GLfloat Piramid_shape[18][3] = {
	{0.0f, 0.5f, 0.0f}, // 4
	{-0.5f, -0.5f, -0.5f}, // 0
	{-0.5f, -0.5f, 0.5f},// 1

	{0.0f, 0.5f, 0.0f}, // 4
	{0.5f, -0.5f, 0.5f},// 3
	{0.5f, -0.5f, -0.5f},// 2

	{0.0f, 0.5f, 0.0f}, // 4
	{0.5f, -0.5f, -0.5f},// 2
	{-0.5f, -0.5f, -0.5f}, // 0


	{0.0f, 0.5f, 0.0f}, // 4
	{-0.5f, -0.5f, 0.5f},// 1
	{0.5f, -0.5f, 0.5f},// 3

	{-0.5f, -0.5f, -0.5f}, // 0
	{0.5f, -0.5f, -0.5f},// 2
	{-0.5f, -0.5f, 0.5f},// 1


	{0.5f, -0.5f, -0.5f},// 2
	{0.5f, -0.5f, 0.5f},// 3
	{-0.5f, -0.5f, 0.5f},// 1
	};

	const GLfloat Piramid_color[18][3] = {
	{0.0f, 0.5f, 1.0f}, // 4
	{0.0f, 0.5f, 1.0f}, // 0
	{0.0f, 0.5f, 1.0f},// 1

	{1.0f, 0.5f, 0.0f},// 2
	{1.0f, 0.5f, 0.0f},// 3
	{1.0f, 0.5f, 0.0f}, // 4

	{0.5f, 0.0f, 1.0f}, // 4
	{0.5f, 0.0f, 1.0f},// 2
	{0.5f, 0.0f, 1.0f}, // 0


	{1.0f, 0.0f, 0.0f}, // 4c
	{1.0f, 0.0f, 0.0f},// 1
	{1.0f, 0.0f, 0.0f},// 3

	{0.0f, 0.0f, 1.0f}, // 0
	{0.0f, 0.0f, 1.0f},// 1
	{0.0f, 0.0f, 1.0f},// 2

	{0.0f,0.0f, 1.0f},// 2
	{0.0f, 0.0f, 1.0f},// 3
	{0.0f, 0.0f, 1.0f},// 1
	};
};

