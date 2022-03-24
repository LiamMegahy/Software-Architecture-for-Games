#include "Explosion.h"
#include <iostream>

Explosion::Explosion(ObjectManager& TheObjectManager) : om(TheObjectManager) {
}

void Explosion::Initialise(Vector2D location) {
	active = true;
	om.AddObject(this);
	modelArray[0] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion1.bmp");
	modelArray[1] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion2.bmp");
	modelArray[2] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion3.bmp");
	modelArray[3] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion4.bmp");
	modelArray[4] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion5.bmp");
	modelArray[5] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion6.bmp");
	modelArray[6] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion7.bmp");
	modelArray[7] = MyDrawEngine::GetInstance()->LoadPicture(L"explosion8.bmp");
	//modelArray[8] = { model1, model2, model3, model4, model5, model6, model7, model8 };
	explosionSounds();
	explosion(location);
}

void Explosion::Render(Vector2D location) {
	int random = (rand() % 4 - 1);
	for (int i = 0; i < 8; i++) {
		MyDrawEngine::GetInstance()->DrawAt(location, modelArray[i], 1, random, 1);
	}
}

void Explosion::explosion(Vector2D location) {
	

	
		//PictureIndex model = modelArray[i];
		//Render(location, model);
	//}
}

void Explosion::explosionSounds() {
	int random = (rand() % 4 - 1);
	if (random == 1) {
		GameObject::loadSound(L"explosion.wav");
	}
	else if (random == 2) {
		GameObject::loadSound(L"explosion1.wav");
	}
	else {
		GameObject::loadSound(L"explosion2.wav");
	}
}

void Explosion::deactiveExplosion() {
	this->active = false;
}