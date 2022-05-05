#pragma once
#include "Rock.h"
#include "MeleeRock.h"

class ObjectManager;
class PlayerCharacter;

class LevelManager {
public:
	LevelManager();
	void loadNewEnemies(int level);
	void update(float frameTime);
	void incrementEnemies();
	void render();
	void resetLevel();
	void removeEnemies();
	void setPlayer(PlayerCharacter* pc);
	void playerDead();
	void newLevelEnviroment(int currentLevel);
	void loadPlayerCharacter();
	void timeLimit();
	Vector2D getPlayerPosition();
	void initailise(ObjectManager* om);
	PlayerCharacter* pc;
	ObjectManager* om;
	int colour;
private:
	int lives;
	float deathTimer;
	float levelDelayTimer;
	int levelsCompleted;
	int defaultEnemiesAmount;
	int Enemies;
	float playerTimer = 90.0f;
	const float frameTime = 0.016f;
};