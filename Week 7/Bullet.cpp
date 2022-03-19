#include "Bullet.h"

Bullet::Bullet() {
	//Bullets constructor
	active = true;
	//Setting active to true so the ObjectManager knows it doesn't have to delete this object yet
	timer = deleationDelay;
}

void Bullet::Initialise(Vector2D location, float angle) {
	//Initialising based upon a Vector2D for the spawn location, and a float for the angle that the bullet is traveling in
	GameObject::loadImage(L"bullet.bmp");
	//Loading a provided image reference for the image to be drawn
	GameObject::loadSound(L"shoot.wav");
	//Providing a sound file reference for the sound that will play when drawn
	Velocity.setBearing(angle, 1000.0f);
	//Setting the bearing of the bullet based upon the angle of the ship, at a speed of 100f
	pos = location;
	this->angle = angle;
}

void Bullet::update() {
	pos = pos + Velocity * 0.016; 
	//Setting the current location impacted by the speed and direction of velocity, while being limited by the frametime - to keep all speeds capped
	timer = timer - frameTime;
	//Count down to setting the bullets active status to false
	if (timer < 0.0f) {
		active = false;
		//Setting this to false will allow for the ObjectManager to delete this instance of a bullet
		//This will save on screen clutter, and system memory 
	}
}