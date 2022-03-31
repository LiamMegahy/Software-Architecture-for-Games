#pragma once
#include "GameObject.h"
#include <list>
#include <string>
//#include "PlayerCharacter.h"
//#include "Rock.h"
//#include "LevelManager.h"

class ObjectManager {
public:
	ObjectManager();
	void UpdateAll(float frametime);
	void RenderAll();
	void AddObject(GameObject* pNewObject);
	void addEnemy(GameObject* pNewObject);
	void deleteThis();
	void deleteInactive();
	void CheckAllCollisions();
	void checkEnemyCount();
	void runAllFunctions();
	std::list<GameObject*> Enemies;
private:
	std::list<GameObject*> GameObjectList;
	const float frameTime = 0.016f;
};

