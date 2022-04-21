#pragma once
#include "Rock.h"

class ObjectManager;
class PlayerCharacter;

class LevelManager {
public:
	LevelManager();
	void loadNewEnemies();
	void displayGameOverState();
	void displayGameWonState();
	void update(float frameTime);
	void incrementEnemies();
	void render();
	void resetLevel();
	void removeEnemies();
	void setPlayer(PlayerCharacter* pc);
	void playerDead();
	int setColour();
	Vector2D getPlayerPosition();
	void initailise(ObjectManager* om);
	PlayerCharacter* pc;
	ObjectManager* om;
	int colour;
private:
	int levelsCompleted;
	int defaultEnemiesAmount;
	int Enemies;
};

