#pragma once

#include "Shader.h"
class VertexShader:public Shader
{
public:
	VertexShader(const string filePath);
	~VertexShader();
};

