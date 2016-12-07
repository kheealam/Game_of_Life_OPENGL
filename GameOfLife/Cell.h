#include<GL\glew.h>
#pragma once
class Cell
{
public:

	Cell::Cell(float x, float y, float gap);
	~Cell();
private:
	GLfloat vertices[3 * 6];
	GLuint VAO;
	GLuint vertexBuffer;
};

