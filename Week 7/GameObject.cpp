#include <iostream>
#include "GameObject.h"
#include "mydrawengine.h"
#include "Bullet.h"

GameObject::GameObject() {
	//Constructor for GameObject
	active = true;
	MyDrawEngine::GetInstance();
	//Creating a new instance of the MyDrawEngine, so this class can handle drawing file images to the screen
}

void GameObject::render() {
	if (active == true) {
		//If the currently selected object trying to run this function is active
		MyDrawEngine::GetInstance()->DrawAt(pos, model, 1, angle);
		//Draw this image to the screen with the provided variables as to the context of what and where
	}
	else {
		ErrorLogger::Writeln(L"Failed to load image, within the GameObject - Render function");
		//Log that an error has occured and where
	}
}

void GameObject::loadImage(std::wstring fileName) {
	//Function taking a standard Wstring for a filename of an image
	model = MyDrawEngine::GetInstance()->LoadPicture(fileName.c_str());
	//Setting the variable mode, used in Render, to be equal to the value of the filename provided in the functions parameters
}

void GameObject::update() {
	//Abstract, just used to be overwritten by other classes when GameObject is inhereted
}

void GameObject::loadSound(std::wstring soundName) {
	//Function taking a Standard Wstring, except this time for a sound file
	sound = MySoundEngine::GetInstance()->LoadWav(soundName.c_str());
	//Setting the variable sound to be equal to the provided file as part of loadSounds parameters
	MySoundEngine* pSE = MySoundEngine::GetInstance();
	//Creating a new instance of the MySoundEngine
	pSE->Play(sound);
	//Play the sound located within the variable sound (the provided file will then play)
}