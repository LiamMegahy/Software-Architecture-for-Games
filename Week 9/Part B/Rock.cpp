#include "Rock.h"
#include <iostream>
#include "Explosion.h"
Rock::Rock() {
	active = true;
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

void Rock::ProcessCollision(GameObject& object) {
	active = false;
	int random = (rand() % 4 - 1);
	for (int i = 0; i < random; i++) {
		SubRock* pSubRock = new SubRock;
		pSubRock->Initialise(pos, angle);
		if (om) {
			om->AddObject(pSubRock);
		}
	}
	Explosion* pExplosion = new Explosion();
	pExplosion->Initialise(pos);
	if (om) {
		om->AddObject(pExplosion);
	}
}

