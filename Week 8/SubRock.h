#pragma once
#include "Rock.h"
#include "ObjectManager.h"
class SubRock : public Rock{
public:
	SubRock();
	void Initialise(Vector2D location, float angle);
	void splitOff(Vector2D location, float angle);
	void ProcessCollision(GameObject* object);
};

