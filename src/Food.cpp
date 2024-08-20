#include "Food.h"


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
	Position randomPos = grid.GetRandomCell();
	foodRect.x = (float) randomPos.x + offset;
	foodRect.y = (float)randomPos.y + offset;

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
