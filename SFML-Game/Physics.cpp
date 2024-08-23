#include "Physics.h"
Vec2 Physics::getOverlap(Entity* a, Entity* b)
{
	float distanceX = abs(a->cTransform->position.x - b->cTransform->position.x);
	float distanceY = abs(a->cTransform->position.y - b->cTransform->position.y);
	float totalX = a->cBoundingBox->size.x / 2 + b->cBoundingBox->size.x/2;
	float totalY = a->cBoundingBox->size.y / 2 + b->cBoundingBox->size.y/2;
	return Vec2(totalX - distanceX, totalY - distanceY);
}
Vec2 Physics::getPreviousOverlap(Entity* a, Entity* b)
{
	float distanceX = abs(a->cTransform->prevPosition.x - b->cTransform->prevPosition.x);
	float distanceY = abs(a->cTransform->prevPosition.y - b->cTransform->prevPosition.y);
	float totalX = a->cBoundingBox->size.x / 2 + b->cBoundingBox->size.x / 2;
	float totalY = a->cBoundingBox->size.y / 2 + b->cBoundingBox->size.y / 2;
	return Vec2(totalX - distanceX, totalY - distanceY);
}
bool Physics::isCollision(Entity* e1, Entity* e2)
{
	Physics p;
	Vec2 v = p.getOverlap(e1, e2);
	Vec2 v2 = p.getPreviousOverlap(e1, e2);
	e1->cBoundingBox->preOverlapX = v2.x;
	e1->cBoundingBox->preOverlapY = v2.y;
	if (v.x > 0 && v.y > 0)
	{
		e1->cBoundingBox->overlapX = v.x;
		e1->cBoundingBox->overlapY = v.y;
		return true;
	}
	return false;
}
