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
	void CreateVertexBufferObjects(GLuint& VAO, GLuint* VBO);


	// 여기서부터 작성하고 집어넣을 것
private:

public:
	void DrawScene();

public:
	GLuint T1_TriangleShader = 0;
	GLuint T2_TriangleShader = 0;
	GLuint T3_TriangleShader = 0;
	GLuint T4_TriangleShader = 0;
	int draw_mode = 1;
	GLuint T_1_VAO_PR02, T_1_VBO_PR02[2];
	GLuint T_2_VAO_PR02, T_2_VBO_PR02[2];
	GLuint T_3_VAO_PR02, T_3_VBO_PR02[2];
	GLuint T_4_VAO_PR02, T_4_VBO_PR02[2];


};

