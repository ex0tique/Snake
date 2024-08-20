#pragma once

struct Position 
{
	float x;
	float y;
};

class Grid
{

public:
	Grid(int screenWidth, int screenHeight);
	void Draw() const;
	int GetRows() const { return rows; }
	int GetColumns() const { return columns; }
	int GetCellWidth() const { return cellWidth; }
	int GetCellHeight() const { return cellHeight; }
	Position GetRandomCell() const;
	
private:
	int cellWidth;
	int cellHeight;
	int rows{32};
	int columns{32};
};