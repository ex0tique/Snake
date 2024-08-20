#include "Food.h"
#include <cstdlib>
#include <typeinfo>

#include <iostream>
Food::Food(Grid &grid) : grid(grid)
{
	offset = 3;
	foodRect.width = grid.GetCellWidth() - offset * 2;
	foodRect.height = grid.GetCellHeight() - offset * 2;
	GenerateNewFood();
}


void Food::GenerateNewFood()
{
	xPos = (float)(rand() % grid.GetRows()) * grid.GetCellWidth() + offset;
	yPos = (float)(rand() % grid.GetColumns() * grid.GetCellHeight()) + offset;
	foodRect.x = xPos;
	foodRect.y = yPos;
}

void Food::DrawFood() const
{
	DrawRectangleRec(foodRect, RED);
}

bool Food::IsEaten(Rectangle const& head) const
{
	if (CheckCollisionRecs(head, foodRect))
	{
		return true;
	}
	return false;
}
