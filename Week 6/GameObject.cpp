#include <iostream>
#include "GameObject.h"
#include "mydrawengine.h"

GameObject::GameObject() {
	active = true;
	MyDrawEngine::GetInstance();
}

void GameObject::render() {
	if (active == true) {
		MyDrawEngine::GetInstance()->DrawAt(pos, model, 1, angle);
	}
	else {
		ErrorLogger::Writeln(L"Failed to load image");
	}
}

void GameObject::loadImage(std::wstring fileName) {
	model = MyDrawEngine::GetInstance()->LoadPicture(fileName.c_str());
}

void GameObject::update() {

}

void GameObject::loadSound(std::wstring soundName) {
	sound = MySoundEngine::GetInstance()->LoadWav(soundName.c_str());
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	sound = pSE->LoadWav(soundName.c_str());
	pSE->Play(sound);
}