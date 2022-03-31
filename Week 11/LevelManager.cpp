#include "LevelManager.h"
//#include "Rock.h"

LevelManager::LevelManager() {
	defaultEnemiesAmount = 10;
	levelsCompleted = 1;
}

void LevelManager::loadNewEnemies() {
	int remainingEnemies = Enemies.size();
	if (remainingEnemies = 0) {
		levelsCompleted = levelsCompleted + 1;
		defaultEnemiesAmount = defaultEnemiesAmount * levelsCompleted;

		for (int i = 0; i < defaultEnemiesAmount; i++) {
			Rock* pRock;
			pRock = new Rock;
			pRock->Initialise(Vector2D(rand() % 2000 - 1000, rand() % 2000 - 1000), rand() % 628 / 100.0);
			AddObject(pRock);
			addEnemy(pRock);
		}
	}
}

void LevelManager::displayGameOverState() {
	//MyDrawEngine::GetInstance()->WriteText(50, 50, "Sample game over text", 1);
}

void LevelManager::displayGameWonState() {
	//MyDrawEngine::GetInstance()->WriteText(50, 50, "Sample game won text", 1);
}
