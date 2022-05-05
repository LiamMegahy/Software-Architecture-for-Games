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
	virtual ~GameObject();
	virtual void render();
	virtual void update();
	void offScreen();
	virtual IShape2D& GetShape() = 0;
	virtual void ProcessCollision(GameObject& object) = 0;
	bool active;
	bool isActive() const;
	void deactivate();
protected:
	Vector2D pos;
	float angle;
	float scale = 1;
	PictureIndex loadImage(std::wstring fileName);
	void loadSound(std::wstring soundName);
};