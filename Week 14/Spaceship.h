#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "myinputs.h"
#include "GameObject.h"
#include "Bullet.h"

class Spaceship : public GameObject {
	//Creating a new class, Spaceship, and inherting from GameObject
private:
	Vector2D velocity;
	Vector2D friction;
	const int rotation = 4;
	//Variable for setting the rotation speed for the ship
	const float frameTime = 0.016f;
	//Setting the framerate to 60fps, for the purposes of frame limited movement speed
	const float shotDelay = 0.5f;
	//Variable for the shot delay, delays the ability to press the fire button by a set float value
	float timer;
	//Timer for counting down between shots
	Vector2D gravity;
	//Gravity to have a constant force applied in a negative force on the Y Axis (constantly moving down)
	ObjectManager &om;
	//New reference to the ObjectManager so it can be used and called upon locally
public:
	Spaceship(ObjectManager& TheObjectManager);
	//Constructor for the Spaceship, which will take a ObjectManager passed by Reference - so it can be used locally
	//Without also increasing the level of dependency within the program, it's not being #Included 
	void initialise(Vector2D location);
	//Initailise function which will take a 2D Vector to store the starting location within the game
	void update();
	void move();
};