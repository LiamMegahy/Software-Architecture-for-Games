#pragma once
#include "Rock.h"
//#include "ObjectManager.h"
class SubRock : public Rock{
public:
	SubRock(ObjectManager& TheObjectManager);
	ObjectManager& om;
	void Initialise(Vector2D location, float angle);
	void ProcessCollision(GameObject* object, Vector2D location, float angle);
	IShape2D& GetShape();
};

