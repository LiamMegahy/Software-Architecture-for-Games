#include "SubRock.h"
#include "Bullet.h"
#include "Reward.h"
#include "LevelManager.h"
#include "ObjectManager.h"

SubRock::SubRock(){
	active = false;
}

void SubRock::update() {
	Velocity = (lm->getPlayerPosition() - pos).unitVector() * 200;
	pos = pos + Velocity * 0.016;
	angle = (lm->getPlayerPosition() - pos).angle();
}

void SubRock::Initialise(Vector2D location, float angle, ObjectManager* Pom, LevelManager* plm) {
	active = true;
	GameObject::loadImage(L"rock2.bmp");
	Velocity.setBearing(angle, 100.0f);
	pos = location;
	this->angle = angle;
	this->scale = 0.5;
	om = Pom;
	lm = plm;
}

void SubRock::ProcessCollision(GameObject& object) {
	if (typeid(object) == typeid(Bullet)) {
		active = false;
		lm->removeEnemies();
		Reward* pReward;
		pReward = new Reward;
		pReward->Initialise(pos, 1);
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(pos);
		if (om) {
			om->AddObject(pExplosion);
		}
	}

	if (typeid(object) == typeid(SubRock)) {
		float random = (rand() % 10 - 5);
		Velocity.setBearing(random, 150.0f);
	}

	if (typeid(object) == typeid(Rock)) {
		float random = (rand() % 10 - 5);
		Velocity.setBearing(random, 200.0f);
	}
}

IShape2D& SubRock::GetShape() {
	m_collisionShape.PlaceAt(pos, 16);
	return m_collisionShape;
}