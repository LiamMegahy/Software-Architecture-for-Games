#pragma once
#include "mydrawengine.h"
#include "GameObject.h"
#include "Explosion.h"
#include "Bullet.h"
#include "Reward.h"

class LevelManager;
class ObjectManager;

class MeleeRock : public GameObject {
public:
	MeleeRock();
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
	float timer;
	const float frameTime = 0.016f;
};