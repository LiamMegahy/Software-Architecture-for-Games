#include "EnemyBullet.h"
#include "PlayerCharacter.h"

EnemyBullet::EnemyBullet() {
	active = true;
	timer = deleationDelay;
}

void EnemyBullet::Initialise(Vector2D location, float angle) {
	GameObject::loadImage(L"bullet.bmp");
	GameObject::loadSound(L"shoot.wav");
	Velocity.setBearing(angle, 1000.0f);
	pos = location;
	this->angle = angle;
}

void EnemyBullet::update() {
	pos = pos + Velocity * 0.01;
	timer = timer - frameTime;
	if (timer < 0.0f) {
		active = false;
	}
}

IShape2D& EnemyBullet::GetShape() {
	m_collisionShape.PlaceAt(pos, 12);
	return m_collisionShape;
}

void EnemyBullet::ProcessCollision(GameObject& object) {
	if (typeid(object) == typeid(PlayerCharacter)) {
		active = false;
	}
}