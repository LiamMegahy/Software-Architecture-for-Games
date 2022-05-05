#include "MeleeZombie.h"
#include "Reward.h"
#include "LevelManager.h"
#include "ObjectManager.h"
#include "SubRock.h"

MeleeZombie::MeleeZombie() {
	active = false;
}

void MeleeZombie::update() {
	Velocity = (lm->getPlayerPosition() - pos).unitVector() * 200;
	pos = pos + Velocity * 0.016;
	angle = (lm->getPlayerPosition() - pos).angle();
}

void MeleeZombie::Initialise(Vector2D location, float angle, ObjectManager* Pom, LevelManager* plm) {
	active = true;
	GameObject::loadImage(L"zombie.png");
	Velocity.setBearing(angle, 100.0f);
	pos = location;
	this->angle = angle;
	this->scale = 0.5;
	om = Pom;
	lm = plm;
}

void MeleeZombie::ProcessCollision(GameObject& object) {
	if (typeid(object) == typeid(Bullet)) {
		active = false;
		lm->removeEnemies();
		Reward* pReward;
		pReward = new Reward;
		if (om) {
			pReward->Initialise(pos, 1);
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

IShape2D& MeleeZombie::GetShape() {
	m_collisionShape.PlaceAt(pos, 32);
	return m_collisionShape;
}