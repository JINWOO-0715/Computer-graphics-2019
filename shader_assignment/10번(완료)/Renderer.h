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
	void Renderer::CreateVertexBufferObjects(GLuint& VAO, GLuint* VBO, GLuint& EBO);


	// 여기서부터 작성하고 집어넣을 것
private:

public:
	void DrawScene();

public:
	GLuint VAO_PR02, VBO_PR02[2] , EBO_PRO;
	unsigned int num;
	GLuint T_1_VAO_PR02, T_1_VBO_PR02[2];
	GLuint TriangleShader = 0;
	GLuint LineShader = 0;
	float angle_size = 1.0f;
	int shape_type = 1;
	int draw_type = 0;
	int shape=0;
	float move_size_x = 0.0f;
	float move_size_y = 0.0f;
	float move_size_z = 0.0f;
	int spin_sign = 0;

};

