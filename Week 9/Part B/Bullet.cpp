#include "Bullet.h"

Bullet::Bullet() {
	active = true;
	timer = deleationDelay;
}

void Bullet::Initialise(Vector2D location, float angle) {
	GameObject::loadImage(L"bullet.bmp");
	GameObject::loadSound(L"shoot.wav");
	Velocity.setBearing(angle, 1000.0f);
	pos = location;
	this->angle = angle;
}

void Bullet::update() {
	pos = pos + Velocity * 0.01; 
	timer = timer - frameTime;
	if (timer < 0.0f) {
		active = false;
	}
}

IShape2D& Bullet::GetShape() {
	m_collisionShape.PlaceAt(pos, 12);
	return m_collisionShape;
}

void Bullet::ProcessCollision(GameObject& object) {
	//active = false;
}