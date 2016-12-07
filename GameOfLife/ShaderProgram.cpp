#include "ShaderProgram.h"


ShaderProgram::ShaderProgram()
{
	m_programObject = glCreateProgram();
}
Shader ShaderProgram::getVertexShader(){
	return m_vertexShader;
}
Shader ShaderProgram::getFragmentShader(){
	return m_fragmentShader;
}

GLuint ShaderProgram::getProgramObject(){
	return m_programObject;

}

void ShaderProgram::attachShader(Shader shader){

	if (shader.getShaderType() == GL_VERTEX_SHADER){
	
		glDetachShader(m_programObject,m_vertexShader.getShaderObject());
		m_vertexShader = shader;	
	}
	else if (shader.getShaderType() == GL_FRAGMENT_SHADER){
		glDetachShader(m_programObject, m_fragmentShader.getShaderObject());
		m_fragmentShader = shader;
	}
	glAttachShader(m_programObject, shader.getShaderObject());
}
void ShaderProgram::link(){

	//glDetachShader(m_programObject, m_vertexShader.getShaderObject());
	//glDetachShader(m_programObject, m_fragmentShader.getShaderObject());

	//glDeleteShader(m_vertexShader.getShaderObject());
	//glDeleteShader(m_fragmentShader.getShaderObject());

	glLinkProgram(m_programObject);

	glDetachShader(m_programObject, m_vertexShader.getShaderObject());
	glDetachShader(m_programObject, m_fragmentShader.getShaderObject());

	glDeleteShader(m_vertexShader.getShaderObject());
	glDeleteShader(m_fragmentShader.getShaderObject());

	GLint isLinkSuccess;

	glGetProgramiv(m_programObject, GL_LINK_STATUS, &isLinkSuccess);
	if (!isLinkSuccess){
	
		GLchar info[512];
		glGetProgramInfoLog(m_programObject, 512, NULL, info);
		std::cout << info << std::endl;
	}
}
void ShaderProgram::use(){
	glUseProgram(m_programObject);
}
ShaderProgram::~ShaderProgram()
{
}
