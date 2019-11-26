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
	GLuint L_VAO_PR02, L_VBO_PR02[2];
	GLuint TriangleShader = 0;
	GLuint LineShader = 0;
	GLfloat top_point_x = 1.2f;
	GLfloat top_point_y = 1.2f;
	int figure_shape = 1;
	int fill_line_shape = 1;

	GLfloat Line_shape[100][3] = {
		0,
	};
	GLfloat Line_color[100][3] = {
		0.7f,

	};

};

