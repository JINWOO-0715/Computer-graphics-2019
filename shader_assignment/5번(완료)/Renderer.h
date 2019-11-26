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


	// ���⼭���� �ۼ��ϰ� ������� ��
private:
	GLuint TriangleShader = 0;
public:
	void DrawScene();
public:
	int draw_mode = 0; 
	GLuint VAO_PR02, VBO_PR02[2];
	GLuint T_1_VAO_PR02, T_1_VBO_PR02[2];
	float circle_x, circle_y;
	float circle_radian = 0.1f;
	bool draw_sign = false;

};

