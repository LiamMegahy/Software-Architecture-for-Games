#include "ObjectManager.h"
#include <string>
#include <list>

ObjectManager::ObjectManager() {
	
}

void ObjectManager::RenderAll() {
	for (GameObject* pNext : GameObjectList) {
		if (pNext != nullptr && pNext->active!=false) {
			pNext->render();
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