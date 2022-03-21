#pragma once
#include "GameObject.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "ObjectManager.h"
class Explosion : GameObject{
public:
	Explosion();
	void Initialise(Vector2D location);
	void explosion(Vector2D location);
	void Render();
	int currentImage;
	Vector2D pos;
private:
	
};

