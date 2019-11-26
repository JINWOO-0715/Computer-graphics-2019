#include"States.hpp"
#include"Robot.hpp"
#include"Polygons.hpp"
#include "FrameWork.hpp"
#include <memory>
#include <vector>
#include <random>
using namespace std;

random_device rd;
default_random_engine dre(rd());
bernoulli_distribution bdForPolygonGeneration(0.4f);//bd means bernoilli_distribution �̰Ŵ� �ش� ��ġ�� ������ �������� ������(40%)Ȯ����
bernoulli_distribution bdForPolygonType(0.5f);//�̰Ŵ� 50%Ȯ���� �Ƕ�̵常���� ť�� ������ ���ϰ�� �Ƕ�̵� �ƴϸ� ť��


float cameraXpos = 0.0f;
float cameraYpos = 4.0f;
float cameraZpos = 10.0f;
float myPolygon_z[8] = { 0.0f, };
float myPolygon_x[8] = { 0.0f, };

float generationTimer = 0.0;

float velocity = 6.0f;
float gameTime = 0.0f;

bool isKeyDown = false;

unique_ptr<Robot> myRobot;
vector<unique_ptr<PolygonAbstractClass>> myPolygons;

void MainState::enter()
{
	myRobot = make_unique<Robot>();
}

void MainState::draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	auto viewMatrix = glm::mat4(1.0f);
	auto projectionMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::mat4(1.0f);
	auto modelTransformLocation = glGetUniformLocation(shaderProgramID, "transform");
	//��ǥ�� ��ȯ�� �κ�Ŭ������ draw���� ���� ����ȴ�.
	//ī�޶�� ������ �κ��� ������ ��ο��� ����ǹǷ� MainState���� �����Ѵ�.
	auto viewTransformLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	auto projectionTransformLocation = glGetUniformLocation(shaderProgramID, "projectionTransform");
	glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	//get location of uniform!

	auto eye = glm::vec3(cameraXpos, cameraYpos, cameraZpos);
	auto direction = glm::vec3(0.0f, 0.0f, -1.0f);

	direction = glm::normalize(direction);
	viewMatrix = glm::lookAt(eye, eye + direction, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	projectionMatrix = glm::perspective(glm::radians(120.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	//������� ī�޶�� ������ȯ ����.
	myRobot->draw(modelTransformLocation);
	for (int i = 0; i < myPolygons.size(); ++i)
		myPolygons[i]->draw(modelTransformLocation);
	//�̰��� ������ �׸��� �ڵ� ������ �ɰͰ����ϴ�.

	glutSwapBuffers();
}

void MainState::handleEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		if(!isKeyDown)
		myRobot->changeXpos(-1.0f), isKeyDown = true;
		break;
	case 'd':
		if(!isKeyDown)
		myRobot->changeXpos(1.0f), isKeyDown = true;
		break;
	default:
		break;
	}
}
void MainState::keyUpEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		if(isKeyDown)
		myRobot->changeXpos(+1.0f),isKeyDown=false;
		break;
	case 'd':
		if(isKeyDown)
		myRobot->changeXpos(-1.0f), isKeyDown = false;
		break;
	default:
		break;
	}
}
bool collide(float robot_z, float poloy_z , float robot_x , float poloy_x , float velocity )
{
	// x<0.5f  0.0
	velocity = velocity*0.1f;
	if (((robot_z - velocity) < poloy_z) && (robot_x <= -3) && (poloy_x < -3)) //����
	{
		printf(" %f %f %f %f \n ", robot_z, poloy_z, robot_x, poloy_x);
		printf(" �浹 \n");
	}
	if (((robot_z - velocity) < poloy_z) && (-3 < robot_x)&& (robot_x<=1) &&
		(-1 < poloy_x )&&(poloy_x < 2)) //�߾�
	{
		printf(" �浹 \n");
		printf(" %f %f %f %f \n ", robot_z, poloy_z, robot_x, poloy_x);
	}
	if (((robot_z - velocity) < poloy_z) && (1 < robot_x) && (2 < poloy_x))  // ������
	{
		printf(" �浹 \n");
	}


	return true;
}

void MainState::update()
{
	//�̰� ������Ʈ���� ������� ���ΰ��� �浹üũ�� �����Ͻø� �ɰͰ����ϴ�.

	myRobot->update(velocity);
	float myRobot_z = myRobot->retRobotZpos();
	float myRobot_x = myRobot->retRobotXpos();
	//printf(" %f \n ",myRobot->retRobotxpos());


	gameTime += 0.05;
	if (gameTime >= 2.0f)//����Ÿ���� 5.0�ʸ��� �ӵ��� 1.0�� �����Ѵ�.
	{
		velocity += 1.0f;
		gameTime = 0.0f;
	}
	for (int i = 0; i < myPolygons.size(); ++i)
	{
		//update�Լ� ȣ���ϸ鼭 ���� ���� ��ȯ�ϴ��� �˻��ϰ� true��ȯ�� ��ü�� ���ΰ����� �ڿ�
		//�ִٴ� ���̱⿡ ��ü�� �迭(����)���� �����Ѵ�.
	
		myPolygon_z[i] = myPolygons[i]->retPolygonZpos();	
		myPolygon_x[i] = myPolygons[i]->retPolygonXpos();
		collide(myRobot_z, myPolygon_z[i], myRobot_x, myPolygon_x[i]  , velocity);
		myPolygon_z[i] = 0.0f;
		myPolygon_x[i] = 0.0f;
		if (myPolygons[i]->update(velocity))
		{
			myPolygons.erase(myPolygons.begin() + i);
			//break;
		}
	}
	generationTimer += 0.05;
	if (generationTimer >= 1.5f)
	{
		generationTimer = 0.0f;
		int generationCount = 0;//�� ī��Ʈ�� 2�� �Ѿ�� ������ ����X �� ��� 1���⿣ ���� �ִ�.
		for (int i = 0; i < 3; ++i)
		{
			if (bdForPolygonGeneration(dre)&&generationCount<2)
			{
				++generationCount;
				if (bdForPolygonType(dre))
				{
					if(i==0) myPolygons.emplace_back(make_unique<Pyramid>(POLYGON_DIRECTION::LEFT));
					else if(i==1)myPolygons.emplace_back(make_unique<Pyramid>(POLYGON_DIRECTION::MIDDLE));
					else myPolygons.emplace_back(make_unique<Pyramid>(POLYGON_DIRECTION::RIGHT));

				}
				else
				{
					if (i == 0) myPolygons.emplace_back(make_unique<Cube>(POLYGON_DIRECTION::LEFT));
					else if (i == 1)myPolygons.emplace_back(make_unique<Cube>(POLYGON_DIRECTION::MIDDLE));
					else myPolygons.emplace_back(make_unique<Cube>(POLYGON_DIRECTION::RIGHT));
				}
			}
			else
			{
				//�̰��� ������ �����ϴ� �ڵ� �����ø� �ɰͰ����ϴ�.
			}
		}
	}
}

void MainState::exit()
{
	//��� ��ü �ı�
	//�ϴ� ����ũ ������ ���� �־ ���� �Ҵ����� �� �ʿ䰡X
	//�ڵ����� �Ҵ�������.
}
