#include "Rock.h"
#include <iostream>
#include "Explosion.h"
#include "Bullet.h"
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

void Rock::Initialise(Vector2D location, float angle, ObjectManager* Pom) {
	Initialise(location, angle);
	om = Pom;
}

IShape2D& Rock::GetShape() {
	m_collisionShape.PlaceAt(pos, 32);
	return m_collisionShape;
}

void Rock::ProcessCollision(GameObject& object) {
	if (typeid(object) == typeid(Bullet)) {
		active = false;

		int random = (rand() % 6 - 1);
		for (int i = 0; i < random; i++) {
			SubRock* pSubRock;
			pSubRock = new SubRock;
			Vector2D currentLocation = pos + Vector2D(rand()% 200 - 100, rand() % 200 - 100);
			float currentAngle = angle + rand() % 6 - 1;
			pSubRock->Initialise(currentLocation, currentAngle, om);
			if (om) {
				om->AddObject(pSubRock);
			}
		}
	}

	if (typeid(object) == typeid(Rock)) {
		float random = (rand() % 5 - 1);
		Velocity.setBearing(random, 70.0f);
	}

	if (typeid(object) == typeid(Bullet)) {
		active = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(pos);
		if (om) {
			om->AddObject(pExplosion);
		}
	}
}