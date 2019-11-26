
#include "VertexShader.hpp"
#include "FragShader.hpp"
#include "ShaderProgram.hpp"
#include "FrameWork.hpp"
#include "States.hpp"
#include "Robot.hpp"
#define _CRT_SECURE_NO_WARNINGS

//메인에서는 프레임워크랑 스테이트만 인클루드해서 돌리고싶다.
//프레임워크가 메인에서 처음 생성되고 이때 프레임워크의 생성자에서
//지금 메인에서 하고있는 초기화 작업을 수행한다.

int windowNumber = 0;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid keyBoardEvent(unsigned char key, int x, int y);
GLvoid keyUpEvent(unsigned char key, int x, int y);
GLvoid timerFunc(int);
GLuint compileShaders();
int WIDTH = 800;
int HEIGTH = 600;

GLuint shaderProgramID;


std::unique_ptr<FrameWork> myFrameWork = nullptr;
State* myMainState = nullptr;
void main(int argc, char** argv)
{
	//create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGTH);
	windowNumber = glutCreateWindow("2016182044HJO");
	//GLEW init
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initalize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW initialized\n";
	auto a = compileShaders();
	shaderProgramID = a;
	glUseProgram(shaderProgramID);
	
	myMainState = new MainState();
	myFrameWork = std::make_unique<FrameWork>(myMainState);
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(keyBoardEvent);
	glutReshapeFunc(Reshape);
	glutKeyboardUpFunc(keyUpEvent);
	glutTimerFunc(50, timerFunc, 1);
	glutMainLoop();
	//여기까지 윈도우 만들고 함수 등록하는 초기작업을 수행한다.
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
GLvoid drawScene()
{
	myFrameWork->draw();
}

GLvoid keyBoardEvent(unsigned char key, int x, int y)
{
	myFrameWork->handleEvent(key, x, y);
}

GLvoid keyUpEvent(unsigned char key, int x, int y)
{
	myFrameWork->keyUpEvent(key, x, y);
}

GLvoid timerFunc(int index)
{
	myFrameWork->update();
	glutTimerFunc(50, timerFunc, 1);
	glutPostRedisplay();
}

GLuint compileShaders()
{
	VertexShader vShader1("vertexSource.txt");
	vShader1.createAndCompile();
	FragShader fShader1("FragSource.txt");
	fShader1.createAndCompile();
	ShaderProgram ShaderProgram1;
	ShaderProgram1.attachAndLink({ fShader1.retShader(),vShader1.retShader() });

	return ShaderProgram1.retProgramID();
}