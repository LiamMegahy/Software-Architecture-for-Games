#include <iostream>
#include "PlayerCharacter.h"
#include "mydrawengine.h"
#include "Explosion.h"
#include "Rock.h"
#include "LevelManager.h"
#include "EnemyBullet.h"
#include <chrono>
#include <thread>
#include <string>
#include <ddraw.h>

PlayerCharacter::PlayerCharacter() {
	active = true;
	setToDead = true;
	magazine = 6;
	newWeaponTimer = 10;
	score = 0;
	timer = 4;
	lives = 3;
	weaponType = 0;
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
}

int PlayerCharacter::getAmmoCount() {
	return magazine;
}

int PlayerCharacter::getScore() {
	return score;
}

Vector2D PlayerCharacter::getPlayerLocation() {
	return pos;
}

int PlayerCharacter::getHealth() {
	return playerHealth;
}

void PlayerCharacter::setActiveToFalse() {
	active = false;
}

int PlayerCharacter::getLives() {
	return lives;
}

void PlayerCharacter::setPlayerHealth(int damage) {
	playerHealth = playerHealth - damage;
}

void PlayerCharacter::reloading(int guntype) {
	gunTimer = 4;
	GameObject::loadSound(L"servoloop.wav");
	if (guntype == 0) {
		magazine = 6;
	}
	else if (guntype == 1) {
		magazine = 12;
	}
	else if (guntype == 2) {
		magazine = 18;
	}
	else {
		magazine = 8;
	}
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
	if (pInputs->KeyPressed(DIK_1)) {
		if (score >= 60) {
			weaponType = 1;
			score = score - 60;
			magazine = 12;
			GameObject::loadSound(L"target1.wav");
		}
	}
	if (pInputs->KeyPressed(DIK_2)) {
		if (score >= 100) {
			weaponType = 2;
			score = score - 100;
			magazine = 16;
			GameObject::loadSound(L"target1.wav");
		}
	}
	if (pInputs->KeyPressed(DIK_3)) {
		if (score >= 150) {
			weaponType = 3;
			score = score - 150;
			magazine = 6;
			GameObject::loadSound(L"target1.wav");
		}
	}
	if (pInputs->KeyPressed(DIK_R)) {
		magazine = 0;
		reloading(weaponType);
	}
	if (pInputs->NewKeyPressed(DIK_F)) {
		if (magazine > 0) {
			if (weaponType == 0) {
				if (gunTimer <= 0) {
					magazine = magazine - 1;
					Bullet* pBullet = new Bullet();
					pBullet->Initialise(pos, angle);
					if (om) {
						om->AddObject(pBullet);
					}
					gunTimer = shotDelay;
				}
			}
			else if (weaponType == 1) {
				if (gunTimer <= 0) {
					magazine = magazine - 1;
					Bullet* pBullet = new Bullet();
					pBullet->Initialise(pos, angle);
					if (om) {
						om->AddObject(pBullet);
					}
					gunTimer = shotDelay;
				}
			}
			else if (weaponType == 2) {
				for (int i = 0; i < 2; i++) {
					magazine = magazine - 1;
					Bullet* pBullet = new Bullet();
					pBullet->Initialise(pos, angle);
					if (om) {
						om->AddObject(pBullet);
					}
				}
				gunTimer = shotDelay;
			}
			else {
				for (int i = 0; i < 6; i++) {
					Bullet* pBullet = new Bullet();
					pBullet->Initialise(pos, angle);
					if (om) {
						om->AddObject(pBullet);
					}
				}
				magazine = magazine - 1;
				gunTimer = shotDelay;
			}
		}	
	}
	gunTimer -= frameTime;
	bombCooldown -= frameTime;
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
	if (typeid(object) == typeid(Rock)) {
		if (hitDelay <= 0) {
			playerHealth = playerHealth - 10;
			float random = (rand() % 5 - 1);
			velocity.setBearing(random, 150.0f);
			if (playerHealth <= 0) {
				lives = lives - 1;
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
				lives = lives - 1;
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
				lives = lives - 1;
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
	if (typeid(object) == typeid(Reward)) {
		score = score + 10;
		GameObject::loadSound(L"target1.wav");
	}
	if (typeid(object) == typeid(Explosion)) {
		if (hitDelay <= 1) {
			playerHealth = playerHealth - 30;
			hitDelay = shotDelay;
			float random = (rand() % 5 - 1);
			velocity.setBearing(random, 700.0f);
			if (playerHealth <= 0) {
				lives = lives - 1;
				active = false;
				Explosion* pExplosion = new Explosion();
				pExplosion->Initialise(pos);
				if (om) {
					om->AddObject(pExplosion);
					lm->playerDead();
				}
			}
		}
	}
}