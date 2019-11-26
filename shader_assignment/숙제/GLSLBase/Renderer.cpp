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
	TriangleShader = CompileShaders("./Shaders/T1_tirangel.vs", "./Shaders/T1_tirangel.fs"); // ��ǥ�� �Լ����� ��������
	LineShader = CompileShaders("./Shaders/T1_tirangel.vs", "./Shaders/T1_tirangel.fs"); // ��ǥ�� �Լ����� ��������
	CreateVertexBufferObjects(VAO_PR02, VBO_PR02);//���� ����� �Ӽ��� �ٲٴ� �Լ� 
	CreateVertexBufferObjects(L_VAO_PR02, L_VBO_PR02);//���� ����� �Ӽ��� �ٲٴ� �Լ� 
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

void Renderer::CreateVertexBufferObjects(GLuint& VAO, GLuint* VBO )
{

	const GLfloat Rectangle_shape[6][3] = {
	top_point_x, top_point_y, 0.2f, // 1
	top_point_x-0.2f, top_point_y, 0.2f, // 2
	top_point_x-0.2f, top_point_y - 0.2f, 0.2f, // 3
	
	top_point_x, top_point_y, 0.2f, // 3
	top_point_x-0.2f, top_point_y-0.2f, 0.2f, // 3
	top_point_x, top_point_y-0.2f, 0.2f, // 3
	};

	const GLfloat Rectangle_color[6][3] = {
		{1.0f,0.0f,0.0f},
		{1.0f,0.0f,0.0f},
		{1.0f,0.0f,0.0f},
		{1.0f,0.0f,0.0f},
		{1.0f,0.0f,0.0f},
		{1.0f,0.0f,0.0f}

	};
	

	 GLfloat Triangle_shape[3][3] = {
	top_point_x, top_point_y, 0.2f, // 3
	top_point_x-0.2f, top_point_y - 0.2f, 0.2f, //  1
	top_point_x + 0.2f, top_point_y - 0.2f, 0.2f,//2
	};

	 GLfloat Triangle_color[3][3] = {
		{1.0f,0.0f,0.0f},
		{1.0f,0.0f,0.0f},
		{1.0f,0.0f,0.0f}
	};




	// VAO �� �����ϰ� �Ҵ��ϱ�
	glGenVertexArrays(1, &VAO);
	// VAO�� ���ε��ϱ�
	glBindVertexArray(VAO);

	// 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	glGenBuffers(2, VBO);


	// ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	// triShape �迭�� ������: 9 * float
	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����

	if(figure_shape ==1) // �簢�� 
	{	// ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	// triShape �迭�� ������: 9 * float
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Rectangle_shape, GL_STATIC_DRAW);

		//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

		// ���� colors���� ���ؽ� ������ �����Ѵ�.
		// colors �迭�� ������: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Rectangle_color, GL_STATIC_DRAW);

	}
	if(figure_shape==0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), Triangle_shape, GL_STATIC_DRAW);

		//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

		// ���� colors���� ���ؽ� ������ �����Ѵ�.
		// colors �迭�� ������: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), Triangle_color, GL_STATIC_DRAW);

	}
	if (figure_shape == 3)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, 100 * 3 * sizeof(GLfloat), Line_shape, GL_STATIC_DRAW);

		//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

		// ���� colors���� ���ؽ� ������ �����Ѵ�.
		// colors �迭�� ������: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 100 * 3 * sizeof(GLfloat), Line_color, GL_STATIC_DRAW);
	}

}

void Renderer::DrawScene()
{

	CreateVertexBufferObjects(VAO_PR02, VBO_PR02);
	glUseProgram(TriangleShader); // � ���̴��� �����ΰ�?
	int attribPosition = glGetAttribLocation(TriangleShader, "in_Position"); // ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[0]);// � �Ӽ��� �������ΰ�
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); // 

	int attribColor = glGetAttribLocation(TriangleShader, "in_Color");// ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(attribColor); // � �Ӽ�?
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[1]);
	glVertexAttribPointer(attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glPointSize(8);
	if (figure_shape == 1)
	{
		if (fill_line_shape == 1)
		{
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		else
		{
			glDrawArrays(GL_LINE_LOOP, 0, 6);

		}

	}
	if (figure_shape == 0)
	{
		if (fill_line_shape == 1)
		{
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		else
		{
			glDrawArrays(GL_LINE_LOOP, 0, 6);
		}
	
	}
	if (figure_shape == 3)
	{
			glDrawArrays(GL_LINES, 0, 97);
	}

	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(attribColor);
	//------------------------------------------------------------------------------------------------

}