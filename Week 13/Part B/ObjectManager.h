#pragma once
#include "GameObject.h"
#include <list>
#include <string>

class ObjectManager {
public:
	ObjectManager();
	void UpdateAll(float frametime);
	void RenderAll();
	void AddObject(GameObject* pNewObject);
	void deleteThis();
	void deleteInactive();
	void CheckAllCollisions();
	void runAllFunctions();
	void addNewEnemy();
	void removeDeadEnemy();
	int returnEnemySize();
	std::list<GameObject*> GameObjectList;
	int remainingEnemies;
private:
	const float frameTime = 0.016f;
};

