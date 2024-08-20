#pragma once


class Grid
{

public:
	Grid(int screenWidth, int screenHeight);
	void Draw() const;
	int GetRows() const { return rows; }
	int GetColumns() const { return columns; }
	int GetCellWidth() const { return cellWidth; }
	int GetCellHeight() const { return cellHeight; }
private:
	int cellWidth;
	int cellHeight;
	int rows{32};
	int columns{32};
};