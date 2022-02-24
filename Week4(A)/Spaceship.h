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
	bool isActive;
	PictureIndex model;
	SoundIndex shootSound;
	MyDrawEngine* pDE;
public:
	Spaceship();
	void render(Vector2D location);
	void initialise(Vector2D location);
	void update();
	void move();
};