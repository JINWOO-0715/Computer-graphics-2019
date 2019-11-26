#include "stdafx.h"
#include "Renderer.h"


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
	T1_TriangleShader = CompileShaders("./Shaders/T1_tirangel.vs", "./Shaders/T1_tirangel.fs");
	T2_TriangleShader = CompileShaders("./Shaders/T2_tirangel.vs", "./Shaders/T2_tirangel.fs");
	T3_TriangleShader = CompileShaders("./Shaders/T2_tirangel.vs", "./Shaders/T2_tirangel.fs");
	T4_TriangleShader = CompileShaders("./Shaders/T2_tirangel.vs", "./Shaders/T2_tirangel.fs");
	// ���� �Ӽ� ����°� �ʿ��ϴٸ� ���� �־����� .
	CreateVertexBufferObjects(T_1_VAO_PR02, T_1_VBO_PR02);
	CreateVertexBufferObjects(T_2_VAO_PR02, T_2_VBO_PR02);
	CreateVertexBufferObjects(T_3_VAO_PR02, T_3_VBO_PR02);
	CreateVertexBufferObjects(T_4_VAO_PR02, T_4_VBO_PR02);
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


	glUseProgram(T1_TriangleShader); // � ���̴��� �����ΰ�?
	int T1_attribPosition = glGetAttribLocation(T1_TriangleShader, "in_Position"); // ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(T1_attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, T_1_VBO_PR02[0]);// � �Ӽ��� �������ΰ�
	glVertexAttribPointer(T1_attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); // 

	int T1_attribColor = glGetAttribLocation(T1_TriangleShader, "in_Color");// ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(T1_attribColor); // � �Ӽ�?
	glBindBuffer(GL_ARRAY_BUFFER, T_1_VBO_PR02[1]);
	glVertexAttribPointer(T1_attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
	if (Renderer::draw_mode== 1)
	{
		glDrawArrays(GL_LINE_LOOP, 0, 3);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}


	glDisableVertexAttribArray(T1_attribPosition);
	glDisableVertexAttribArray(T1_attribColor);
	//------------------------------------------------------------------------------------------------
	glUseProgram(T2_TriangleShader); // � ���̴��� �����ΰ�?
	int T2_attribPosition = glGetAttribLocation(T2_TriangleShader, "in_Position"); // ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(T2_attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, T_2_VBO_PR02[0]);// � �Ӽ��� �������ΰ�
	glVertexAttribPointer(T2_attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); // 


	int T2_attribColor = glGetAttribLocation(T2_TriangleShader, "in_Color");// ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(T2_attribColor); // � �Ӽ�?
	glBindBuffer(GL_ARRAY_BUFFER, T_2_VBO_PR02[1]);
	glVertexAttribPointer(T2_attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
	if (Renderer::draw_mode == 1)
	{
		glDrawArrays(GL_LINE_LOOP, 0, 3);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}




	glDisableVertexAttribArray(T2_attribPosition);
	glDisableVertexAttribArray(T2_attribColor);
	
	glUseProgram(T3_TriangleShader); // � ���̴��� �����ΰ�?
	int T3_attribPosition = glGetAttribLocation(T3_TriangleShader, "in_Position"); // ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(T3_attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, T_3_VBO_PR02[0]);// � �Ӽ��� �������ΰ�
	glVertexAttribPointer(T3_attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); // 


	int T3_attribColor = glGetAttribLocation(T3_TriangleShader, "in_Color");// ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(T3_attribColor); // � �Ӽ�?
	glBindBuffer(GL_ARRAY_BUFFER, T_3_VBO_PR02[1]);
	glVertexAttribPointer(T3_attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);


	if (Renderer::draw_mode == 1)
	{
		glDrawArrays(GL_LINE_LOOP, 0, 3);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	glDisableVertexAttribArray(T3_attribPosition);
	glDisableVertexAttribArray(T3_attribColor);

	glUseProgram(T4_TriangleShader); // � ���̴��� �����ΰ�?
	int T4_attribPosition = glGetAttribLocation(T4_TriangleShader, "in_Position"); // ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(T4_attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, T_4_VBO_PR02[0]);// � �Ӽ��� �������ΰ�
	glVertexAttribPointer(T4_attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); // 


	int T4_attribColor = glGetAttribLocation(T4_TriangleShader, "in_Color");// ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(T4_attribColor); // � �Ӽ�?
	glBindBuffer(GL_ARRAY_BUFFER, T_4_VBO_PR02[1]);
	glVertexAttribPointer(T4_attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

	if (Renderer::draw_mode == 1)
	{
		glDrawArrays(GL_LINE_LOOP, 0, 3);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}


	glDisableVertexAttribArray(T4_attribPosition);
	glDisableVertexAttribArray(T4_attribColor);
}