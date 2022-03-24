#include "Rock.h"
#include <iostream>

Rock::Rock(ObjectManager& TheObjectManager) : om(TheObjectManager) {
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
	om.AddObject(this);
}

IShape2D& Rock::GetShape() {
	m_collisionShape.PlaceAt(pos, 32);
	return m_collisionShape;
}

void Rock::ProcessCollision(GameObject* object, Vector2D location, float angle) {
	active = false;
	int random = (rand() % 4 - 1);
	for (int i = 0; i < random; i++) {
		SubRock* pSubRock = new SubRock(om);
		pSubRock->Initialise(location, angle);
	}
	Explosion* pExplosion = new Explosion(om);
	pExplosion->Initialise(location);
	//SubRock::splitOff(pos, angle);
}

