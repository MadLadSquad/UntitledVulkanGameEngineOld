#include "GLShader.hpp"

#ifdef Legacy
UVK::GLShader::GLShader()
{
	ShaderID = 0;
	UniformModel = 0;
	UniformProjection = 0;
}

void UVK::GLShader::CreateFromString(const char* Vertex, const char* Fragment)
{
	CompileShader(Vertex, Fragment);
}

void UVK::GLShader::CreateFromFiles(const char* VertexLocation, const char* FragmentLocation)
{
	std::string VertexString = ReadFile(VertexLocation);
	std::string FragmentString = ReadFile(FragmentLocation);
	//const char* vertexCode = vertexString.c_str();
	//const char* fragmentCode = fragmentString.c_str();
	CompileShader(VertexString.c_str(), FragmentString.c_str());
}

std::string UVK::GLShader::ReadFile(const char* FileLocation)
{
	std::string Content;
	std::ifstream FileStream(FileLocation, std::ios::in);

	if (!FileStream.is_open()) {
		std::cout << "Failed to open" << FileLocation << "!" << "File may not exist!" << std::endl;
		return "";
	}

	std::string Line = "";
	while (!FileStream.eof())
	{
		std::getline(FileStream, Line);
		Content.append(Line + "\n");
	}

	FileStream.close();
	return Content;
}

void UVK::GLShader::CompileShader(const char* Vertex, const char* Fragment)
{
	ShaderID = glCreateProgram();

	if (!ShaderID)
	{
		std::cout << "Error creating a shader!" << std::endl;
		return;
	}

	AddShader(ShaderID, Vertex, GL_VERTEX_SHADER);
	AddShader(ShaderID, Fragment, GL_FRAGMENT_SHADER);

	GLint Result = 0;

	glLinkProgram(ShaderID);
	glGetProgramiv(ShaderID, GL_LINK_STATUS, &Result);

	glValidateProgram(ShaderID);
	glGetProgramiv(ShaderID, GL_VALIDATE_STATUS, &Result);

	UniformProjection = glGetUniformLocation(ShaderID, "projection");
	UniformModel = glGetUniformLocation(ShaderID, "model");
	UniformView = glGetUniformLocation(ShaderID, "view");
}

GLuint UVK::GLShader::GetProjectionLocation()
{
	return UniformProjection;
}
GLuint UVK::GLShader::GetModelLocation()
{
	return UniformModel;
}

GLuint UVK::GLShader::GetViewLocation()
{
	return UniformView;
}

void UVK::GLShader::UseShader()
{
	glUseProgram(ShaderID);	
}

void UVK::GLShader::ClearShader()
{
	if (ShaderID != 0)
	{
		glDeleteProgram(ShaderID);
		ShaderID = 0;
	}

	UniformModel = 0;
	UniformProjection = 0;
}


void UVK::GLShader::AddShader(GLuint Program, const char* Shader, GLenum ShaderType)
{
	GLuint LeShader = glCreateShader(ShaderType);

	const GLchar* Code[1];
	Code[0] = Shader;

	GLint codeLength[1];
	codeLength[0] = strlen(Shader);

	glShaderSource(LeShader, 1, Code, codeLength);
	glCompileShader(LeShader);

	GLint Result = 0;
	GLchar ErrorLog[1024] = { 0 };

	glGetShaderiv(LeShader, GL_COMPILE_STATUS, &Result);
	if (!Result)
	{
		glGetShaderInfoLog(LeShader, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << "Error compiling the " << ShaderType << "Shader" << std::endl;
		return;
	}

	glAttachShader(Program, LeShader);
}

UVK::GLShader::~GLShader()
{
	ClearShader();
}
#endif