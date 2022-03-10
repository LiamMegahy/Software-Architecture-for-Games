#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "myinputs.h"
#include "GameObject.h"
#include "Bullet.h"

class Spaceship : public GameObject {
private:
	Vector2D velocity;
	Vector2D friction;
	const int rotation = 4;
	const float frameTime = 0.016f;
	const float shotDelay = 0.5f;
	float timer;
	Vector2D gravity;
	PictureIndex model;
	SoundIndex shootSound;
	ObjectManager &om;
public:
	Spaceship(ObjectManager& TheObjectManager);
	void initialise(Vector2D location);
	void update();
	void move();
};