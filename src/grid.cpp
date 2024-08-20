#include "grid.h"
#include <raylib.h>
#include <random>



Grid::Grid(int screenWidth, int screenHeight)
{
	cellWidth = (screenWidth / rows);
	cellHeight = (screenHeight / columns);
}

void Grid::Draw() const
{
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++)
		{
			DrawRectangle(column * cellWidth, row * cellHeight, cellWidth - 1 , cellHeight -1 , DARKGRAY);
		}
	}

}

Position Grid::GetRandomCell() const
{

	Position position;
	position.x = (rand() % GetRows()) * GetCellWidth();
	position.y = (rand() % GetColumns() * GetCellHeight());
	return position;
}
