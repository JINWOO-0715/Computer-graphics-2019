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

	CreateVertexBufferObjects(VAO_PR02, VBO_PR02);//���� ����� �Ӽ��� �ٲٴ� �Լ� 

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


	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����


	// ���� diamond ���� ���ؽ� ������ ���� ���ۿ� �����Ѵ�.
	// triShape �迭�� ������: 9 * float
	//--- 1��° VBO�� Ȱ��ȭ�Ͽ� ���ε��ϰ�, ���ؽ� �Ӽ� (��ǥ��)�� ����
	
	
}

void Renderer::DrawScene()
{

	glUseProgram(TriangleShader); // � ���̴��� �����ΰ�?
	int attribPosition = glGetAttribLocation(TriangleShader, "in_Position"); // ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[0]);// � �Ӽ��� �������ΰ�
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); // 

	int attribColor = glGetAttribLocation(TriangleShader, "in_Color");// ���̴� ���� �Ӽ� ����
	glEnableVertexAttribArray(attribColor); // � �Ӽ�?
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[1]);
	glVertexAttribPointer(attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glm::mat4 Translate_y_minus = glm::mat4(1.0f); // ���� ��ķ� �ʱ�ȭ
	glm::mat4 Translate_y_plus = glm::mat4(1.0f); // ���� ��ķ� �ʱ�ȭ
	glm::mat4 Translate_x_plus = glm::mat4(1.0f); // ���� ��ķ� �ʱ�ȭ
	glm::mat4 Translate_x_minus = glm::mat4(1.0f); // ���� ��ķ� �ʱ�ȭ
	glm::mat4 Rotate_y = glm::mat4(1.0f);
	glm::mat4 Rotate_x = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);


	glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 2.0f);
	glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Rotate_x = glm::rotate(Rotate_x, glm::radians(angle_size_x), glm::vec3(1.0f, 0.0f, 0.0f));
	Rotate_y = glm::rotate(Rotate_y, glm::radians(angle_size), glm::vec3(0.0f, 1.0f, 0.0f));
	
	
	Translate_y_minus = glm::translate(Translate_y_minus, glm::vec3(0.0f, -0.5f, 0.0f)); // ��ȯ �̵� x�� 0.1 y�� 0.5
	Translate_y_plus = glm::translate(Translate_y_plus, glm::vec3(0.0f, 0.5f, 0.0f)); // ��ȯ �̵� x�� 0.1 y�� 0.5
	Translate_x_plus = glm::translate(Translate_x_plus, glm::vec3(0.0f, 0.0f, 0.5f)); // ��ȯ �̵� x�� 0.1 y�� 0.5
	Translate_x_minus = glm::translate(Translate_y_minus, glm::vec3(0.0f, 0.0f, -0.5f)); // ��ȯ �̵� x�� 0.1 y�� 0.5

	
	glm::mat4 Trans_form_sum = glm::mat4(1.0f); // �� ��ȯ
	glm::mat4 Trans_form_t = glm::mat4(1.0f); // �� ��ȯ


	Trans_form_sum =  Rotate_y;
	unsigned int modelLocation = glGetUniformLocation(TriangleShader, "modelTransform"); // ���̴��� ������ �ְ� 
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Trans_form_sum)); // ����

	if (press_t == true)
	{
		unsigned int modelLocation = glGetUniformLocation(TriangleShader, "modelTransform"); // ���̴��� ������ �ְ� 
		Trans_form_t = (Trans_form_sum)*Translate_y_plus * Rotate_x*Translate_y_minus;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Trans_form_t)); // ����
	}
	if (press_f == true)
	{
		unsigned int modelLocation = glGetUniformLocation(TriangleShader, "modelTransform"); // ���̴��� ������ �ְ� 
		Trans_form_t = Trans_form_sum* Translate_y_minus*Translate_x_minus*Rotate_x*Translate_x_plus*Translate_y_plus;
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Trans_form_t)); // ����
	}
	
	
	glm::mat4 view = glm::mat4(1.0f); // �亯ȯ
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
	unsigned int view_location = glGetUniformLocation(TriangleShader, "viewTransform"); // ���̴��� ������ �ְ� 
	glUniformMatrix4fv(view_location, 1, GL_FALSE, &view[0][0]);
	
	if (projection_type == 0)
	{
		projection = glm::ortho(-3.0f, 3.0f,-3.0f, 3.0f,-3.0f, 3.0f); // ������ȯ
		unsigned int projectionLocation = glGetUniformLocation(TriangleShader, "projectionTransform");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	
	}
	else
	{

		projection = glm::perspective(glm::radians(45.0f), (float)800.0f / (float)800.0f, 0.1f, 50.0f); // ������ȯ
		unsigned int projectionLocation = glGetUniformLocation(TriangleShader, "projectionTransform");
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);

	}


	glPointSize(8);


	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(attribColor);
	//------------------------------------------------------------------------------------------------

}