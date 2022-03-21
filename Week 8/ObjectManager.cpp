#include "ObjectManager.h"
#include <string>
#include <list>

ObjectManager::ObjectManager() {
	
}

void ObjectManager::RenderAll() {
	for (GameObject* pNext : GameObjectList) {
		if (pNext != nullptr && pNext->active!=false) {
			pNext->render();
			MyDrawEngine::GetInstance()->WriteInt(50, 50, GameObjectList.size(), MyDrawEngine::GREEN);
		}
		else {
			ErrorLogger::Writeln(L"Null pointer in Object Manager - RenderAll function");
		}
	}
}

void ObjectManager::UpdateAll(float frametime) {
	for (GameObject* pNext : GameObjectList) {
		if (pNext != nullptr && pNext->active != false) {
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

void ObjectManager::deleteThis() {
	for (GameObject* pNext : GameObjectList) {
		delete pNext;
		pNext = nullptr;
	}
	GameObjectList.clear();
}

void ObjectManager::deleteInactive() {
	for (GameObject*& pNext : GameObjectList) {
		if (pNext != nullptr && pNext->active == false) {
			delete pNext;
			pNext = nullptr;
		}
	}
	GameObjectList.remove(nullptr);
}

void ObjectManager::CheckAllCollisions() {
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;
	for (it1 = std::next(it1); it2 != GameObjectList.end(); it2++) {
		for (it2 = std::next(it1); it2 != GameObjectList.end(); it2++) {
			if ((*it1)->GetShape().Intersects((*it2)->GetShape())) {
				if ((*it1)->isActive() && (*it2)->isActive()) {
					if ((*it1) != nullptr && (*it2) != nullptr) {
						(*it1)->ProcessCollision((*it2));
						(*it2)->ProcessCollision((*it1));
					}
				}
			}
		}
	}
}