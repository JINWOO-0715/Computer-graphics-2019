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
	GLuint TriangleShader = 0;
public:
	void DrawScene();

public:
	GLuint VAO_PR02, VBO_PR02[2];
	int dir = rand() % 4;
	float Triangle_top_x;
	float Triangle_top_y;
	float Triangle_left_x;
	float Triangle_left_y;
	float Triangle_right_x;
	float Triangle_right_y;
	float speed = ((float)rand() / RAND_MAX)*0.05;
	void create_point();


	GLfloat colors[3][3] = {
		   { 1.0, 0.0, 0.0 }, // Red
		   { 1.0, 0.0, 0.0 }, // Green
		   { 1.0, 0.0, 0.0 } // Blue
	};


};

