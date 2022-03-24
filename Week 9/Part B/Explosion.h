#pragma once
#include "GameObject.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include <list>
class ObjectManager;

class Explosion : public GameObject{
public:
	PictureIndex modelArray[8];
	Explosion();
	void Initialise(Vector2D location);
	void explosionSounds();
	void Render();
	void update();
	void deactiveExplosion();
	float currentImage = 0.0f;
	std::list<PictureIndex> explosionList;
	ObjectManager* om;
	IShape2D& GetShape();
	Circle2D m_collisionShape;
	void ProcessCollision(GameObject& object) override;
};

