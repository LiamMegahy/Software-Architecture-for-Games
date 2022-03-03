#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "myinputs.h"
class Spaceship {
private:
	Vector2D velocity;
	Vector2D pos;
	float direction;
	const int rotation = 4;
	const float frameTime = 0.016;
	bool isActive;
	PictureIndex model;
	SoundIndex shootSound;
	MyDrawEngine* pDE;
public:
	Spaceship();
	void render();
	void initialise(Vector2D location);
	void update();
	void move();
};