#include "Shader.h"
#pragma once
class ShaderProgram
{
private:
	GLuint m_programObject;
	Shader m_vertexShader;
	Shader m_fragmentShader;
	
public:
	GLuint getProgramObject();
	Shader getVertexShader();
	Shader getFragmentShader();
	//detaches shaders and deletes them
	void link();
	void attachShader(Shader shader);
	void use();
	ShaderProgram();
	~ShaderProgram();
};

