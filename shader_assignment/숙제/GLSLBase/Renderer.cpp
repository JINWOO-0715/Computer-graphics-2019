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
	LineShader = CompileShaders("./Shaders/T1_tirangel.vs", "./Shaders/T1_tirangel.fs"); // 좌표를 함수에서 설정해줌
	CreateVertexBufferObjects(VAO_PR02, VBO_PR02);//정점 만들고 속성을 바꾸는 함수 
	CreateVertexBufferObjects(L_VAO_PR02, L_VBO_PR02);//정점 만들고 속성을 바꾸는 함수 
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




	// VAO 를 지정하고 할당하기
	glGenVertexArrays(1, &VAO);
	// VAO를 바인드하기
	glBindVertexArray(VAO);

	// 2개의 VBO를 지정하고 할당하기
	glGenBuffers(2, VBO);


	// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
	// triShape 배열의 사이즈: 9 * float
	//--- 1번째 VBO를 활성화하여 바인드하고, 버텍스 속성 (좌표값)을 저장

	if(figure_shape ==1) // 사각형 
	{	// 변수 diamond 에서 버텍스 데이터 값을 버퍼에 복사한다.
	// triShape 배열의 사이즈: 9 * float
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Rectangle_shape, GL_STATIC_DRAW);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 6 * 3 * sizeof(GLfloat), Rectangle_color, GL_STATIC_DRAW);

	}
	if(figure_shape==0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), Triangle_shape, GL_STATIC_DRAW);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), Triangle_color, GL_STATIC_DRAW);

	}
	if (figure_shape == 3)
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, 100 * 3 * sizeof(GLfloat), Line_shape, GL_STATIC_DRAW);

		//--- 2번째 VBO를 활성화 하여 바인드 하고, 버텍스 속성 (색상)을 저장
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);

		// 변수 colors에서 버텍스 색상을 복사한다.
		// colors 배열의 사이즈: 9 *float
		glBufferData(GL_ARRAY_BUFFER, 100 * 3 * sizeof(GLfloat), Line_color, GL_STATIC_DRAW);
	}

}

void Renderer::DrawScene()
{

	CreateVertexBufferObjects(VAO_PR02, VBO_PR02);
	glUseProgram(TriangleShader); // 어떤 쉐이더를 쓸것인가?
	int attribPosition = glGetAttribLocation(TriangleShader, "in_Position"); // 세이더 정점 속성 지정
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PR02[0]);// 어떤 속성을 넣은것인가
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); // 

	int attribColor = glGetAttribLocation(TriangleShader, "in_Color");// 세이더 정점 속성 지정
	glEnableVertexAttribArray(attribColor); // 어떤 속성?
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