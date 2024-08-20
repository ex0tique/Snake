#include "Snake.h"

#include <iostream>
Snake::Snake(Grid &grid)
	: grid(grid), direction(RIGHT)
{
		bodyPartWidth = grid.GetCellWidth() - 6;
		bodyPartHeight = grid.GetCellHeight() - 6;
	int offset = 3;
	int xStartPos = 8 * grid.GetCellWidth() + offset;
	int yStartPos = 3 * grid.GetCellHeight() + offset;

	int startBodySize = 8;

	for (int i = 0; i < startBodySize; i++)
	{
		Rectangle bodypartRect = CreateBodyPartRect((float) (xStartPos - i * grid.GetCellWidth()), (float)yStartPos, (float)bodyPartWidth, (float)bodyPartHeight);
		std::pair<Rectangle, int> bodyPart(bodypartRect, direction);
		body.push_back(bodyPart);
	}
	head.x = body[0].first.x;
	head.y = body[0].first.y;
	head.width = (float)bodyPartWidth;
	head.height = (float)bodyPartHeight;
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
	int bodyXPos = body[0].first.x;
	int bodyYPos = body[0].first.y;
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

Rectangle Snake::CreateBodyPartRect(float x, float y, int width, int height)
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

