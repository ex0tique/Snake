#include "Application.h"

#include <iostream>

Application::Application(unsigned int screenWidth, unsigned int ScreenHeight)
	: screenWidth(screenWidth), ScreenHeight(ScreenHeight)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, ScreenHeight, "Snake");
	FPS = 60;
	SetTargetFPS(FPS);
}

void Application::Run()
{
	int frameCount = 0;
	unsigned int gridSize = 30;
	Grid grid(screenWidth, ScreenHeight);
	Snake snake(grid);
	Food food(grid);


	while (!WindowShouldClose() && running)
	{
		if (IsWindowResized())
		{
			screenWidth = GetRenderWidth();
			ScreenHeight = GetRenderHeight();
		}
		if (!gameOver)
		{
			Update(snake, food, grid, frameCount);
			Draw(grid, snake, food);
		}
		else
			GameOver();

	}
		
	CloseWindow();
}

void Application::HandelGameEvent(Snake& snake)
{
	if (IsKeyPressed(KEY_UP)) {
		if (snake.GetDirection() != DOWN)
			snake.SetDirection(UP);
	}
		
	else if (IsKeyPressed(KEY_DOWN))
	{
		if (snake.GetDirection() != UP)
			snake.SetDirection(DOWN);
	}
		
	else if (IsKeyPressed(KEY_RIGHT))
	{ 
		if (snake.GetDirection() != LEFT)
			snake.SetDirection(RIGHT);
	}
		
	else if (IsKeyPressed(KEY_LEFT))
	{
		if (snake.GetDirection() != RIGHT)
			snake.SetDirection(LEFT);
	}
		
}

void Application::GameOver()
{
	Rectangle buttonPlayAgain{ 100, 450, 250, 75 };
	Rectangle buttonQuit{ 500, 450, 250, 75 };
	DrawGameOverMenu(buttonPlayAgain, buttonQuit);
	HandelGameOverEvent(buttonPlayAgain, buttonQuit);
}

void Application::DrawGameOverMenu(Rectangle &buttonPlayAgain, Rectangle &buttonQuit)
{
	BeginDrawing();
	DrawText(TextFormat("Game Over"), 25 , ScreenHeight/2 - 150, screenWidth/6, RED);

	DrawRectangleRec(buttonPlayAgain, BLACK);
	DrawText(TextFormat("Play again"), 100, 450, 50, WHITE);
	
	DrawRectangleRec(buttonQuit, BLACK);
	DrawText(TextFormat("Quit"), 550, 450, 50, WHITE);

	EndDrawing();
}

void Application::HandelGameOverEvent(Rectangle &buttonPlayAgain, Rectangle &buttonQuit)
{
	Vector2 mousePoint = { GetMousePosition() };
	if (CheckCollisionPointRec(mousePoint, buttonPlayAgain))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			gameOver = false;
	}
	else if (CheckCollisionPointRec(mousePoint, buttonQuit))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			running = false;
	}
	
}

void Application::Draw(Grid &grid, Snake &snake, Food &food) const
{
	BeginDrawing();
	grid.Draw();
	food.DrawFood();
	snake.Draw();
	ClearBackground(BLACK);
	EndDrawing();
}

void Application::Update(Snake &snake, Food &food, Grid& grid, int &frameCount)
{
	HandelGameEvent(snake);
	if (frameCount > 60 / 6)
	{
		if (food.IsEaten( snake.GetHead() ))
		{
			snake.AddBodyPart();
			food.GenerateNewFood();
		}
		snake.Update(); 

		if (snake.CheckCollision())
			gameOver = true;
		frameCount = 0;
	}
	else
		frameCount++;
}

