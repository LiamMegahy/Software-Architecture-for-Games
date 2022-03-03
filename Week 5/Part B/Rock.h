#pragma once
#include "GameObject.h"
#include "mydrawengine.h"

class Rock : public GameObject {
public:
	Rock();
	void update();
	void fall();
};