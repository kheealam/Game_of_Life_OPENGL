#include "FragmentShader.h"


FragmentShader::FragmentShader(const string filePath)
{
	m_shaderType = GL_FRAGMENT_SHADER;
	m_filePath = filePath;
	init();
}


FragmentShader::~FragmentShader()
{
}
