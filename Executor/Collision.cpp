#include "Collision.h"
#include <cmath>

bool Collision::IsCircleHit(const Circle& first, const Circle& second)
{
	const float distanceX = first.x - second.x; // 二つの円の中心のX座標の差

	const float distanceY = first.y - second.y; // 二つの円の中心のY座標の差
	
	const float distanceSquared = distanceX * distanceX + distanceY * distanceY;
	
	const float radiusSum = first.radius + second.radius;
	
	return distanceSquared <= radiusSum * radiusSum;
}

bool Collision::IsRectangleHit(const CollisionRectangle& first, const CollisionRectangle& second)
{
	return false;
}

bool Collision::IsCircleRectangleHit(const Circle& circle, const CollisionRectangle& rectangle)
{
	return false;
}
