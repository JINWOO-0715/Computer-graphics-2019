#include "Robot.hpp"


float cube[] =
{
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,//¾Æ·§¸é
	-1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,1.0f,-1.0f,
	-1.0f,1.0f,1.0f,//¿ÞÂÊ¿·¸é
	1.0f,1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,-1.0f,//¿À¸¥ÂÊ¿·¸é
	-1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,1.0f,1.0f,
	-1.0f,1.0f,1.0f,//Á¤¸é
	-1.0f,1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,1.0f,-1.0f,
	-1.0f,1.0f,-1.0f,//µÞ¸é
	-1.0f,1.0f,-1.0f,
	-1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,-1.0f,
	-1.0f,1.0f,-1.0f//À­¸é

};
float color[6][108];

Robot::Robot()
{
	robotXpos = 0.0f;
	robotYpos = 0.0f;
	robotZpos = 5.0f;
	isBodyUp = true;
	bodyRads = 0.0f;
	xVelocity = 0.0f;
	transMatrix = glm::mat4(1.0f);
	for (int i = 0; i < 108; i += 3)
	{
		color[0][i] = 1.0f;
		color[0][i + 1] = 1.0f;
		color[0][i + 2] = 1.0f;
		//¸ö»ö
		color[1][i] = 1.0f;
		color[1][i + 1] = 0.0f;
		color[1][i + 2] = 0.0f;
		color[2][i] = 1.0f;
		color[2][i + 1] = 0.0f;
		color[2][i + 2] = 0.0f;
		//¾çÆÈ
		color[3][i] = 0.0f;
		color[3][i + 1] = 1.0f;
		color[3][i + 2] = 0.0f;
		color[4][i] = 0.0f;
		color[4][i + 1] = 1.0f;
		color[4][i + 2] = 0.0f;
		//¾ç´Ù¸®
		color[5][i] = 0.0f;
		color[5][i + 1] = 0.0f;
		color[5][i + 2] = 1.0f;
		//¸Ó¸®
		color[6][i] = 1.0f;
		color[6][i + 1] = 0.0f;
		color[6][i + 2] = 1.0f;
		//ÄÚ
	}
	//ÄÃ·¯°ª ÃÊ±âÈ­.
	glGenVertexArrays(6, VAO);
	glGenBuffers(6, VBO);
	glGenBuffers(6, VBOC);
	for (int i = 0; i < 6; ++i)
	{
		glBindVertexArray(VAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBOC[i]);

		glBufferData(GL_ARRAY_BUFFER, sizeof(color[i]), color[i], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
		glEnableVertexAttribArray(1);
	}
}

void Robot::draw(GLint modelTransformLocation)

{
	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos, robotYpos, robotZpos));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//¸öÅë
	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos - 1.5f, robotYpos, robotZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(0.5f, 1.0f, 0.5f));
	transMatrix = glm::rotate(transMatrix, glm::radians(bodyRads), glm::vec3(1.0f, 0.0f, 0.0f));

	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//¿ÞÆÈ

	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos + 1.5f, robotYpos, robotZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(0.5f, 1.0f, 0.5f));
	transMatrix = glm::rotate(transMatrix, glm::radians(-bodyRads), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glBindVertexArray(VAO[2]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//¿À¸¥ÆÈ

	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos - 0.5f, robotYpos - 2.0f, robotZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(0.5f, 1.0f, 0.5f));
	transMatrix = glm::rotate(transMatrix, glm::radians(-bodyRads), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glBindVertexArray(VAO[3]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//¿Þ´Ù¸®

	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos + 0.5f, robotYpos - 2.0f, robotZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(0.5f, 1.0f, 0.5f));
	transMatrix = glm::rotate(transMatrix, glm::radians(bodyRads), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glBindVertexArray(VAO[4]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	////¿À¸¥´Ù¸®

	initMatrix();
	transMatrix = glm::scale(transMatrix, glm::vec3(0.7f, 0.7f, 0.7f));
	transMatrix = glm::translate(transMatrix, glm::vec3(robotXpos + (robotXpos*0.5f), robotYpos + 2.5f, robotZpos + (robotZpos*0.5f)));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glBindVertexArray(VAO[5]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	////¸Ó¸®
}

void Robot::update(float velocity)
{
	if (isBodyUp)
	{
		bodyRads += velocity / 2.0f;
		if (bodyRads >= 45.0f)
			isBodyUp = false;
	}
	else
	{
		bodyRads -= velocity / 2.0f;
		if (bodyRads <= -45.0f)
			isBodyUp = true;
	}
	if (xVelocity > 0.0)
	{
		if (robotXpos <= 5.0f)
			robotXpos += xVelocity;
	}
	else
	{
		if (robotXpos >= -5.0f)
			robotXpos += xVelocity;
	}
}

void Robot::initMatrix()
{
	glLoadIdentity();
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			transMatrix[i][j] = 0.0f;
		}
	}
	transMatrix[0][0] = 1.0f;
	transMatrix[1][1] = 1.0f;
	transMatrix[2][2] = 1.0f;
	transMatrix[2][2] = 1.0f;
	transMatrix[3][3] = 1.0f;

}

Robot::~Robot()
{
	glDeleteBuffers(6, VBO);
	glDeleteBuffers(6, VBOC);
	glDeleteVertexArrays(6, VAO);
}