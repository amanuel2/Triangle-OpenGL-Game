#pragma once

#include <string>
#include <GL/glew.h>
#include "Errors.h"


//This class handles the compilation, linking, and usage of a GLSL shader program.
//Reference: http://www.opengl.org/wiki/Shader_Compilation
class GLSLCompliation
{
public:
	GLSLCompliation();
	~GLSLCompliation();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);

	void linkShaders();

	void addAttribute(const std::string& attributeName);

	void use();
	void unuse();
private:

	int _numAttributes;

	void compileShader(const std::string& filePath, GLuint id);

	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	Errors err;
};

