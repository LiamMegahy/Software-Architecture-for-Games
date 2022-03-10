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
	SoundIndex sound;
public:
	GameObject();
	void render();
	virtual void update();
	bool active;
protected:
	Vector2D pos;
	float angle;
	void loadImage(std::wstring fileName);
	void loadSound(std::wstring soundName);
};