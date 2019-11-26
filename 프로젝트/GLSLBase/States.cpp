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
bernoulli_distribution bdForPolygonGeneration(0.4f);//bd means bernoilli_distribution 이거는 해당 위치에 폴리곤 생성할지 안할지(40%)확률로
bernoulli_distribution bdForPolygonType(0.5f);//이거는 50%확률로 피라미드만들지 큐브 만들지 참일경우 피라미드 아니면 큐브


float cameraXpos = 0.0f;
float cameraYpos = 4.0f;
float cameraZpos = 10.0f;

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
	//좌표계 변환은 로봇클래스의 draw에서 직접 적용된다.
	//카메라와 투영은 로봇과 폴리곤 모두에게 적용되므로 MainState에서 진행한다.
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
	//여기까지 카메라랑 투영변환 수행.
	myRobot->draw(modelTransformLocation);
	for (int i = 0; i < myPolygons.size(); ++i)
		myPolygons[i]->draw(modelTransformLocation);
	//이곳에 아이템 그리는 코드 넣으면 될것같습니다.

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


void MainState::update()
{
	//이곳 업데이트에서 폴리곤과 주인공의 충돌체크를 구현하시면 될것같습니다.
	myRobot->update(velocity);
	gameTime += 0.05;
	if (gameTime >= 2.0f)//게임타임이 5.0초마다 속도가 1.0씩 증가한다.
	{
		velocity += 1.0f;
		gameTime = 0.0f;
	}
	for (int i = 0; i < myPolygons.size(); ++i)
	{
		//update함수 호출하면서 무슨 값을 반환하는지 검사하고 true반환시 객체가 주인공보다 뒤에
		//있다는 말이기에 객체를 배열(벡터)에서 제거한다.
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
		int generationCount = 0;//이 카운트가 2가 넘어가면 폴리곤 생성X 즉 적어도 1방향엔 길이 있다.
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
				//이곳에 아이템 생성하는 코드 넣으시면 될것같습니다.
			}
		}
	}
}

void MainState::exit()
{
	//모든 객체 파괴
	//일단 유니크 포인터 쓰고 있어서 따로 할당해제 할 필요가X
	//자동으로 할당해제됨.
}