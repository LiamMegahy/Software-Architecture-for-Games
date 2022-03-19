#include "Rock.h"
#include <iostream>

Rock::Rock() {
	active = true;
	//When the constructor is run, setting active to true so the ObjectManager knows this is an active game object
	GameObject::loadImage(L"rock1.bmp");
	//Providing an image file reference to be loaded upon its construction
}

void Rock::update() {
	pos = pos + Velocity * 0.016;
	//Causing the position of the rock to be constantly moving, based upon its velocity and * by frametime
}

void Rock::Initialise(Vector2D location, float angle) {
	Velocity.setBearing(angle, 50.0f);
	//Setting the bearing to be based on the provided value as part of Initailised parameters
	pos = location;
	//The position of the rock is based upon the Vector2D value provided
	this->angle = angle;
}