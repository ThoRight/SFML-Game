#ifndef PHYSICS_H
#define PHYSICS_H
#include "Entity.h"
class Physics
{
public:
	Vec2 getOverlap(Entity* a, Entity* b);
	Vec2 getPreviousOverlap(Entity* a, Entity* b);
	bool isCollision(Entity* a, Entity* b);
};

#endif

