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
	enum class EventType { BULLET_FIRED, CHASE, EXPLOSION };
	struct Message {
		EventType type;
		Vector2D location;
		GameObject* pSource;
		int otherData;
	};
	void SendMessage(Message msg);
private:
	std::list<GameObject*> GameObjectList;
	const float frameTime = 0.016f;
};

