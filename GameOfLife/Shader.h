#pragma once

#include <gl\glew.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
class Shader
{
protected:
	string m_source;
	GLuint m_shaderObject;
	GLuint m_shaderType;
	string m_filePath;
	GLint m_compileStatus;


	GLint compileShader(GLuint shaderObject, string &errMsg);
	string textFileRead(const char * filename);
	void init();
public:
	GLuint getShaderObject();
	GLuint getShaderType();
	
	~Shader();
};

