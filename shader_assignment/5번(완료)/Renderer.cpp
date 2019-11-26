#include "stdafx.h"
#include "Renderer.h"
#include <math.h>

#define pi 3.14159265f
#define radian 180/pi
struct cir
{
	GLfloat x = 0.0f;
	GLfloat y = 0.0f;
	GLfloat z = 0.0f;
};
Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}

Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	// ������ â ũ�� �ʱ�ȭ
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	// ���̴� �ε�
	TriangleShader = CompileShaders("./Shaders/T1_tirangel.vs", "./Shaders/T1_tirangel.fs"); // ��ǥ�� �Լ����� ��������
	

	CreateVertexBufferObjects(VAO_PR02, VBO_PR02);//���� ����� �Ӽ��� �ٲٴ� �Լ� 
	CreateVertexBufferObjects(T_1_VAO_PR02, T_1_VBO_PR02);
}

bool Renderer::ReadFile(const char* fileName, string* target)
{
	ifstream file(fileName);

	if (file.fail())
	{
		cout << fileName << " ���� �ε� ����" << endl;
		file.close();

		return false;
	}

	std::string line;
	while (getline(file, line))
	{
		target->append(line.c_str());
		target->append("\n");
	}

	return true;
}

void Renderer::AddShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
	GLuint ShaderObject = glCreateShader(shaderType);

	if (ShaderObject == 0)
	{
		fprintf_s(stderr, "���̴� Ÿ�� ���� ���� : %d", shaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;

	GLint Lengths[1];
	Lengths[0] = (GLint)strlen(pShaderText);

	glShaderSource(ShaderObject, 1, p, Lengths); // ���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�

	glCompileShader(ShaderObject); // �Ҵ�� ���̴� �ڵ带 ������

	GLint isCompileSucceed;

	glGetShaderiv(ShaderObject, GL_COMPILE_STATUS, &isCompileSucceed); // ShaderObject�� ���������� ������ �Ǿ����� Ȯ��
	if (isCompileSucceed == false)
	{
		GLchar InfoLog[1024];

		glGetShaderInfoLog(ShaderObject, 1024, NULL, InfoLog);
		fprintf_s(stderr, "Error compiling shader type %d: '%s'\n", shaderType, InfoLog);
		cout << pShaderText << endl;
	}

	glAttachShader(shaderProgram, ShaderObject); // ���̴� ���α׷��� Attach
}

GLuint Renderer::CompileShaders(const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
	GLuint ShaderProgram = glCreateProgram(); // �� ���̴� ���α׷� ����

	if (ShaderProgram == 0) // 0�̸� ���̴� ���α׷� ���� ����
	{
		fprintf_s(stderr, "���̴� ���α׷� ���� ����");
	}

	string vs, fs;

	// ���̴�.vs�� vs ������ �ε���
	if (ReadFile(vertexShaderFileName, &vs) == false)
	{
		printf_s("���ؽ� ���̴� ������ ����\n");
		return -1;
	}

	// ���̴�.fs�� fs ������ �ε���
	if (ReadFile(fragmentShaderFileName, &fs) == false)
	{
		printf_s("���ؽ� ���̴� ������ ����\n");
		return -1;
	}

	// ���̴� ���α׷��� vs.c_str() ���ؽ� ���̴��� �������� ����� Attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ���̴� ���α׷��� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� Attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint isLinkSucceed = 0;
	GLchar ErrorLog[1024] = { 0 };

	// Attach �Ϸ�� ���̴� ���α׷��� ��ũ��
	glLinkProgram(ShaderProgram);

	// ��ũ ���� ���� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &isLinkSucceed);

	if (isLinkSucceed == 0)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		cout << vertexShaderFileName << ", " << fragmentShaderFileName << " ���̴� ���α׷� ��ũ ����\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &isLinkSucceed);
	if (isLinkSucceed == 0)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		cout << vertexShaderFileName << ", " << fragmentShaderFileName << " ��ȿ�� ���̴� ���α׷��� �ƴ�\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	cout << vertexShaderFileName << ", " << fragmentShaderFileName << " ������ �Ϸ�\n" << ErrorLog;

	return ShaderProgram;
}

void Renderer::CreateVertexBufferObjects(GLuint& VAO, GLuint* VBO)
{
	// VAO �� �����ϰ� �Ҵ��ϱ�
	glGenVertexArrays(1, &VAO);

	// VAO�� ���ε��ϱ�
	glBindVertexArray(VAO);

	// 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	glGenBuffers(2, VBO);
}

void Renderer::DrawScene()
{
	glUseProgram(TriangleShader); // � ���̴��� �����ΰ�?
	cir cir_point[36];
	cir cor_color[36];
	int q = 0;
	for (int k = 0; k < 360 ; k += 10)
	{
			float angle = k * 3.141592 / 180;
			cir_point[q].x = circle_x+ circle_radian * cos(angle);
			cir_point[q].y = circle_y + circle_radian * sin(angle);

			cor_color[q].x = 0.25f;
			cor_color[q].y = 0.45f;
			cor_color[q].z = 0.55f;
			q++;

	}

	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[0]);

	// ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	// triShape �迭�� ������: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 36*3* sizeof(GLfloat), cir_point, GL_STATIC_DRAW);

	//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[1]);
	// triShape �迭�� ������: 9 * float
	glBufferData(GL_ARRAY_BUFFER, 36*3 * sizeof(GLfloat), cor_color, GL_STATIC_DRAW);

	// ���� colors���� ���ؽ� ������ �����Ѵ�.
	// colors �迭�� ������: 9 *float


	int attribPosition = glGetAttribLocation(TriangleShader, "in_Position"); // ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[0]);// � �Ӽ��� �������ΰ�
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); // 

	int attribColor = glGetAttribLocation(TriangleShader, "in_Color");// ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(attribColor); // � �Ӽ�?
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[1]);
	glVertexAttribPointer(attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	if (draw_mode == 0)
	{
		glDrawArrays(GL_LINE_LOOP, 0, 36);
		
	
	}
	else
	{
		glPointSize(4);
		glDrawArrays(GL_POINTS, 0, 36);
		
	}
	

	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(attribColor);




	//////////////////////////////////////////////



}