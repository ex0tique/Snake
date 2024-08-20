#pragma once
#include "raylib.h"
#include "grid.h"

class Food
{
public:
	Food(Grid &grid);
	Rectangle GetFoodRect() const { return foodRect; }
	void GenerateNewFood() ;
	void DrawFood() const;
	bool IsEaten(Rectangle const &head) const;
private:
	Grid grid;
	Rectangle foodRect;
	float offset;
};