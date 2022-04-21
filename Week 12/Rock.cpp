#include "Rock.h"
#include <iostream>
#include "LevelManager.h"
#include "ObjectManager.h"
#include "EnemyBullet.h"

Rock::Rock() {
	active = true;
}

void Rock::update() {
	//GameObject::offScreen();
	Velocity = (lm->getPlayerPosition() - pos).unitVector() * 200;
	pos = pos + Velocity * 0.016;
	angle = (lm->getPlayerPosition() - pos).angle();
	fireGun();
}

void Rock::Initialise(Vector2D location, float angle, ObjectManager* Pom, LevelManager* plm) {
	int random = (rand() % 6 - 1);
	GameObject::loadImage(L"rock1.bmp");
	Velocity.setBearing(angle, 50.0f);
	pos = location;
	this->angle = angle;
	om = Pom;
	lm = plm;
}

IShape2D& Rock::GetShape() {
	m_collisionShape.PlaceAt(pos, 32);
	return m_collisionShape;
}

void Rock::fireGun() {
	if (timer <= 0) {
		EnemyBullet* pEnemyBullet = new EnemyBullet();
		pEnemyBullet->Initialise(pos, angle);
		if (om) {
			om->AddObject(pEnemyBullet);
		}
		timer = shotDelay;
	}
	timer -= frameTime;
}

void Rock::ProcessCollision(GameObject& object) {
	if (typeid(object) == typeid(Bullet)) {
		active = false;
		lm->removeEnemies();
		int random = (rand() % 6 - 3);
		for (int i = 0; i < random; i++) {
			SubRock* pSubRock;
			pSubRock = new SubRock;
			Vector2D currentLocation = pos + Vector2D(rand()% 200 - 100, rand() % 200 - 100);
			float currentAngle = angle + rand() % 6 - 1;
			pSubRock->Initialise(currentLocation, currentAngle, om, lm);
			if (om) {
				om->AddObject(pSubRock);
				lm->incrementEnemies();
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