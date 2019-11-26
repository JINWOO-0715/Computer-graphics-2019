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
	// 윈도우 창 크기 초기화
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	// 셰이더 로드
	TriangleShader = CompileShaders("./Shaders/T1_tirangel.vs", "./Shaders/T1_tirangel.fs"); // 좌표를 함수에서 설정해줌

	CreateVertexBufferObjects(VAO_PR02, VBO_PR02,EBO_PRO);//정점 만들고 속성을 바꾸는 함수 
	CreateVertexBufferObjects(T_1_VAO_PR02, T_1_VBO_PR02, EBO_PRO);
}

bool Renderer::ReadFile(const char* fileName, string* target)
{
	ifstream file(fileName);

	if (file.fail())
	{
		cout << fileName << " 파일 로드 실패" << endl;
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
		fprintf_s(stderr, "셰이더 타입 생성 실패 : %d", shaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;

	GLint Lengths[1];
	Lengths[0] = (GLint)strlen(pShaderText);

	glShaderSource(ShaderObject, 1, p, Lengths); // 셰이더 코드를 셰이더 오브젝트에 할당

	glCompileShader(ShaderObject); // 할당된 셰이더 코드를 컴파일

	GLint isCompileSucceed;

	glGetShaderiv(ShaderObject, GL_COMPILE_STATUS, &isCompileSucceed); // ShaderObject가 성공적으로 컴파일 되었는지 확인
	if (isCompileSucceed == false)
	{
		GLchar InfoLog[1024];

		glGetShaderInfoLog(ShaderObject, 1024, NULL, InfoLog);
		fprintf_s(stderr, "Error compiling shader type %d: '%s'\n", shaderType, InfoLog);
		cout << pShaderText << endl;
	}

	glAttachShader(shaderProgram, ShaderObject); // 셰이더 프로그램에 Attach
}

GLuint Renderer::CompileShaders(const char* vertexShaderFileName, const char* fragmentShaderFileName)
{
	GLuint ShaderProgram = glCreateProgram(); // 빈 셰이더 프로그램 생성

	if (ShaderProgram == 0) // 0이면 셰이더 프로그램 생성 실패
	{
		fprintf_s(stderr, "셰이더 프로그램 생성 실패");
	}

	string vs, fs;

	// 셰이더.vs가 vs 안으로 로딩됨
	if (ReadFile(vertexShaderFileName, &vs) == false)
	{
		printf_s("버텍스 셰이더 컴파일 실패\n");
		return -1;
	}

	// 셰이더.fs가 fs 안으로 로딩됨
	if (ReadFile(fragmentShaderFileName, &fs) == false)
	{
		printf_s("버텍스 셰이더 컴파일 실패\n");
		return -1;
	}

	// 셰이더 프로그램에 vs.c_str() 버텍스 셰이더를 컴파일한 결과를 Attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// 셰이더 프로그램에 fs.c_str() 프래그먼트 셰이더를 컴파일한 결과를 Attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint isLinkSucceed = 0;
	GLchar ErrorLog[1024] = { 0 };

	// Attach 완료된 셰이더 프로그램을 링크함
	glLinkProgram(ShaderProgram);

	// 링크 성공 여부 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &isLinkSucceed);

	if (isLinkSucceed == 0)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		cout << vertexShaderFileName << ", " << fragmentShaderFileName << " 셰이더 프로그램 링크 에러\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &isLinkSucceed);
	if (isLinkSucceed == 0)
	{
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		cout << vertexShaderFileName << ", " << fragmentShaderFileName << " 유효한 셰이더 프로그램이 아님\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	cout << vertexShaderFileName << ", " << fragmentShaderFileName << " 컴파일 완료\n" << ErrorLog;

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

   0,3,1,3,2,1, // 뒤
   2,6,1,6,5,1,// 오

   0,1,5,4,0,5,// 밑 
  6,7,5,5,7,4,//   앞
  0,4,7,3,0,7,//왼

  6,3,7,6,2,3// 위 





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
	// VAO 를 지정하고 할당하기
	glGenVertexArrays(1, &VAO);
	// VAO를 바인드하기
	glBindVertexArray(VAO);

	// 2개의 VBO를 지정하고 할당하기
	glGenBuffers(2, VBO);

	//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);

	// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
	// triShape 배열의 사이즈: 9 * float

	
	if (shape == 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
		glBufferData(GL_ARRAY_BUFFER, sizeof(Rectangle_shape), Rectangle_shape, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Rectangle_index), Rectangle_index, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 6 *2* 3 * sizeof(GLfloat), Rectangle_color, GL_STATIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
		glBufferData(GL_ARRAY_BUFFER, sizeof(Piramid_shape), Piramid_shape, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Piramid_index), Piramid_index, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Piramid_color, GL_STATIC_DRAW);
	}

}

void Renderer::DrawScene()
{
	

	CreateVertexBufferObjects(VAO_PR02, VBO_PR02, EBO_PRO);
	glUseProgram(TriangleShader); // 어떤 쉐이더를 쓸것인가?
	int attribPosition = glGetAttribLocation(TriangleShader, "in_Position"); // 세이더 정점 속성 지정
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[0]);// 어떤 속성을 넣은것인가
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); // 

	int attribColor = glGetAttribLocation(TriangleShader, "in_Color");// 세이더 정점 속성 지정
	glEnableVertexAttribArray(attribColor); // 어떤 속성?
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[1]);
	glVertexAttribPointer(attribColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glm::mat4 model = glm::mat4(1.0f); // 단위 행렬로 초기화
	model = glm::translate(model, glm::vec3(0.1f, 0.5f, 0.0f)); // 변환 이동 x로 0.1 y로 0.5
	

	glm::mat4 Rotate_y = glm::mat4(1.0f);
	Rotate_y = glm::rotate(Rotate_y, glm::radians(angle_size), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 Rotate_x = glm::mat4(1.0f);
	Rotate_x = glm::rotate(Rotate_x, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));


	glm::mat4 Trans_form_sum = glm::mat4(1.0f);

	Trans_form_sum = Rotate_x * Rotate_y;

	unsigned int modelLocation = glGetUniformLocation(TriangleShader, "modelTransform"); // 쉐이더를 변수에 넣고 
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Trans_form_sum)); // 적용

	glPointSize(8);
	if (shape == 0)
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Trans_form_sum)); // 적용

			glDrawElements(GL_LINE_LOOP, 36, GL_UNSIGNED_INT, 0);
	
	}
	else
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Trans_form_sum)); // 적용

			glDrawElements(GL_LINE_LOOP, 18, GL_UNSIGNED_INT, 0);
	

	
	}

	
	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(attribColor);
	//------------------------------------------------------------------------------------------------

}