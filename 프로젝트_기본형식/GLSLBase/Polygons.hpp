#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\ext.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
enum class POLYGON_DIRECTION
{
	LEFT,
	RIGHT,
	MIDDLE
};
//폴리곤이 생성되는 위치 길이 3방향 있다 왼쪽, 오른쪽, 가운데 
class PolygonAbstractClass
{
public:
	virtual void draw(GLint modelTransformLocation)=0;
	virtual bool update(float)=0;
	virtual 	float retPolygonZpos() { return NULL; };
	virtual 	float retPolygonXpos() { return NULL; };

	//update 함수에서 z값을 계속 감소시키다가 특정 z값에 도달하면 return true(객체가 사라짐.)
	//추가적으로 rads도 증가시킴!!
};

class Pyramid:public PolygonAbstractClass
{
public:
	Pyramid(POLYGON_DIRECTION initDirection);
	virtual void draw(GLint modelTransformLocation) override;
	virtual bool update(float)override;
	float retPolygonZpos() { return pyramidZpos;};
	float retPolygonXpos() { return pyramidXpos; };
	~Pyramid();
private:
	float pyramidXpos;
	float pyramidYpos;
	float pyramidZpos;
	float rads;//rads각도만큼 폴리곤이 y축기준으로 회전한다.
	unsigned int VAO, VBO, VBOC;
	glm::mat4 transMatrix;
	GLvoid initMatrix();
};

class Cube:public PolygonAbstractClass
{
public:
	Cube(POLYGON_DIRECTION initDirection);
	virtual void draw(GLint modelTransformLocation) override;
	virtual bool update(float)override;
	float retPolygonZpos() { return cubeZpos; };
	float retPolygonXpos() { return cubeXpos; };
	~Cube();
private:
	float cubeXpos;
	float cubeYpos;
	float cubeZpos;
	float rads;
	unsigned int VAO, VBO, VBOC;
	glm::mat4 transMatrix;
	GLvoid initMatrix();
};