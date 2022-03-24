#include "SubRock.h"

SubRock::SubRock(){
	active = true;
	loadImage(L"rock2.bmp");
}

void SubRock::Initialise(Vector2D location, float angle) {
	GameObject::loadImage(L"rock2.bmp");
	Velocity.setBearing(angle, 100.0f);
	pos = location;
	this->angle = angle;
}

void SubRock::ProcessCollision(GameObject& object) {
	active = false;
	Explosion* pExplosion = new Explosion();
	pExplosion->Initialise(pos);
	if (om) {
		om->AddObject(pExplosion);
	}
}

IShape2D& SubRock::GetShape() {
	m_collisionShape.PlaceAt(pos, 32);
	return m_collisionShape;
}