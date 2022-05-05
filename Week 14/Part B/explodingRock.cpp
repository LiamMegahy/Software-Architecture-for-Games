#include "explodingRock.h"
#include "EnemyBullet.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include <iostream>

explodingRock::explodingRock() {
	active = true;
}

void explodingRock::update() {
	Velocity = (lm->getPlayerPosition() - pos).unitVector() * 200;
	pos = pos + Velocity * 0.016;
	angle = (lm->getPlayerPosition() - pos).angle();
}

void explodingRock::Initialise(Vector2D location, float angle, ObjectManager* Pom, LevelManager* plm) {
	int random = (rand() % 6 - 1);
	GameObject::loadImage(L"rock1.bmp");
	Velocity.setBearing(angle, 50.0f);
	pos = location;
	this->angle = angle;
	om = Pom;
	lm = plm;
}

IShape2D& explodingRock::GetShape() {
	m_collisionShape.PlaceAt(pos, 64);
	return m_collisionShape;
}

void explodingRock::ProcessCollision(GameObject& object) {
	if (typeid(object) == typeid(Bullet)) {
		active = false;
		lm->removeEnemies();
		for (int i = 0; i < 3; i++){
			Reward* pReward;
			pReward = new Reward;
			pReward->Initialise(pos, 1);
			om->AddObject(pReward);
		}
	}

	if (typeid(object) == typeid(Rock)) {
		float random = (rand() % 5 - 1);
		Velocity.setBearing(random, 250.0f);
	}

	if (typeid(object) == typeid(SubRock)) {
		float random = (rand() % 5 - 1);
		Velocity.setBearing(random, 250.0f);
	}

	if (typeid(object) == typeid(MeleeRock)) {
		float random = (rand() % 5 - 1);
		Velocity.setBearing(random, 250.0f);
	}

	if (typeid(object) == typeid(PlayerCharacter)) {
		active = false;
		lm->removeEnemies();
		for (int i = 0; i < 4; i++) {
			om->addNewEnemy();
			SubRock* pSubRock;
			pSubRock = new SubRock;
			Vector2D currentLocation = pos + Vector2D(rand() % 200 - 100, rand() % 200 - 100);
			float currentAngle = angle + rand() % 6 - 1;
			pSubRock->Initialise(currentLocation, currentAngle, om, lm);
			if (om) {
				om->AddObject(pSubRock);
			}
			if (lm) {
				lm->incrementEnemies();
			}
		}
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(pos + Vector2D(rand() % 200 - 100, rand() % 200 - 100));
		if (om) {
			om->AddObject(pExplosion);
		}
	}
}