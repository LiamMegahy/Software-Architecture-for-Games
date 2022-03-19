#pragma once
#include "ObjectManager.h"

class Bullet : public GameObject
	//New class Bullet which inherets from the GameObject class - so it can use the default functions offered, like Render or Update
{
public:
	Bullet();
	//Creating the bullet constructor
	void Initialise(Vector2D location, float angle);
	//Function to initailise, based on a Vector2D for the location and a Float variable for the current angle (measured in Radians)
	void update()override;
	//Creating a new update function, overriding the contents of the default update function offered by the GameObject class
	//This will allow for active movement, as the default GameObject class does not handle moveable objects as default
private:
	Vector2D Velocity;
	const float frameTime = 0.016f;
	//Setting of Frametime locally within Bullet, cuts down on the required #Includes within the program - cutting down on dependencies
	const float deleationDelay = 5.0f;
	//Set variable for how long bullets should stay on the screen for, this will later be used as a check to switch the active status of the bullet object
	float timer;
};

