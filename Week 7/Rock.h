#pragma once
#include "GameObject.h"
#include "mydrawengine.h"
#include "GameObject.h"
class Rock : public GameObject {
	//New Class Rock inherets from GameObject
public:
	Rock();
	//Rocks constructor
	void Initialise(Vector2D location, float angle);
	//Used for initialising the starting locating and angle of the new GameObject - in the form of a Vector2D for the location
	//And the float for the Radians
	void update();
	//Classes own update function, as the ObjectManager can handle using each classes own member functions
	//This allows for more fine tuning of each object to function and work in different ways, more engaging gameplay
private:
	Vector2D Velocity;
	//Vector 2D for storing the velocity of an objects movement
};