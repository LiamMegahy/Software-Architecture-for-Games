#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "SubRock.h"
#include "ObjectManager.h"
class Rock : public GameObject {
public:
	Rock();
	ObjectManager* om;
	void Initialise(Vector2D location, float angle);
	void update();
	IShape2D& GetShape();
	void ProcessCollision(GameObject& object) override;
	Vector2D m_velocity;
	Circle2D m_collisionShape;
	Vector2D Velocity;
};