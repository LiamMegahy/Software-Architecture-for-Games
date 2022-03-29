#include <iostream>
#include "Spaceship.h"
#include "mydrawengine.h"
#include "Explosion.h"
#include "Rock.h"
#include <chrono>
#include <thread>

Spaceship::Spaceship() {
	active = true;
}

void Spaceship::initialise(Vector2D location, ObjectManager* pOM ) {
	loadImage(L"ship.bmp");
	pos = location;
	om = pOM;
	velocity = { 0.0f, 0.0f };
	gravity = { 0.0f, -10.0f };
	active = true;
	angle = 1;
}

void Spaceship::update() {
	move();
	GetShape();
}

void Spaceship::move() {
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	Vector2D acceleration(0, 0);
	if (pInputs->KeyPressed(DIK_W)) {
		acceleration.setBearing(angle, 500.0f);
	}
	if (pInputs->KeyPressed(DIK_S)) {
		acceleration.setBearing(angle, -50.0f);
	}
	if (pInputs->KeyPressed(DIK_A)) {
		angle = angle - rotation * frameTime;
	}
	if (pInputs->KeyPressed(DIK_D)) {
		angle = angle + rotation * frameTime;
	}
	if (pInputs->NewKeyPressed(DIK_F)) {
		if (timer <= 0) {
			Bullet* pBullet = new Bullet();
			pBullet->Initialise(pos, angle);
			if (om) {
				om->AddObject(pBullet);
			}
			timer = shotDelay;
		}
	}
	if (pInputs->NewKeyPressed(DIK_SPACE)) {
		if (timer <= 0) {
			for (int i = 0; i < 6; i++) {
				Bullet* pBullet = new Bullet();
				pBullet->Initialise(pos, angle);
				if (om) {
					om->AddObject(pBullet);
				}
				angle = angle + 0.1;
				timer = 6;
			}
		}	
	}

	timer -= frameTime;

	acceleration += gravity;
	velocity = velocity + acceleration * frameTime;
	friction = -0.5 * velocity;
	velocity = velocity + friction * frameTime;
	pos = pos + velocity * frameTime;
}
IShape2D& Spaceship::GetShape() {
	m_collisionShape.PlaceAt(pos, 32);
	return m_collisionShape;
}

void Spaceship::ProcessCollision(GameObject& object) {
	if (typeid(object) == typeid(Rock)){
		active = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(pos);
		if (om) {
			om->AddObject(pExplosion);
		}
	}
	if (typeid(object) == typeid(SubRock)) {
		active = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(pos);
		if (om) {
			om->AddObject(pExplosion);
		}
	}
}