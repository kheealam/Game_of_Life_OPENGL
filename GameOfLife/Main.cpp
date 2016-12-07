#include <iostream>
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "Game.h"

#define DIMENSIONS 50

void drawGrid(int n);
GLuint vertexBuffer;
GLuint VAO;
Game *g;
int main(int argc, char**argv){

	
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	GLFWwindow* window = glfwCreateWindow(1080, 1080, "Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glewInit();

	VertexShader vShader("vLineShader.glsl");
	FragmentShader fShader("fLineShader.glsl");

	VertexShader vCellShader("vCellShader.glsl");
	FragmentShader fCellShader("fCellShader.glsl");

	ShaderProgram program;
	ShaderProgram cellProgram;
	cellProgram.attachShader(vCellShader);
	cellProgram.attachShader(fCellShader);
	program.attachShader(vShader);
	program.attachShader(fShader);
	program.link();
	cellProgram.link();
	g = new Game(DIMENSIONS);
	drawGrid(DIMENSIONS);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	double deltaTime = 0;
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		
		program.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, DIMENSIONS * 4);
		cellProgram.use();
		g->draw(deltaTime);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();



	return 0;
}
void drawGrid(int n){
	GLfloat *vertices=new GLfloat[2*n*4];
	GLfloat gap = 2.0 / n;
	GLfloat distance = -1.0;

	for (int i = 0; i < 2*n*4; i+=8){
		distance += gap;
		vertices[i] = distance;
		vertices[i + 1] = 1.0;
		vertices[i + 2] = distance;
		vertices[i + 3] = -1.0;

		vertices[i + 4] = -1.0;
		vertices[i + 5] = distance;
		vertices[i + 6] = 1.0;
		vertices[i + 7] = distance;
	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexBuffer);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, 2*n*4 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}