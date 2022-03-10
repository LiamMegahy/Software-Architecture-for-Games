#pragma once
#include "GameObject.h"
#include "mydrawengine.h"
#include "GameObject.h"
class Rock : public GameObject {
public:
	Rock();
	void Initialise(Vector2D location, float angle);
	void update();
private:
	Vector2D Velocity;

};