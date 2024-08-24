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
			DrawRectangleLines(column * cellWidth, row * cellHeight, cellWidth, cellHeight, BLACK);
		}
	}

}

Position Grid::GetRandomCell() const
{

	Position position;
	position.x = float((rand() % GetRows()) * GetCellWidth());
	position.y = float((rand() % GetColumns() * GetCellHeight()));
	return position;
}
