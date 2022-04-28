#include "Reward.h"

Reward::Reward() {
	active = true;
}

void Reward::dropReward(Vector2D pos) {

}

void Reward::ProcessCollision(GameObject& object) {
	if (typeid(object) == typeid(PlayerCharacter)) {
		active = false;
	}
}

void Reward::Initialise(Vector2D location, float angle) {
	GameObject::loadImage(L"crate1.bmp");
	pos = location;
	this->angle = angle;
}

IShape2D& Reward::GetShape() {
	m_collisionShape.PlaceAt(pos, 32);
	return m_collisionShape;
}