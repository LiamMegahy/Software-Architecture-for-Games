#include "Explosion.h"
#include <iostream>
#include "ObjectManager.h"
#include "PlayerCharacter.h"

Explosion::Explosion() {
	active = false;
}

void Explosion::Initialise(Vector2D location) {
	pos = location;
	active = true;
	currentImage = 0.0f;

	modelArray[0] = loadImage(L"explosion1.bmp");
	modelArray[1] = loadImage(L"explosion2.bmp");
	modelArray[2] = loadImage(L"explosion3.bmp");
	modelArray[3] = loadImage(L"explosion4.bmp");
	modelArray[4] = loadImage(L"explosion5.bmp");
	modelArray[5] = loadImage(L"explosion6.bmp");
	modelArray[6] = loadImage(L"explosion7.bmp");
	modelArray[7] = loadImage(L"explosion8.bmp");
	explosionSounds();
}

void Explosion::Render() {
	int random = (rand() % 4 - 1);
	for (int i = (int)currentImage; i < 8; i++) {
		if (active) {
			MyDrawEngine::GetInstance()->DrawAt(pos, modelArray[i], 1, random);
		}
	}
}

void Explosion::update() {
	currentImage = currentImage + 0.1f;
	Render();
	if (currentImage >= 8) {
		deactiveExplosion();
	}
}

void Explosion::explosionSounds() {
	int random = (rand() % 4 - 1);
	if (random == 1) {
		GameObject::loadSound(L"explosion.wav");
	}
	else if (random == 2) {
		GameObject::loadSound(L"explosion1.wav");
	}
	else {
		GameObject::loadSound(L"explosion2.wav");
	}
}

void Explosion::deactiveExplosion() {
	this->active = false;
}

IShape2D& Explosion::GetShape()
{
	m_collisionShape.PlaceAt(pos, 32);
	return m_collisionShape;
}

void Explosion::ProcessCollision(GameObject& object){
	
}
