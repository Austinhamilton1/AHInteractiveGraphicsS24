#include "Shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) {
	this->vertexSource = vertexSource;
	this->fragmentSource = fragmentSource;
	Init();
	CreateShaderProgram();
}

Shader::Shader() {
	SetDefaultSource();
	Init();
	CreateShaderProgram();
}

void Shader::Init() {
	shaderProgram = 0;
}

void Shader::SetDefaultSource() {
	vertexSource =
		"#version 430\n"
		"layout(location = 0) in vec3 position;\n"
		"layout(location = 1) in vec3 color;\n"
		"out vec4 fragColor;\n"
		"uniform mat4 world;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = projection * view * world * vec4(position, 1.0);\n"
		"   fragColor = vec4(color, 1.0);\n"
		"}\n";

	fragmentSource =
		"#version 430\n"
		"in vec4 fragColor;\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"   color = fragColor;\n"
		"}\n";
}

unsigned int Shader::CompileShaderSource(int type, const std::string& shaderSource) {
	unsigned shaderId = glCreateShader(type);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const char* source = (const char*)shaderSource.c_str();
	glShaderSource(shaderId, 1, &source, 0);

	glCompileShader(shaderId);

	int isCompiled = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE) {
		int maxLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetShaderInfoLog(shaderId, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(shaderId);

		log(infoLog);
		return -1;
	}
	log("Success");
	return shaderId;
}

void Shader::CreateShaderProgram() {
	unsigned int vertexShader =
		CompileShaderSource(GL_VERTEX_SHADER, vertexSource);
	if (vertexShader == -1) return;

	unsigned int fragmentShader =
		CompileShaderSource(GL_FRAGMENT_SHADER, fragmentSource);
	if (fragmentShader == -1) return;

	// Time to link the shaders together into a program.

	shaderProgram = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link our program
	glLinkProgram(shaderProgram);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	int isLinked = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(shaderProgram);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		log(infoLog);
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	log("Successfully created the shader!");
}

void Shader::AddUniform(const std::string& uniformName) {
	if (uniformMap.find(uniformName) != uniformMap.end())
		return;
	unsigned int location = glGetUniformLocation(shaderProgram, uniformName.c_str());
	uniformMap[uniformName] = location;
}

void Shader::SendMat4Uniform(const std::string& uniformName, const glm::mat4& mat) {
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(uniformMap[uniformName], 1, GL_FALSE, glm::value_ptr(mat));
}
