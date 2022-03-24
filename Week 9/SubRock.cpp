#include "SubRock.h"

SubRock::SubRock(ObjectManager& TheObjectManager) : om(TheObjectManager) {
	active = true;
	loadImage(L"rock2.bmp");
}

void SubRock::Initialise(Vector2D location, float angle) {
	GameObject::loadImage(L"rock2.bmp");
	Velocity.setBearing(angle, 100.0f);
	pos = location;
	this->angle = angle;
	om.AddObject(this);
}

void SubRock::ProcessCollision(GameObject* object, Vector2D location, float angle) {
	active = false;
	Explosion* pExplosion = new Explosion(om);
	pExplosion->Initialise(location);
}

IShape2D& SubRock::GetShape() {
	m_collisionShape.PlaceAt(pos, 32);
	return m_collisionShape;
}