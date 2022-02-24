#include <iostream>
#include "Spaceship.h"
#include "mydrawengine.h"

Spaceship::Spaceship() {
	isActive = true;
	std::cout << "Spaceship" << "\n";
}
void Spaceship::render(Vector2D location) {
	if (isActive == true) {
		pDE = MyDrawEngine::GetInstance();
		model = pDE->LoadPicture(L"ship.bmp");
		pDE->DrawAt(location, model, 1, direction);
	}
	else {
		std::cout << "null";
	}
}
void Spaceship::initialise(Vector2D location) {
	pos = location;
	velocity = { 0.0f, 0.0f };
	isActive = true;
}
void Spaceship::update() {

}

void Spaceship::move() {
	//render(pos);
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard();
	if (pInputs->KeyPressed(DIK_W)) {
		Vector2D move(0.0f, 2.0f);
		pos = pos + move;
		//render(pos);
	}
	if (pInputs->KeyPressed(DIK_S)) {
		Vector2D move(0.0f, -2.0f);
		pos = pos + move;
	}
	if (pInputs->KeyPressed(DIK_A)) {
		Vector2D move(-2.0f, 0.0f);
		pos = pos + move;
	}
	if (pInputs->KeyPressed(DIK_D)) {
		Vector2D move(2.0f, 0.0f);
		pos = pos + move;
	}
	if (pInputs->KeyPressed(DIK_LEFT)) {
		direction = direction - 0.5;
		velocity.setBearing(direction, 4.0f);
		//pos = pos + velocity;
	}
	if (pInputs->KeyPressed(DIK_RIGHT)) {
		direction = direction + 0.5;
		velocity.setBearing(direction, 4.0f);
	}
	if (pInputs->KeyPressed(DIK_F)) {
		MySoundEngine* pSE = MySoundEngine::GetInstance();
		//pSE->Play(shootSound);
	}
	pDE->DrawAt(pos, model, 1, direction);
}