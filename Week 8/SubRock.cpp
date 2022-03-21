#include "SubRock.h"

SubRock::SubRock() {
	active = true;
	loadImage(L"rock2.bmp");
}

void SubRock::Initialise(Vector2D location, float angle) {
	GameObject::loadImage(L"rock2.bmp");
	Velocity.setBearing(angle, 100.0f);
	pos = location;
	this->angle = angle;
}

void SubRock::splitOff(Vector2D location, float angle) {
	int numberOfRocks = (rand() % 6 - 1);
	for (int i = 0; i < numberOfRocks; i++) {
		SubRock* pSubRock;
		pSubRock = new SubRock();
		pSubRock->Initialise(location, rand() % 628 / 100.0);
		ObjectManager::AddObject(pSubRock);
	}
}

void SubRock::ProcessCollision(GameObject* object) {
	active = false;
}