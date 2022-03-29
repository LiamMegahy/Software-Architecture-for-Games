#include "SubRock.h"
#include "Bullet.h"

SubRock::SubRock(){
	active = false;
}

void SubRock::update() {
	pos = pos + Velocity * 0.016;
}

void SubRock::Initialise(Vector2D location, float angle) {
	active = true;
	GameObject::loadImage(L"rock2.bmp");
	Velocity.setBearing(angle, 100.0f);
	pos = location;
	this->angle = angle;
}

void SubRock::Initialise(Vector2D location, float angle, ObjectManager* Pom) {
	Initialise(location, angle);
	this->scale = 0.5;
	om = Pom;
}

void SubRock::ProcessCollision(GameObject& object) {
	if (typeid(object) == typeid(Bullet)) {
		active = false;
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