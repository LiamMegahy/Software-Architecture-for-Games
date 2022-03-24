#pragma once
#include "GameObject.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "ObjectManager.h"
class Explosion : GameObject{
public:
	PictureIndex modelArray[8];
	Explosion(ObjectManager& TheObjectManager);
	void Initialise(Vector2D location);
	void explosion(Vector2D location);
	void explosionSounds();
	virtual void Render(Vector2D location);
	void deactiveExplosion();
	std::list<PictureIndex> explosionList;
	ObjectManager& om;
	IShape2D& GetShape();
	void ProcessCollision(GameObject* object, Vector2D location, float angle) override;
};

