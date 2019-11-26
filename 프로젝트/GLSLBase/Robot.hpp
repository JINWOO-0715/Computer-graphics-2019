#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\ext.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
class Robot
{
public:
	Robot();
	void draw(GLint modelTransformLocation);
	void update(float);
	void changeXpos(float deltaX) { xVelocity += deltaX; }
	void changeYpos(float deltaY) { robotYpos += deltaY; }
	float retRobotXpos() { return robotXpos; }
	~Robot();
private:
	float robotXpos;
	float robotYpos;
	float robotZpos;
	unsigned int VAO[6];
	unsigned int VBO[6];
	unsigned int VBOC[6];
	float bodyRads;
	float xVelocity;
	bool isBodyUp;
	//팔이랑 다리가 들리고있는가

	glm::mat4 transMatrix;
	GLvoid initMatrix();
};