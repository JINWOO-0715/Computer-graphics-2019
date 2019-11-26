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

	CreateVertexBufferObjects(VAO_PR02, VBO_PR02,EBO_PRO);//���� ����� �Ӽ��� �ٲٴ� �Լ� 
	CreateVertexBufferObjects(T_1_VAO_PR02, T_1_VBO_PR02, EBO_PRO);
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

void Renderer::CreateVertexBufferObjects(GLuint& VAO, GLuint* VBO , GLuint& EBO)
{
	
	const GLfloat Rectangle_shape[8][3] = {
	-0.5f, -0.5f, -0.5f, //0
	0.5f, -0.5f, -0.5f,//1
	0.5f, 0.5f, -0.5f,//2
   -0.5f, 0.5f, -0.5f,//3

   -0.5f, -0.5f, 0.5f,//4
	0.5f, -0.5f, 0.5f,//5/
	0.5f, 0.5f, 0.5f,//6/
   -0.5f, 0.5f, 0.5f//7

	};


	const GLfloat Rectangle_color[8][3] = {
		{0.5f,0.5f,0.5f},
		{1.0f,1.0f,1.0f},
		{0.0f,1.0f,0.0f},
		{1.0f,0.0f,0.0f},
		{0.0f,0.0f,1.0f},

		{0.0f,1.0f,0.5f},
		{1.0f,0.0f,0.5f},
		{1.0f,0.5f,0.0f},
	};

	unsigned int Rectangle_index[] = {

   0,3,1,3,2,1, // ��
   2,6,1,6,5,1,// ��

   0,1,5,4,0,5,// �� 
  6,7,5,5,7,4,//   ��
  0,4,7,3,0,7,//��

  6,3,7,6,2,3// �� 





	};

	const GLfloat Piramid_shape[5][3] = {
	-0.5f, -0.5f, -0.5f, // 
	-0.5f, -0.5f, 0.5f,// 
	0.5f, -0.5f, -0.5f,// 
	0.5f, -0.5f, 0.5f,// 
	0.0f, 0.5f, 0.0f // 
	};

	const GLfloat Piramid_color[5][3] = {
		{0.5f,0.5f,0.5f},
		{1.0f,1.0f,1.0f},
		{0.0f,1.0f,0.0f},
		{1.0f,0.0f,0.0f},
		{0.0f,0.0f,1.0f}
	};
	unsigned int Piramid_index[] = {

4,0,1,
4,3,2,

4,2,0,
4,1,3,

0,2,1,
2,3,1


	

	};
	// VAO �� �����ϰ� �Ҵ��ϱ�
	glGenVertexArrays(1, &VAO);
	// VAO�� ���ε��ϱ�
	glBindVertexArray(VAO);

	// 2���� VBO�� �����ϰ� �Ҵ��ϱ�
	glGenBuffers(2, VBO);

	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	// ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	// triShape �迭�� ������: 9 * float

	
	if (shape == 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // GL_ELEMENT_ARRAY_BUFFER ���� �������� ���ε�
		glBufferData(GL_ARRAY_BUFFER, sizeof(Rectangle_shape), Rectangle_shape, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Rectangle_index), Rectangle_index, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

		// ���� colors���� ���ؽ� ������ �����Ѵ�.
		// colors �迭�� ������: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 6 *2* 3 * sizeof(GLfloat), Rectangle_color, GL_STATIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // GL_ELEMENT_ARRAY_BUFFER ���� �������� ���ε�
		glBufferData(GL_ARRAY_BUFFER, sizeof(Piramid_shape), Piramid_shape, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Piramid_index), Piramid_index, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		//--- 2��° VBO�� Ȱ��ȭ �Ͽ� ���ε� �ϰ�, ���ؽ� �Ӽ� (����)�� ����
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

		// ���� colors���� ���ؽ� ������ �����Ѵ�.
		// colors �迭�� ������: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Piramid_color, GL_STATIC_DRAW);
	}

}

void Renderer::DrawScene()
{
	

	CreateVertexBufferObjects(VAO_PR02, VBO_PR02, EBO_PRO);
	glUseProgram(TriangleShader); // � ���̴��� �����ΰ�?
	int attribPosition = glGetAttribLocation(TriangleShader, "in_Position"); // ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[0]);// � �Ӽ��� �������ΰ�
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); // 

	int attribColor = glGetAttribLocation(TriangleShader, "in_Color");// ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(attribColor); // � �Ӽ�?
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[1]);
	glVertexAttribPointer(attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glm::mat4 model = glm::mat4(1.0f); // ���� ��ķ� �ʱ�ȭ
	model = glm::translate(model, glm::vec3(0.1f, 0.5f, 0.0f)); // ��ȯ �̵� x�� 0.1 y�� 0.5
	

	glm::mat4 Rotate_y = glm::mat4(1.0f);
	Rotate_y = glm::rotate(Rotate_y, glm::radians(angle_size), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 Rotate_x = glm::mat4(1.0f);
	Rotate_x = glm::rotate(Rotate_x, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));


	glm::mat4 Trans_form_sum = glm::mat4(1.0f);

	Trans_form_sum = Rotate_x * Rotate_y;

	unsigned int modelLocation = glGetUniformLocation(TriangleShader, "modelTransform"); // ���̴��� ������ �ְ� 
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Trans_form_sum)); // ����

	glPointSize(8);
	if (shape == 0)
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Trans_form_sum)); // ����

			glDrawElements(GL_LINE_LOOP, 36, GL_UNSIGNED_INT, 0);
	
	}
	else
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Trans_form_sum)); // ����

			glDrawElements(GL_LINE_LOOP, 18, GL_UNSIGNED_INT, 0);
	

	
	}

	
	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(attribColor);
	//------------------------------------------------------------------------------------------------

}