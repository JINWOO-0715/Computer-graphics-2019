#include "Polygons.hpp"

using namespace std;

float cubeCoords[] =
{
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,//아랫면
	-1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,1.0f,-1.0f,
	-1.0f,1.0f,1.0f,//왼쪽옆면
	1.0f,1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,-1.0f,//오른쪽옆면
	-1.0f,1.0f,1.0f,
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,1.0f,1.0f,
	-1.0f,1.0f,1.0f,//정면
	-1.0f,1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,1.0f,-1.0f,
	-1.0f,1.0f,-1.0f,//뒷면
	-1.0f,1.0f,-1.0f,
	-1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,
	1.0f,1.0f,-1.0f,
	-1.0f,1.0f,-1.0f//윗면

};


float pyramidCoords[] =
{
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,//여기까지 밑면
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	0.0f,1.0f,0.0f,//여기까지 앞면
	-1.0f,-1.0f,1.0f,
	1.0f,-1.0f,1.0f,
	0.0f,1.0f,0.0f,//여기까지 뒷면
	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,1.0f,
	0.0f,1.0f,0.0f,//여기까지 오른면
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,1.0f,
	0.0f,1.0f,0.0f,//여기까지 왼면

};

float cubeColor[] =
{
	 0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f

};
float pyramidColor[] =
{
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
};

Pyramid::Pyramid(POLYGON_DIRECTION initDirection)
{
	if (initDirection == POLYGON_DIRECTION::LEFT)
		pyramidXpos = -5.0f;
	else if (initDirection == POLYGON_DIRECTION::MIDDLE)
		pyramidXpos = 0.0f;
	else pyramidXpos = 5.0f;
	pyramidYpos = 0.0f;
	pyramidZpos = -15.0f;
	rads = 0.0f;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBOC);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidCoords), pyramidCoords, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBOC);

	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidColor), pyramidColor, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(1);
}
void Pyramid::draw(GLint modelTransformLocation)
{
	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(pyramidXpos, pyramidYpos, pyramidZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(1.0f, 2.0f, 1.0f));
	transMatrix = glm::rotate(transMatrix, glm::radians(rads), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0,18);
}
bool Pyramid::update(float velocity)
{
	rads += velocity / 2.0f;
	pyramidZpos += 0.05f*velocity;
	if (pyramidZpos >= 6.0f)
		return true;
	return false;
}
Pyramid::~Pyramid()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Pyramid::initMatrix()
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

Cube::Cube(POLYGON_DIRECTION initDirection)
{
	if (initDirection == POLYGON_DIRECTION::LEFT)
		cubeXpos = -5.0f;
	else if (initDirection == POLYGON_DIRECTION::MIDDLE)
		cubeXpos = 0.0f;
	else cubeXpos = 5.0f;
	cubeYpos = 0.0f;
	cubeZpos = -15.0f;
	rads = 0.0f;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBOC);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeCoords), cubeCoords, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBOC);

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColor), cubeColor, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(1);
}
void Cube::draw(GLint modelTransformLocation)
{
	initMatrix();
	transMatrix = glm::translate(transMatrix, glm::vec3(cubeXpos, cubeYpos, cubeZpos));
	transMatrix = glm::scale(transMatrix, glm::vec3(1.0f, 2.0f, 1.0f));
	transMatrix = glm::rotate(transMatrix, glm::radians(rads), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
bool Cube::update(float velocity)
{
	rads += velocity / 2.0f;
	cubeZpos += 0.05f*velocity;
	if (cubeZpos >= 6.0f)
		return true;
	return false;
}
Cube::~Cube()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}
void Cube::initMatrix()
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