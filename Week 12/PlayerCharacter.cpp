#include <iostream>
#include "PlayerCharacter.h"
#include "mydrawengine.h"
#include "Explosion.h"
#include "LevelManager.h"
#include "Rock.h"
#include <chrono>
#include <thread>
#include "EnemyBullet.h"

PlayerCharacter::PlayerCharacter() {
	active = true;
	lm = nullptr;
}

void PlayerCharacter::initialise(Vector2D location, ObjectManager* pOM, LevelManager* lm) {
	loadImage(L"ship.bmp");
	this->lm = lm;
	lm->setPlayer(this);
	playerHealth = 100;
	pos = location;
	om = pOM;
	velocity = { 0.0f, 0.0f };
	gravity = { 0.0f, -10.0f };
	active = true;
	angle = 1;
}

void PlayerCharacter::update() {
	GameObject::offScreen();
	MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(pos.XValue, pos.YValue));
	move();
	GetShape();
	showHealth();
}

void PlayerCharacter::showHealth() {
	MyDrawEngine::GetInstance()->WriteInt(150, 50, playerHealth, MyDrawEngine::GREEN);
}

Vector2D PlayerCharacter::getPlayerLocation() {
	return pos;
}

void PlayerCharacter::setPlayerHealth(int damage) {
	playerHealth = playerHealth - damage;
}

void PlayerCharacter::move() {
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
	hitDelay -= frameTime;

	acceleration += gravity;
	velocity = velocity + acceleration * frameTime;
	friction = -0.5 * velocity;
	velocity = velocity + friction * frameTime;
	pos = pos + velocity * frameTime;
}
IShape2D& PlayerCharacter::GetShape() {
	m_collisionShape.PlaceAt(pos, 32);
	return m_collisionShape;
}

void PlayerCharacter::ProcessCollision(GameObject& object) {
	if (typeid(object) == typeid(Rock)){
		if (hitDelay <= 0) {
			playerHealth = playerHealth - 10;
			float random = (rand() % 5 - 1);
			velocity.setBearing(random, 150.0f);
			if (playerHealth <= 0) {
				active = false;
				Explosion* pExplosion = new Explosion();
				pExplosion->Initialise(pos);
				if (om) {
					om->AddObject(pExplosion);
					lm->playerDead();
				}
			}
		}
		hitDelay = shotDelay;
	}
	if (typeid(object) == typeid(SubRock)) {
		if (hitDelay <= 0) {
			playerHealth = playerHealth - 5;
			float random = (rand() % 5 - 1);
			velocity.setBearing(random, 150.0f);
			if (playerHealth <= 0) {
				active = false;
				Explosion* pExplosion = new Explosion();
				pExplosion->Initialise(pos);
				if (om) {
					om->AddObject(pExplosion);
					lm->playerDead();
				}
			}
		}
		hitDelay = shotDelay;
	}
	if (typeid(object) == typeid(EnemyBullet)) {
		if (hitDelay <= 0) {
			playerHealth = playerHealth - 20;
			if (playerHealth <= 0) {
				active = false;
				Explosion* pExplosion = new Explosion();
				pExplosion->Initialise(pos);
				if (om) {
					om->AddObject(pExplosion);
					lm->playerDead();
				}
			}
		}
		hitDelay = shotDelay;
	}
}