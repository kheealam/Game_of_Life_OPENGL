#include "Cell.h"


Cell::Cell(float x, float y,float gap)
{
		vertices[0] = x;
		vertices[1] = y;
		vertices[2] = x+gap;
		vertices[3] = y;
		vertices[4] = x+gap;
		vertices[5] = y+gap;
		vertices[6] = x+gap;
		vertices[7] = y+gap;
		vertices[8] = x;
		vertices[9] = y+gap;
		vertices[10]= x;
		vertices[11]= y;

		glGenBuffers(1, &VAO);
		glGenBuffers(1, &vertexBuffer);
		glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, 160 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
			glEnableVertexAttribArray(0);

		glBindVertexArray(0);

}


Cell::~Cell()
{
}
