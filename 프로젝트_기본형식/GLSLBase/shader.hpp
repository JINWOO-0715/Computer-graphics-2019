#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\ext.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
#include <iostream>
#include <fstream>
class Shader
{
public:
	Shader() = default;
	virtual GLint createAndCompile() = 0;
	virtual GLuint retShader() = 0;
	virtual ~Shader() = default;
};