#pragma once
#include "ObjectManager.h"

class Bullet : public GameObject
{
public:
	Bullet(ObjectManager& TheObjectManager);
	void Initialise(Vector2D location, float angle);
	void update()override;
	IShape2D& GetShape();
	void ProcessCollision(GameObject* object, Vector2D location, float angle) override;
	Vector2D m_velocity;
	Circle2D m_collisionShape;
	ObjectManager& om;
private:
	Vector2D Velocity;
	const float frameTime = 0.016f;
	const float deleationDelay = 5.0f;
	float timer;
};

