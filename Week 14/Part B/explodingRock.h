#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "SubRock.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Reward.h"

class LevelManager;
class ObjectManager;

class explodingRock : public GameObject {
public:
	explodingRock();
	void Initialise(Vector2D location, float angle, ObjectManager* Pom, LevelManager* plm);
	void update();
	IShape2D& GetShape();
	void ProcessCollision(GameObject& object) override;
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