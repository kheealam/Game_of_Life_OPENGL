#include "VertexShader.h"


VertexShader::VertexShader(const string filePath)
{
	m_shaderType = GL_VERTEX_SHADER;
	m_filePath = filePath;
	init();
}

VertexShader::~VertexShader()
{

}
