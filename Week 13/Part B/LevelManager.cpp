#include "LevelManager.h"
#include "ObjectManager.h"
#include "PlayerCharacter.h"

LevelManager::LevelManager() {
	defaultEnemiesAmount = 10;
	levelsCompleted = 1;
	pc = nullptr;
}

void LevelManager::update(float frameTime) {
	om->runAllFunctions();
	if (Enemies <= 0) {
		newLevelEnviroment(levelsCompleted);
	}
}

void LevelManager::initailise(ObjectManager* om) {
	this->om = om;
	resetLevel();
}

void LevelManager::newLevelEnviroment(int currentLevel) {
	if (currentLevel == 1) {
		resetLevel();
		loadNewEnemies(1);
		loadPlayerCharacter();
		levelsCompleted = levelsCompleted + 1;
	}
	if (currentLevel == 2) {
		resetLevel();
		loadNewEnemies(2);
		levelsCompleted = levelsCompleted + 1;
	}
	if (currentLevel == 3) {
		resetLevel();
		loadNewEnemies(3);
		levelsCompleted = levelsCompleted + 1;
	}
}

void LevelManager::loadPlayerCharacter() {
	Vector2D location = { 0.0f, 0.0f };
	PlayerCharacter* pPlayerCharacter2;
	pPlayerCharacter2 = new PlayerCharacter;
	pPlayerCharacter2->initialise(location, om, this);
	om->AddObject(pPlayerCharacter2);
}

void LevelManager::loadNewEnemies(int level) {
	for (int i = 0; i < (defaultEnemiesAmount * level); i++) {
		Rock* pRock;
		pRock = new Rock;
		pRock->Initialise(Vector2D(rand() % 2000 - 1000, rand() % 2000 - 1000), rand() % 628 / 100.0, om, this);
		om->AddObject(pRock);
		incrementEnemies();
	}
}

void LevelManager::changeBackgroundColour() {

}

void LevelManager::generateTextPopUpText() {

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
	timeLimit();
	auto ammoText = L"Ammo :";
	auto scoreText = L"Score : ";
	auto healthText = L"Health : ";
	auto remainingLivesText = L"Lives : ";
	MyDrawEngine::GetInstance()->WriteInt(150, 50, pc->getAmmoCount(), MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteText(50, 50, ammoText, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteInt(400, 50, pc->getScore(), MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteText(200, 50, scoreText, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteInt(700, 50, pc->getHealth(), MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteText(500, 50, healthText, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteInt(1000, 50, pc->getLives(), MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteText(900, 50, remainingLivesText, MyDrawEngine::GREEN);
}

void LevelManager::timeLimit() {
	playerTimer -= frameTime;
	auto timerText = L"Time Remaining : ";
	MyDrawEngine::GetInstance()->WriteText(1150, 50, timerText, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteInt(1400, 50, playerTimer, MyDrawEngine::GREEN);
	if (playerTimer <= 0) {
		pc->setActiveToFalse();
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(pc->getPlayerLocation());
		if (om) {
			om->AddObject(pExplosion);
		}
	}
}