#pragma once
#include "GameObject.h"
#include "mydrawengine.h"
#include "GameObject.h"
#include "SubRock.h"
class Rock : public GameObject {
public:
	Rock();
	void Initialise(Vector2D location, float angle);
	void update();
	IShape2D& GetShape();
	void ProcessCollision(GameObject* object);

	Vector2D m_velocity;
	Circle2D m_collisionShape;
	Vector2D Velocity;
};