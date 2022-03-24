#pragma once
#include "GameObject.h"
#include <list>
#include <string>

class ObjectManager{
public:
	ObjectManager();
	void UpdateAll(float frametime);
	void RenderAll();
	void AddObject(GameObject* pNewObject);
	void deleteThis();
	void deleteInactive();
	void CheckAllCollisions();
private:
	std::list<GameObject*> GameObjectList;
};

