#pragma once

#include "Snake.h"
#include "raylib.h"
#include "grid.h"
#include "Food.h"

class Application
{
public:
	Application(unsigned int screenWidth, unsigned int windowHeight);
	void Run();
	void HandelGameEvent(Snake& snake);
	void GameOver();
	void DrawGameOverMenu(Rectangle &buttonPlayAgain, Rectangle &buttonQuit);
	void HandelGameOverEvent(Rectangle &buttonPlayAgain, Rectangle &buttonQuit);
	void Draw(Grid &grid, Snake &snake, Food &food) const;
	void Update(Snake &snake, Food &food, Grid &grid, int &frameCount);
private:
	unsigned int screenWidth;
	unsigned int ScreenHeight;
	unsigned int FPS;
	bool gameOver = false;
	bool running = true;
	bool playAgain = false;
};