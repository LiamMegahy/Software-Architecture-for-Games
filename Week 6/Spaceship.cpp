#include <iostream>
#include "Spaceship.h"
#include "mydrawengine.h"

Spaceship::Spaceship() {
	active = true;
	std::cout << "Spaceship" << "\n";
}

void Spaceship::initialise(Vector2D location) {
	loadImage(L"ship.bmp");
	pos = location;
	velocity = { 0.0f, 0.0f };
	gravity = { 0.0f, -10.0f };
	active = true;
	angle = 1;
}

void Spaceship::update() {
	move();
}

void Spaceship::move() {
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	Vector2D acceleration(0, 0);
	if (pInputs->KeyPressed(DIK_W)) {
		acceleration.setBearing(angle, 500.0f);
	}
	if (pInputs->KeyPressed(DIK_S)) {
		acceleration.setBearing(angle, -50.0f);
	}
	if (pInputs->KeyPressed(DIK_A)) {
		angle = angle - rotation * frameTime;
	}
	if (pInputs->KeyPressed(DIK_D)) {
		angle = angle + rotation * frameTime;
	}
	if (pInputs->KeyPressed(DIK_F)) {
		GameObject::loadSound(L"shoot.wav");
	}
	acceleration += gravity;
	velocity = velocity + acceleration * frameTime;
	friction = -0.5 * velocity;
	velocity = velocity + friction * frameTime;
	pos = pos + velocity * frameTime;
}