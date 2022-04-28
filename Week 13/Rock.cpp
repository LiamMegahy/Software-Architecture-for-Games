#include "Rock.h"
#include "EnemyBullet.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include <iostream>

Rock::Rock() {
	active = true;
}

void Rock::update() {
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
		Reward* pReward;
		pReward = new Reward;
		pReward->Initialise(pos, 1);
		om->AddObject(pReward);
		for (int i = 0; i < 1; i++) {
			om->addNewEnemy();
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

	if (typeid(object) == typeid(Explosion)) {
		active = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(pos);
		if (om) {
			om->AddObject(pExplosion);
		}
	}
}