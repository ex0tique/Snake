#include "Application.h"

#include <iostream>
#include <time.h>


Application::Application(unsigned int screenWidth, unsigned int ScreenHeight)
	: screenWidth(screenWidth), ScreenHeight(ScreenHeight)
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, ScreenHeight, "Snake");
	FPS = 60;
	SetTargetFPS(FPS);
	srand((unsigned int)time(0)); // Need for Randomness
}

void Application::Run()
{
	int frameCount = 0;
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
		else if (playAgain)
		{
			snake.CreateNewSnake();
			playAgain = false;
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
	float buttonWidth{ (screenWidth / 3.0f)};
	float buttonHeight{ (ScreenHeight / 12.0f )};
	Rectangle buttonPlayAgain{	(screenWidth / 10.0f), (ScreenHeight / 2.0f), buttonWidth, buttonHeight };
	Rectangle buttonQuit{		(screenWidth - buttonWidth - (screenWidth / 10.0f)), (ScreenHeight / 2.0f), buttonWidth, buttonHeight };
	DrawGameOverMenu(buttonPlayAgain, buttonQuit);
	HandelGameOverEvent(buttonPlayAgain, buttonQuit);
}

void Application::DrawGameOverMenu(Rectangle &buttonPlayAgain, Rectangle &buttonQuit)
{
	BeginDrawing();
	DrawText(TextFormat("Game Over"), 25 , ScreenHeight/2 - 150, screenWidth/6, RED);

	int textSize = (int)(buttonPlayAgain.height * 0.8);

	DrawRectangleRec(buttonPlayAgain, BLACK);
	DrawText(TextFormat("Play again"), (int)buttonPlayAgain.x, (int)buttonPlayAgain.y, textSize, WHITE);
	
	DrawRectangleRec(buttonQuit, BLACK);
	DrawText(TextFormat("Quit"), (int)(buttonQuit.x + buttonQuit.width/2 - textSize), (int)buttonQuit.y , textSize, WHITE);

	EndDrawing();
}

void Application::HandelGameOverEvent(Rectangle &buttonPlayAgain, Rectangle &buttonQuit)
{
	Vector2 mousePoint = { GetMousePosition() };
	if (CheckCollisionPointRec(mousePoint, buttonPlayAgain))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			playAgain = true;
			gameOver = false;
		}
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
	ClearBackground(DARKGRAY);
	grid.Draw();
	food.DrawFood();
	snake.Draw();
	EndDrawing();
}

void Application::Update(Snake &snake, Food &food, Grid& grid, int &frameCount)
{
	HandelGameEvent(snake);
	AutoPlay(snake, food);

	if (true)
	{
		if (food.IsEaten( snake.GetHead() ))
		{
			snake.AddBodyPart();
			food.GenerateNewFood();
		}
		snake.Update();

		if (snake.CheckCollision() || snake.OutOfScreen())
			gameOver = true;

		frameCount = 0;
	}
	else
		frameCount++;
}

void Application::AutoPlay(Snake& snake, Food& food)
{
	int direction{snake.GetDirection()};
	Rectangle headRect = snake.GetHead();
	Rectangle foodRect = food.GetFoodRect();

	if (foodRect.x < headRect.x)
		direction = LEFT;
	else if (foodRect.x > headRect.x)
		direction = RIGHT;
	else if (foodRect.y < headRect.y)
		direction = UP;
	else if (foodRect.y > headRect.y)
		direction = DOWN;
	
	Snake nextUpdateSnake = snake;
	nextUpdateSnake.SetDirection(direction);
	nextUpdateSnake.Update();
	std::cout << "New State: " << "Collision: " << nextUpdateSnake.CheckCollision() << " Out Of Bound: " << nextUpdateSnake.OutOfScreen()
		<< " Direction: " << direction << std::endl;
	if (nextUpdateSnake.CheckCollision() || nextUpdateSnake.OutOfScreen())
		std::cout << "Colision incoming..." << std::endl;

	while (nextUpdateSnake.CheckCollision() || nextUpdateSnake.OutOfScreen())
	{
		if (direction >= 4)
			direction = UP;
		else
			direction++;
		nextUpdateSnake = snake; // go Back to previous state
		nextUpdateSnake.SetDirection(direction);
		nextUpdateSnake.Update();
		std::cout << "changed direction to: " << direction << std::endl;
	}
	snake.SetDirection(direction);
}