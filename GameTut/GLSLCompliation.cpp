#include "GLSLCompliation.h"


GLSLCompliation::GLSLCompliation() :vtx_shader(0), frag_shader(0), _programID(0), status(0)
{
}

void GLSLCompliation::run()
{
}

//Make Shaders One Program.
void GLSLCompliation::linkShaders()
{

	//Attach our shaders to our program
	glAttachShader(_programID, vtx_shader);
	glAttachShader(_programID, frag_shader);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);
		//print the error log and quit
		std::printf("%s\n", &(infoLog[0]));

		err.fatalErr("Linking Shaders Failed");

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(vtx_shader);
		glDeleteShader(frag_shader);

		//Use the infoLog as you see fit.

		//In this simple program, we'll just leave
		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, vtx_shader);
	glDetachShader(_programID, vtx_shader);
}

//Adds an attribute to our shader. SHould be called between compiling and linking.
void GLSLCompliation::addAttribute(const std::string& attributeName) {
	glBindAttribLocation(_programID, _numAttributes_in++, attributeName.c_str());
}

//enable the shader, and all its attributes
void GLSLCompliation::use() {
	glUseProgram(_programID);
	//enable all the attributes we added with addAttribute
	for (int i = 0; i < _numAttributes_in; i++) {
		glEnableVertexAttribArray(i);
	}
}

//disable the shader
void GLSLCompliation::unuse() {
	glUseProgram(0);
	for (int i = 0; i < _numAttributes_in; i++) {
		glDisableVertexAttribArray(i);
	}
}



void GLSLCompliation::checkCompliation(GLuint shader, const str& type)
{
	if (shader == 0 && type == "vtx")
		err.fatalErrShader("Compliation Shader Fail " , "Vertex Shader");
	else if (shader == 0 && type == "frag")
		err.fatalErrShader("Compliation Shader Fail ", "Fragment Shader");
	else if(shader == 0)
		err.fatalErrShader("Compliation Shader Fail", "Unkown");


}

void GLSLCompliation::checkFileErr(const str&path)
{
	if (shader_file.fail()) {
		err.fatalErrFile(path);
	}
}


void GLSLCompliation::checkErrFileCompile(const str& type)
{
	if (status == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vtx_shader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(vtx_shader, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		cout << errorLog[0] << endl;
		// Exit with failure.
		glDeleteShader(vtx_shader); // Don't leak the shader.
		
		//print the error log and quit
		std::printf("%s\n", &(errorLog[0]));

		 err.fatalErr( type + " Shader Failed to Compile");

		return;

	}
}

///Open File
///Read Data
///Compile Shaders
void GLSLCompliation::compileShaders(const str& vertexShaderFilePath,const str& fragShaderFilePath)
{
	//Get a program object.
	_programID = glCreateProgram();
	vtx_shader =  glCreateShader(GL_VERTEX_SHADER);
	this->checkCompliation(vtx_shader,"vtx");
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	this->checkCompliation(frag_shader, "frag");

	glCompileShader(vtx_shader);
	glCompileShader(frag_shader);

	compileShader(vertexShaderFilePath, vtx_shader, "vert");
	compileShader(fragShaderFilePath,frag_shader,"frag");

}

void GLSLCompliation::compileShader(const str& filePath, GLuint shader_param, const str&type)
{
	cout << "TYPE : " << type << endl;
	shader_file.open(filePath);
	if (type == "vert")
		this->checkFileErr("vert");
	else if(type == "frag")
		this->checkFileErr("frag");
	else
		this->checkFileErr("Unkown");


	while (std::getline(shader_file, line_read)) {
		file_content += line_read + "\n";
	}

	shader_file.close();

	//Getting Source.
	//All text in 1 string, file_content
	//get a pointer to our file contents c string;
	const char* contentsPtr = file_content.c_str();
	//tell opengl that we want to use fileContents as the contents of the shader file
	glShaderSource(shader_param, 1, &contentsPtr, nullptr);

	glCompileShader(shader_param);
	//Check Errors For Vtx Shader File.
	glGetShaderiv(shader_param, GL_COMPILE_STATUS, &status);
	
	if (type == "vert")
		this->checkErrFileCompile("Vertex");
	else if (type == "frag")
		this->checkErrFileCompile("Fragment");
	else
		this->checkErrFileCompile("Unkown");

}


GLSLCompliation::~GLSLCompliation()
{
}
