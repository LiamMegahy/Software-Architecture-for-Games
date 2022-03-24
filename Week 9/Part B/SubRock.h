#pragma once
#include "Rock.h"
#include "ObjectManager.h"
#include "Explosion.h"
class ObjectManager;

class SubRock : public GameObject {
public:
	SubRock();
	void Initialise(Vector2D location, float angle);
	void ProcessCollision(GameObject& object);
	IShape2D& GetShape();
	Circle2D m_collisionShape;
	Vector2D Velocity;
	ObjectManager* om;
};

