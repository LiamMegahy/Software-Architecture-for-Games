#include "ObjectManager.h"
#include <string>
#include <list>

ObjectManager::ObjectManager() {

}

void ObjectManager::RenderAll() {
	for (GameObject* pNext : GameObjectList) {
		if (pNext != nullptr) {
			pNext->render();
			MyDrawEngine::GetInstance()->WriteInt(50, 50, GameObjectList.size(), MyDrawEngine::GREEN);
			MyDrawEngine::GetInstance()->WriteInt(300, 50, Enemies.size(), MyDrawEngine::GREEN);
		}
		else {
			ErrorLogger::Writeln(L"Null pointer in Object Manager - RenderAll function");
		}
	}
}

void ObjectManager::UpdateAll(float frametime) {
	for (GameObject* pNext : GameObjectList) {
		if (pNext != nullptr) {
			pNext->update();
		}
		else {
			ErrorLogger::Writeln(L"Null pointer in Object Manager - UpdateAll function");
		}
	}
}

void ObjectManager::AddObject(GameObject* pNewObject) {
	if (pNewObject != nullptr) {
		GameObjectList.push_back(pNewObject);
	}
	else {
		ErrorLogger::Writeln(L"Null pointer in Object Manager - AddObject function");
	}
}

void ObjectManager::checkEnemyCount() {
	int remainingEnemies = Enemies.size();
	LevelManager* pLevelManager;
	pLevelManager = new LevelManager;
	if (remainingEnemies <= 0) {
		pLevelManager->loadNewEnemies();
	}
}

void ObjectManager::addEnemy(GameObject* pNewObject) {
	if (pNewObject != nullptr) {
		Enemies.push_back(pNewObject);
	}
	else {
		ErrorLogger::Writeln(L"Null pointer in Object Manager - AddObject function");
	}
}

void ObjectManager::deleteThis() {
	for (GameObject* pNext : GameObjectList) {
		delete pNext;
		pNext = nullptr;
	}
	for (GameObject* pNext : Enemies) {
		delete pNext;
		pNext = nullptr;
	}
	GameObjectList.clear();
}

void ObjectManager::deleteInactive() {
	for (GameObject*& pNext : GameObjectList) {
		if (pNext->active == false) {
			delete pNext;
			pNext = nullptr;
		}
	}
	for (GameObject*& pNext : Enemies) {
		if (pNext->active == false) {
			delete pNext;
			pNext = nullptr;
		}
	}
	GameObjectList.remove(nullptr);
	Enemies.remove(nullptr);
}

void ObjectManager::CheckAllCollisions() {
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;
	for (it1 = GameObjectList.begin(); it1 != GameObjectList.end(); it1++) {
		for (it2 = std::next(it1); it2 != GameObjectList.end(); it2++) {
			if ((*it1) && (*it2) &&
				(*it1)->isActive() && (*it2)->isActive() &&
				(*it1)->GetShape().Intersects((*it2)->GetShape()))
			{
				(*it1)->ProcessCollision(**it2);
				(*it2)->ProcessCollision(**it1);
			}
		}
	}
}

void ObjectManager::runAllFunctions() {
	UpdateAll(frameTime);
	RenderAll();
	deleteInactive();
	CheckAllCollisions();
	checkEnemyCount();
}