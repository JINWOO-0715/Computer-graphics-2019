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
//�������� �����Ǵ� ��ġ ���� 3���� �ִ� ����, ������, ��� 
class PolygonAbstractClass
{
public:
	virtual void draw(GLint modelTransformLocation)=0;
	virtual bool update(float)=0;
	//update �Լ����� z���� ��� ���ҽ�Ű�ٰ� Ư�� z���� �����ϸ� return true(��ü�� �����.)
	//�߰������� rads�� ������Ŵ!!
};

class Pyramid:public PolygonAbstractClass
{
public:
	Pyramid(POLYGON_DIRECTION initDirection);
	virtual void draw(GLint modelTransformLocation) override;
	virtual bool update(float)override;
	~Pyramid();
private:
	float pyramidXpos;
	float pyramidYpos;
	float pyramidZpos;
	float rads;//rads������ŭ �������� y��������� ȸ���Ѵ�.
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