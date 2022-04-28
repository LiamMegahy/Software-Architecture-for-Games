#include <iostream>
#include "Spaceship.h"
#include "mydrawengine.h"

Spaceship::Spaceship(ObjectManager& TheObjectManager): om(TheObjectManager) {
	active = true;
	//Constructor for the Spaceship is run once the ship has been created
	//Setting active to true so the Object Manager knows to update and not delete this object
}

void Spaceship::initialise(Vector2D location) {
	loadImage(L"ship.bmp");
	//Providing the required file reference for the ships image
	pos = location;
	//Taking the passed parameters and setting it to a local variable for later usage
	velocity = { 0.0f, 0.0f };
	gravity = { 0.0f, -10.0f };
	//Providing 2 Vector 2D's with their initial values - these may or may not be changed later during gameplay
	angle = 0;
	//Setting a starting Angle (measured in Radians)
}

void Spaceship::update() {
	move();
	//Each frame, call the move function - allows for movement at all times as this is called each frame
}

void Spaceship::move() {
	MyInputs* pInputs = MyInputs::GetInstance();
	//Calling upon the MyInputs class and creating a local instance of this
	pInputs->SampleKeyboard();
	//Setting the control method to be the keyboard
	Vector2D acceleration(0, 0);
	//Creating a local variable handle the direction of acceleration within gameplay
	if (pInputs->KeyPressed(DIK_W)) {
		acceleration.setBearing(angle, 500.0f);
		//Moving upon the set angle, moving within the Y axis at a speed of 500
	}
	if (pInputs->KeyPressed(DIK_S)) {
		acceleration.setBearing(angle, -50.0f);
		//Moving upon the set angle, moving within the Y axis at a speed of -50
	}
	if (pInputs->KeyPressed(DIK_A)) {
		angle = angle - rotation * frameTime;
		//Setting the new angle to rotate bearing left, limited speed by FrameTime variable
	}
	if (pInputs->KeyPressed(DIK_D)) {
		angle = angle + rotation * frameTime;
		//Setting the new angle to rotate bearing right, limited speed by FrameTime variable
	}
	if (pInputs->NewKeyPressed(DIK_F)) {
		if (timer <= 0) {
			Bullet* pBullet = new Bullet;
			//Creating a new instance of a bullet, making it a pointer to a bullet
			pBullet->Initialise(pos, angle);
			//Initialising its location to be the current location and angle of the Spaceship
			om.AddObject(pBullet);
			//Passing this new bullet to the object manager to handle
			timer = shotDelay;
			//Resetting the timer to delay the next shot
		}
	}

	timer -= frameTime;
	//Counting down so the user can fire the gun again after a set time, 0.5f

	acceleration += gravity;
	//Factoring in Gravity to the current value of the acceleration, so it's moving in its given direction
	//While also being effected by the gravy on the Y axis
	velocity = velocity + acceleration * frameTime;
	//Factoring in acceleration into the overall velocity of the ship (so it's accelerating while also having gravity effect its bearing)
	friction = -0.5 * velocity;
	//Limiting the top speed by having friction build up over time based on the current speed of the ship
	velocity = velocity + friction * frameTime;
	//Setting the current velocity to be the original value, with the impact of friction to limit top speed and create a feeling of inertia while moving
	pos = pos + velocity * frameTime;
	//Updating the location based upon the previous location, the speed and direction of the velocity, all limited by the value of 60fps
}