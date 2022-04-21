#include <iostream>
#include "GameObject.h"
#include "mydrawengine.h"
#include "Bullet.h"

GameObject::GameObject() {
	active = true;
	MyDrawEngine::GetInstance();
}

GameObject::~GameObject(){}

void GameObject::render() {
	if (active == true) {
		MyDrawEngine::GetInstance()->DrawAt(pos, model, scale, angle);
	}
	else {
		ErrorLogger::Writeln(L"Failed to load image");
	}
}

PictureIndex GameObject::loadImage(std::wstring fileName) {
	model = MyDrawEngine::GetInstance()->LoadPicture(fileName.c_str());
	return model;
}

void GameObject::update() {

}

void GameObject::HandleMessage() {

}

void GameObject::offScreen() {
	if (pos.XValue > 1800.0f || pos.XValue < -1800.0f) {
		pos.XValue *= -1;
	}
}

void GameObject::loadSound(std::wstring soundName) {
	sound = MySoundEngine::GetInstance()->LoadWav(soundName.c_str());
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	sound = pSE->LoadWav(soundName.c_str());
	pSE->Play(sound);
}

bool GameObject::isActive() const {
	return active;
}

void GameObject::deactivate() {
	active = false;
}