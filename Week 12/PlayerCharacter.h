#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "myinputs.h"
#include "GameObject.h"
#include "Bullet.h"

class LevelManager;

class PlayerCharacter : public GameObject {
private:
	Vector2D velocity;
	Vector2D friction;
	const int rotation = 4;
	const float frameTime = 0.016f;
	const float shotDelay = 0.5f;
	int playerHealth;
	float timer;
	float hitDelay;
	Vector2D gravity;
	PictureIndex model;
	SoundIndex shootSound;
	ObjectManager* om;
	LevelManager* lm;
	Vector2D m_velocity;
	Circle2D m_collisionShape;
public:
	PlayerCharacter();
	void initialise(Vector2D location, ObjectManager* pOM, LevelManager* lm);
	void update();
	void showHealth();
	IShape2D& GetShape();
	void ProcessCollision(GameObject& object) override;
	void move();
	void setPlayerHealth(int damage);
	Vector2D getPlayerLocation();
};