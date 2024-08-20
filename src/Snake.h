#pragma once

#include "raylib.h"
#include <vector>
#include "Food.h"
#include "grid.h"

#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

class Snake
{
public:
	Snake(Grid &grid);
	void Draw() const;
	void Update();
	bool CheckCollision() const;
	void SetDirection(int dir) { direction = dir; }
	Rectangle CreateBodyPartRect(float x, float y, int width, int height);
	void AddBodyPart();
	int GetDirection() const { return direction; }
	Rectangle GetHead() const { return head; }
private:
	Grid grid;
	std::vector<std::pair<Rectangle, int>> body;
	Rectangle head;
	int bodyPartWidth;
	int bodyPartHeight;
	int direction;
};