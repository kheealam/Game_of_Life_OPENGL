#include "Game.h"


/*
"GAME OF LIFE" RULES:

1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by over-population.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

*/



Game::Game(int n)
{
	gridDimensions = n*n;
	grid = new int[gridDimensions];
	for (int i = 0; i < gridDimensions; ++i){
		grid[i] = 0;
	}

	//GLIDER
	grid[3 * n + 18] = 1;
	grid[3 * n + 17] = 1;

	grid[4 * n + 16] = 1;

	grid[5 * n + 15] = 1;
	grid[6 * n + 15] = 1;
	grid[7 * n + 15] = 1;

	grid[8 * n + 16] = 1;

	grid[9 * n + 18] = 1;
	grid[9 * n + 17] = 1;

	grid[6 * n + 19] = 1;

	grid[4 * n + 20] = 1;
	grid[8 * n + 20] = 1;

	grid[5 * n + 21] = 1;
	grid[6 * n + 21] = 1;
	grid[7 * n + 21] = 1;

	grid[6 * n + 22] = 1;

	//GUN
	grid[1 * n + 29] = 1;
	grid[2 * n + 29] = 1;

	grid[2 * n + 27] = 1;

	grid[3 * n + 25] = 1;
	grid[3 * n + 26] = 1;
	grid[4 * n + 25] = 1;
	grid[4 * n + 26] = 1;
	grid[5 * n + 25] = 1;
	grid[5 * n + 26] = 1;
	grid[6 * n + 27] = 1;
	grid[6 * n + 29] = 1;
	grid[7 * n + 29] = 1;

	//BOX LEFT
	grid[5*n+5] = 1;
	grid[5 * n + 6] = 1;
	grid[6 * n + 5] = 1;
	grid[6 * n + 6] = 1;

	//BOX RIGHT
	grid[3 * n + 39] = 1;
	grid[3 * n + 40] = 1;
	grid[4 * n + 39] = 1;
	grid[4 * n + 40] = 1;


	vertices = new GLfloat[gridDimensions * 2 * 6];
	float gap = 2.0 / n;
	float gapHalf = gap /2.0;
	int j = 0;
	float con = 0.001;
	GLfloat startPosition[12]={ -gapHalf + con, gapHalf - con,
		-gapHalf + con, -gapHalf + con,
		gapHalf - con, -gapHalf + con,
		//SecondTriangle
		gapHalf - con, -gapHalf + con,
		gapHalf - con, gapHalf - con,
		-gapHalf + con, gapHalf - con};
	for (int i = 0; i < gridDimensions; ++i){
	
		float x=-(1-gapHalf)+((i%n)*gap);
		float y=(1-gapHalf)-((i/n)*gap);
//		for (; j < 2*(i+1); ++j){
			vertices[i * 2] = x;//startPosition[((j*2)%12)]+x;
			vertices[i * 2 + 1] = y;//startPosition[((j*2)%12) + 1] + y;
//		}
	}

	GLuint a;
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &cellStateBuffer);
	glGenBuffers(1, &a);
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, a);
		glBufferData(GL_ARRAY_BUFFER, 12 *sizeof(GLfloat), startPosition, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribDivisor(0, 0);


		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, gridDimensions * 2 * 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribDivisor(1, 1);

		glBindBuffer(GL_ARRAY_BUFFER, cellStateBuffer);
		glBufferData(GL_ARRAY_BUFFER, gridDimensions * sizeof(GLint), grid, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribDivisor(2, 1);

	glBindVertexArray(0);
}		

double time = 0;
int moveCount = 0;
double lastTime = 0;
void Game::draw(double deltaTime){
	time += deltaTime;
	if ((time * 1000) - (lastTime * 1000) > 30){
		lastTime = time;
		nextGen();
		glBindBuffer(GL_ARRAY_BUFFER, cellStateBuffer);
		glBufferData(GL_ARRAY_BUFFER, gridDimensions * sizeof(GLint), grid, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 1, GL_INT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribDivisor(2, 1);
	}
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, gridDimensions);
	

}

void Game::nextGen(){

	std::map<int, std::vector<int>> cells;
	for (int i = 0; i < gridDimensions; ++i){
		int t = grid[i];
		int count = countAlive(grid, i);
		int a = shouldLive(count, t);
		if (t != a){
			cells[a].push_back(i);
		}
	}
	for (int i = 0; i < cells[0].size(); ++i){
	
		grid[cells[0].at(i)] = 0;
	}
	for (int i = 0; i < cells[1].size(); ++i){

		grid[cells[1].at(i)] = 1;
	}
}
int Game::shouldLive(int alive,int isAlive){
	if (isAlive && alive < 2){
	
		return 0;
	}
	if (isAlive && (alive == 2 || alive == 3)){
	
		return 1;
	}
	if (isAlive && alive>3){
	
		return 0;
	
	}
	if (!isAlive && alive == 3){
	
		return 1;
	}
	return 0;

}
int Game::countAlive(int *grid, int index){

	int dimension = sqrt(gridDimensions);
	int alive = 0;
	int startPoint = index - dimension - 1;
	int currentIndex =-1;
	for (int i = 0; i < 9; ++i){
		currentIndex = startPoint + (i / 3) * dimension + i % 3;
		if (currentIndex != index && currentIndex >= 0 && currentIndex < gridDimensions)
		{
			alive += grid[currentIndex];
		}
	}
	return alive;

}
Game::~Game()
{
}