#include "Snake.h"

#include <iostream>
Snake::Snake(Grid &grid)
	: grid(grid)
{
		bodyPartWidth = (float)(grid.GetCellWidth() - 6);
		bodyPartHeight = (float)(grid.GetCellHeight() - 6);
		CreateNewSnake();
}

void Snake::Draw() const
{
	for (auto& bodyPart : body)
	{
		DrawRectangleRec(bodyPart.first, GREEN);
	}
}

void Snake::Update()
{
	body.pop_back();
	float bodyXPos = body[0].first.x;
	float bodyYPos = body[0].first.y;
	switch (direction)
	{
	case UP:
		head.x = bodyXPos;
		head.y = bodyYPos - grid.GetCellHeight();
		break;
	case DOWN:
		head.x = bodyXPos;
		head.y = bodyYPos + grid.GetCellHeight();
		break;
	case RIGHT:
		head.x = bodyXPos + grid.GetCellWidth();
		head.y = bodyYPos;
		break;
	case LEFT:
		head.x = bodyXPos - grid.GetCellWidth();
		head.y = bodyYPos;
		break;
	}
	body.insert(body.begin(), std::pair<Rectangle, int>(head, direction));
}

bool Snake::CheckCollision() const
{

	for (int i = 1; i < body.size(); i++)
	{
		Rectangle bodyPartRect = body[i].first;
		if (CheckCollisionRecs(head, bodyPartRect))
			return true;
	}
	return false;
}

Rectangle Snake::CreateBodyPartRect(float x, float y, float width, float height)
{
	Rectangle bodypart{ x, y, width, height};
	return bodypart;
}

void Snake::AddBodyPart()
{
	Rectangle lastBodyPartRect = body.back().first;
	Rectangle newLastBodypartRect{ lastBodyPartRect.x, lastBodyPartRect.y, lastBodyPartRect.width, lastBodyPartRect.height };

	body.push_back(std::pair<Rectangle, int>(newLastBodypartRect, direction));
}

void Snake::CreateNewSnake()
{
	body.clear();

	direction = RIGHT;
	int offset = 3;
	Position startPos = grid.GetRandomCell();

	int startBodySize = 8;

	for (int i = 0; i < startBodySize; i++)
	{
		Rectangle bodypartRect = CreateBodyPartRect((float)(startPos.x - i * grid.GetCellWidth() + offset), float(startPos.y) + offset, bodyPartWidth, bodyPartHeight);
		std::pair<Rectangle, int> bodyPart(bodypartRect, direction);
		body.push_back(bodyPart);
	}
	head.x = body[0].first.x;
	head.y = body[0].first.y;
	head.width = bodyPartWidth;
	head.height = bodyPartHeight;
}

