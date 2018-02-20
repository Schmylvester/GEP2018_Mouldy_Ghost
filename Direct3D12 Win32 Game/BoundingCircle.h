#pragma once

#include "Collider.h"

class BoundingCircle
	: public Collider
{
public:
	BoundingCircle(Vector2 _center, int _radius);
	~BoundingCircle();

	virtual bool IsColliding(Collider* _object, Vector2 &_direction);
	virtual bool ContainsPoint(int x, int y);

protected:
	float radius;
};