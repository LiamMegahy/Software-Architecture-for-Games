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
	magazine = 10;
	playerTimer = 90;
	newWeaponTimer = 10;
	score = 0;
	timer = 4;
	weaponSelected = 1;
	newWeaponUnlocked = false;
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
	displayAmmoCount();
	reloading();
	timeLimit();
	displayScore();
}

void PlayerCharacter::displayAmmoCount() {
	MyDrawEngine::GetInstance()->WriteInt(900, 50, magazine, MyDrawEngine::GREEN);
}

Vector2D PlayerCharacter::getPlayerLocation() {
	return pos;
}

void PlayerCharacter::displayScore() {
	MyDrawEngine::GetInstance()->WriteInt(1400, 50, score, MyDrawEngine::GREEN);
}

void PlayerCharacter::showHealth() {
	MyDrawEngine::GetInstance()->WriteInt(150, 50, playerHealth, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->DrawLine(start, (fullHealth * scale), 3);
}

void PlayerCharacter::timeLimit() {
	playerTimer -= frameTime;
	MyDrawEngine::GetInstance()->WriteInt(600, 50, playerTimer, MyDrawEngine::GREEN);
	if (playerTimer <= 0) {
		playerHealth = 0;
		active = false;
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(pos);
		if (om) {
			om->AddObject(pExplosion);
		}
	}
}

void PlayerCharacter::setPlayerHealth(int damage) {
	playerHealth = playerHealth - damage;
}

void PlayerCharacter::reloading() {
	if (magazine <= 0) {
		gunTimer = 4;
		GameObject::loadSound(L"servoloop.wav");
		magazine = 10;
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
		weaponSelected = 1;
	}
	if (pInputs->KeyPressed(DIK_2)) {
		weaponSelected = 2;
	}
	if (pInputs->KeyPressed(DIK_R)) {
		magazine = 0;
		reloading();
	}
	if (pInputs->NewKeyPressed(DIK_F)) {
		if (magazine > 0) {
			if (gunTimer <= 0) {
				magazine = magazine - 1;
				if (newWeaponUnlocked == true) {
					Bullet* pBullet = new Bullet();
					pBullet->Initialise(pos, angle);
					if (om) {
						om->AddObject(pBullet);
					}
				}
				Bullet* pBullet = new Bullet();
				pBullet->Initialise(pos, angle);
				if (om) {
					om->AddObject(pBullet);
				}
				gunTimer = shotDelay;
			}
		}
	}
	if (pInputs->NewKeyPressed(DIK_SPACE)) {
		if (magazine > 0) {
			if (gunTimer <= 0) {
				magazine = magazine - 6;
				for (int i = 0; i < 6; i++) {
					Bullet* pBullet = new Bullet();
					pBullet->Initialise(pos, angle);
					if (om) {
						om->AddObject(pBullet);
					}
					angle = angle + 0.1;
					gunTimer = 6;
				}
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
	if (typeid(object) == typeid(Reward)) {
		score = score + 10;
		GameObject::loadSound(L"target1.wav");

		if (score == 40) {
			shotDelay = shotDelay - 0.3;
		}
		if (score == 80) {
			shotDelay = shotDelay - 0.5;
		}
		if (score == 100) {
			shotDelay = shotDelay - 0.7;
			newWeaponUnlocked = true;
		}
	}
	if (typeid(object) == typeid(Explosion)) {
		if (hitDelay <= 0) {
			playerHealth = playerHealth - 30;
			hitDelay = shotDelay;
			float random = (rand() % 5 - 1);
			velocity.setBearing(random, 700.0f);
		}
	}
}