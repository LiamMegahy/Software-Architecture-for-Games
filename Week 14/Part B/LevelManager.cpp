#include "LevelManager.h"
#include "ObjectManager.h"
#include "PlayerCharacter.h"
#include "explodingRock.h"
#include "gamecode.h"

LevelManager::LevelManager() {
	defaultEnemiesAmount = 10;
	levelsCompleted = 1;
	pc = nullptr;
	lives = 1;
	levelDelayTimer = 5.0f;
}

void LevelManager::update(float frameTime) {
	om->runAllFunctions();
	if (Enemies <= 0) {
		levelDelayTimer = levelDelayTimer - frameTime;
		if (levelDelayTimer > 0) {
			auto displayLevelComplete = L"---LEVEL COMPLETE!---";
			MyDrawEngine::GetInstance()->WriteText(800, 500, displayLevelComplete, MyDrawEngine::GREEN);
		}
		if (levelDelayTimer < 0) {
			newLevelEnviroment(levelsCompleted);
		}
	}
	if (pc == nullptr) {
		deathTimer = deathTimer - frameTime;
		if (levelDelayTimer > 0 && lives > 0) {
			auto displayYouHaveDied = L"---YOU HAVE DIED!---";
			MyDrawEngine::GetInstance()->WriteText(800, 500, displayYouHaveDied, MyDrawEngine::GREEN);
		}
		if (deathTimer <= 0) {
			lives = lives - 1;
			if (lives == 0) {
				deathTimer = deathTimer - frameTime;
				if (deathTimer > 0) {
					auto displayGameOver = L"---GAME OVER!---";
					MyDrawEngine::GetInstance()->WriteText(800, 500, displayGameOver, MyDrawEngine::GREEN);
				}
				else {
					Game::instance.endTheGame();
				}
			}
			else {
			resetLevel();
			newLevelEnviroment(levelsCompleted-1);
			loadPlayerCharacter();
			}
		}
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
	if (currentLevel == 4) {
		resetLevel();
		Game::instance.endTheGame();
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
	for (int i = 0; i < ((defaultEnemiesAmount / 4) * level); i++) {
		Rock* pRock;
		pRock = new Rock;
		pRock->Initialise(Vector2D(rand() % 2000 - 1000, rand() % 2000 - 1000), rand() % 628 / 100.0, om, this);
		om->AddObject(pRock);
		incrementEnemies();
	}
	for (int i = 0; i < ((defaultEnemiesAmount / 2) * level); i++) {
		MeleeRock* pMeleeRock;
		pMeleeRock = new MeleeRock;
		pMeleeRock->Initialise(Vector2D(rand() % 2000 - 1000, rand() % 2000 - 1000), rand() % 628 / 100.0, om, this);
		om->AddObject(pMeleeRock);
		incrementEnemies();
	}

	if (level > 1) {
		for (int i = 0; i < ((defaultEnemiesAmount / 6) * level); i++) {
			explodingRock* pExplodingRock;
			pExplodingRock = new explodingRock;
			pExplodingRock->Initialise(Vector2D(rand() % 2000 - 1000, rand() % 2000 - 1000), rand() % 628 / 100.0, om, this);
			om->AddObject(pExplodingRock);
			incrementEnemies();
		}
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
	deathTimer = 5.0f;
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
	auto shopText = L"SHOP : ";
	auto repeaterText = L"1 : Repeater - 60 points";
	auto dualRevolversText = L"2 : Dual Pistols - 100 points";
	auto shotgunText = L"3 : Shotgun - 150 points";
	auto medkitText = L"4 : Medkit - 40 points";
	auto superstimText = L"5 : SuperStim - 150 points";
	if (pc) {
		MyDrawEngine::GetInstance()->WriteInt(150, 50, pc->getAmmoCount(), MyDrawEngine::GREEN);
		MyDrawEngine::GetInstance()->WriteText(50, 50, ammoText, MyDrawEngine::GREEN);
		MyDrawEngine::GetInstance()->WriteInt(300, 50, pc->getScore(), MyDrawEngine::GREEN);
		MyDrawEngine::GetInstance()->WriteText(200, 50, scoreText, MyDrawEngine::GREEN);
		MyDrawEngine::GetInstance()->WriteInt(500, 50, pc->getHealth(), MyDrawEngine::GREEN);
		MyDrawEngine::GetInstance()->WriteText(400, 50, healthText, MyDrawEngine::GREEN);
	}
	MyDrawEngine::GetInstance()->WriteInt(700, 50, lives, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteText(600, 50, remainingLivesText, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteText(50, 300, shopText, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteText(50, 400, repeaterText, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteText(50, 500, dualRevolversText, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteText(50, 600, shotgunText, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteText(50, 700, medkitText, MyDrawEngine::GREEN);
	MyDrawEngine::GetInstance()->WriteText(50, 800, superstimText, MyDrawEngine::GREEN);
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