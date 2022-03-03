#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "myinputs.h"
#include "GameObject.h"

class Spaceship : public GameObject {
private:
	Vector2D velocity;
	Vector2D friction;
	const int rotation = 4;
	const float frameTime = 0.016f;
	Vector2D gravity;
	PictureIndex model;
	SoundIndex shootSound;
public:
	Spaceship();
	void initialise(Vector2D location);
	void update();
	void move();
};