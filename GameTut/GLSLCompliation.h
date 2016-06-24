#pragma once
#include<GL\glew.h>
#include<iostream>
#include<string>
#include "Errors.h"
#include<fstream>
#include<vector>
typedef std::string str;

class GLSLCompliation
{
public:
	GLSLCompliation();
	void run();
	~GLSLCompliation();
	void compileShaders(const str& vertexShaderFilePath, const str& fragShaderFilePath);
	void addAttribute(const std::string& attributeName);
	void linkShaders();
	//Use ProgramID , Unuse.
	void use();
	void unuse();
private:
	void checkCompliation(GLuint shader, const str& type);
	void checkFileErr(const str&path);
	void compileShader(const str& filePath, GLuint shader_param, const str&type);
	void checkErrFileCompile(const str& type);
	int _numAttributes_in;
	GLuint vtx_shader,_programID,frag_shader;
	std::ifstream shader_file;
	GLint status, isLinked = 0;;
	Errors err;
	str file_content;
	str line_read;
};

