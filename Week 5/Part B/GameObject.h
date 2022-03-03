#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "myinputs.h"
#include <string>

class GameObject {
private:
	Vector2D position;
	PictureIndex image;
	PictureIndex model;
public:
	GameObject();
	void render();
	virtual void update();
protected:
	Vector2D pos;
	bool active;
	float angle;
	void loadImage(std::wstring fileName);
};