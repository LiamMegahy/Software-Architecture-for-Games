#include <iostream>
#include "Spaceship.h"
#include "mydrawengine.h"

Spaceship::Spaceship() {
	isActive = true;
	std::cout << "Spaceship" << "\n";
}
void Spaceship::render() {
	if (isActive == true) {
		pDE = MyDrawEngine::GetInstance();
		model = pDE->LoadPicture(L"ship.bmp");
		pDE->DrawAt(pos, model, 1, direction);
	}
	else {
		std::cout << "null";
	}
}
void Spaceship::initialise(Vector2D location) {
	pos = location;
	velocity = { 0.0f, 0.0f };
	isActive = true;
	direction = 1;
}
void Spaceship::update() {

}
void Spaceship::move() {
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	if (pInputs->KeyPressed(DIK_W)) {
		Vector2D acceleration(0, 300);
		Vector2D friction = -10 * acceleration;
		velocity.setBearing(direction, 500.0f);
		velocity = velocity + acceleration * frameTime;
	}
	if (pInputs->KeyPressed(DIK_S)) {
		Vector2D acceleration(0, -300);
		Vector2D friction = -0.5 * acceleration;
		velocity.setBearing(direction, -50.0f);
		velocity = velocity + acceleration * frameTime;
	}
	if (pInputs->KeyPressed(DIK_A)) {
		Vector2D acceleration(-300, 0);
		velocity = velocity + acceleration  * frameTime;
		velocity.setBearing(direction, 4.0f);
	}
	if (pInputs->KeyPressed(DIK_D)) {
		Vector2D acceleration(300, 0);
		velocity = velocity + acceleration * frameTime;
		velocity.setBearing(direction, 4.0f);
	}
	if (pInputs->KeyPressed(DIK_LEFT)) {
		direction = direction - rotation * frameTime;
	}
	if (pInputs->KeyPressed(DIK_RIGHT)) {
		direction = direction + rotation * frameTime;
	}
	if (pInputs->KeyPressed(DIK_F)) {
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		//pSE->Play(shootSound);
	}
	pos = pos + velocity * frameTime;
}