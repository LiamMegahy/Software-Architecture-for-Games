#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "myinputs.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Reward.h"

class LevelManager;

class PlayerCharacter : public GameObject {
private:
	Vector2D velocity;
	Vector2D friction;
	int weaponSelected;
	const int rotation = 4;
	int lives;
	const float frameTime = 0.016f;
	float shotDelay = 2.0f;
	float bombCooldown = 4.0f;
	float timer;
	int playerHealth;
	int magazine;
	float gunTimer;
	float newWeaponTimer;
	float hitDelay;
	int score;
	bool newWeaponUnlocked;
	Vector2D gravity;
	PictureIndex model;
	SoundIndex shootSound;
	ObjectManager* om;
	LevelManager* lm;
	Vector2D m_velocity;
	Circle2D m_collisionShape;
	Vector2D start = { 50, 100 };
	Vector2D fullHealth = { 150, 100 };
	float scale = (playerHealth / 10);
public:
	bool setToDead;
	int getAmmoCount();
	int getLives();
	void reloading();
	void setActiveToFalse();
	PlayerCharacter();
	void initialise(Vector2D location, ObjectManager* pOM, LevelManager* lm);
	void update();
	int getHealth();
	int getScore();
	IShape2D& GetShape();
	void ProcessCollision(GameObject& object) override;
	void move();
	void setPlayerHealth(int damage);
	Vector2D getPlayerLocation();
};