#pragma once
#include <list>
#include <string>
#include "vector2D.h"
#include "GameObject.h"
#include "PlayerCharacter.h"

class Reward : public GameObject {
private:
	Circle2D m_collisionShape;
public:
	Reward();
	void dropReward(Vector2D pos);
	void ProcessCollision(GameObject& object) override;
	void Initialise(Vector2D location, float angle);
	IShape2D& GetShape();
};

