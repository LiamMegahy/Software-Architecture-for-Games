#include "Rock.h"
#include <iostream>
#include "ObjectManager.h"


Rock::Rock() {
	active = true;
	loadImage(L"rock1.bmp");
}

void Rock::update() {
	pos = pos + Velocity * 0.016;
}

void Rock::Initialise(Vector2D location, float angle) {
	int random = (rand() % 6 - 1);
	GameObject::loadImage(L"rock1.bmp");
	Velocity.setBearing(angle, 50.0f);
	pos = location;
	this->angle = angle;
}

IShape2D& Rock::GetShape() {
	m_collisionShape.PlaceAt(pos, 32);
	return m_collisionShape;
}

void Rock::ProcessCollision(GameObject* object) {
	active = false;
	SubRock::splitOff(pos, angle);
}

