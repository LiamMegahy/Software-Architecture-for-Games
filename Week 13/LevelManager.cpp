#include "LevelManager.h"
#include "ObjectManager.h"
#include "PlayerCharacter.h"

LevelManager::LevelManager() {
	defaultEnemiesAmount = 10;
	levelsCompleted = 1;
	pc = nullptr;
}

void LevelManager::update(float frameTime) {
	if (Enemies <= 0) {
		loadNewEnemies();
	}
}

void LevelManager::initailise(ObjectManager* om) {
	this->om = om;
	resetLevel();
}

void LevelManager::loadNewEnemies() {
	levelsCompleted = levelsCompleted + 1;

	for (int i = 0; i < (defaultEnemiesAmount * levelsCompleted); i++) {
		Rock* pRock;
		pRock = new Rock;
		pRock->Initialise(Vector2D(rand() % 2000 - 1000, rand() % 2000 - 1000), rand() % 628 / 100.0, om, this);
		om->AddObject(pRock);
		incrementEnemies();
	}
}

void LevelManager::resetLevel() {
	Enemies = 0;
}

void LevelManager::incrementEnemies() {
	Enemies = Enemies + 1;
}

void LevelManager::removeEnemies() {
	Enemies = Enemies - 1;
}

void LevelManager::setPlayer(PlayerCharacter* pc) {
	this->pc = pc;
}

void LevelManager::playerDead() {
	pc = nullptr;
}

Vector2D LevelManager::getPlayerPosition() {
	if (pc) {
		return pc->getPlayerLocation();
	}
	else {
		return Vector2D(0, 0);
	}
}

void LevelManager::render() {
	MyDrawEngine::GetInstance()->WriteInt(50, 100, Enemies, MyDrawEngine::GREEN);
	//If statement to check and run display states
}

void LevelManager::displayGameOverState() {
	//MyDrawEngine::GetInstance()->WriteText(50, 50, "Sample game over text", 1);
}

void LevelManager::displayGameWonState() {
	//MyDrawEngine::GetInstance()->WriteText(50, 50, "Sample game won text", 1);
}