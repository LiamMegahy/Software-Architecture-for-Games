#pragma once
#include "ObjectManager.h"


class LevelManager : public ObjectManager {
public:
	LevelManager();
	void loadNewEnemies();
	void displayGameOverState();
	void displayGameWonState();
private:
	int levelsCompleted;
	int defaultEnemiesAmount;
};

