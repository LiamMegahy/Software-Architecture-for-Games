#pragma once
#include "Rock.h"
#include "Explosion.h"

class ObjectManager;
class LevelManager;

class SubRock : public GameObject {
public:
	SubRock();
	void Initialise(Vector2D location, float angle, ObjectManager* Pom, LevelManager* plm);
	void ProcessCollision(GameObject& object);
	void update();
	IShape2D& GetShape();
	Circle2D m_collisionShape;
	Vector2D Velocity;
	ObjectManager* om;
	LevelManager* lm;
};

