#include "Rock.h"
#include <iostream>

Rock::Rock() {
	active = true;
	loadImage(L"rock1.bmp");
}

void Rock::update() {
	pos = pos + Velocity * 0.01;
}

void Rock::Initialise(Vector2D location, float angle) {
	int random = (rand() % 6 - 1);
	GameObject::loadImage(L"rock1.bmp");
	Velocity.setBearing(angle, 50.0f);
	pos = location;
	this->angle = angle;
}