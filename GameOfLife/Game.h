#include<map>
#include<GL\glew.h>
#include<vector>
#pragma once
class Game
{
public:
	Game(int n);
	~Game();
	void draw(double deltaTime);
	GLuint VAO;
private:
	int gridDimensions;
	GLuint vertexBuffer;
	GLuint cellStateBuffer;
	
	GLfloat *vertices;
	GLfloat *startPosition;
	int Game::countAlive(int *grid, int index);
	int Game::shouldLive(int alive, int isAlive);
	int *grid;
	void nextGen();
};

