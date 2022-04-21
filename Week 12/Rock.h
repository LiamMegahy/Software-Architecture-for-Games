#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "SubRock.h"
#include "Explosion.h"
#include "Bullet.h"

class LevelManager;
class ObjectManager;

class Rock : public GameObject {
public:
	Rock();
	void Initialise(Vector2D location, float angle, ObjectManager* Pom, LevelManager* plm);
	void update();
	void fireGun();
	void ProcessCollision(GameObject& object) override;
	IShape2D& GetShape();
	ObjectManager* om;
	LevelManager* lm;
	Vector2D m_velocity;
	Circle2D m_collisionShape;
	Vector2D Velocity;
private:
	const float shotDelay = 0.5f;
	float timer;
	const float frameTime = 0.016f;
};