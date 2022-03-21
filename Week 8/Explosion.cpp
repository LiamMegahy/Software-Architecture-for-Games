#include "Explosion.h"
#include <iostream>

Explosion::Explosion() {
}

void Initialise(Vector2D location) {
	pos = location;
	active = true;
	currentImage = 0;
}

void explosion(Vector2D location) {
	const wchar_t explosionSounds[6][25] = { L"explosion.wav", L"explosion1.wav", L"explosion2.wav", L"explosion3.wav",
	L"explosion4.wav", L"explosion5.wav" };
	PictureIndex model1 = MyDrawEngine::GetInstance()->LoadPicture(L"explosion1.bmp");
	PictureIndex model2 = MyDrawEngine::GetInstance()->LoadPicture(L"explosion2.bmp");
	PictureIndex model3 = MyDrawEngine::GetInstance()->LoadPicture(L"explosion3.bmp");
	PictureIndex model4 = MyDrawEngine::GetInstance()->LoadPicture(L"explosion4.bmp");
	PictureIndex model5 = MyDrawEngine::GetInstance()->LoadPicture(L"explosion5.bmp");
	PictureIndex model6 = MyDrawEngine::GetInstance()->LoadPicture(L"explosion6.bmp");
	PictureIndex model7 = MyDrawEngine::GetInstance()->LoadPicture(L"explosion7.bmp");
	PictureIndex model8 = MyDrawEngine::GetInstance()->LoadPicture(L"explosion8.bmp");
	PictureIndex temp[8][25] = { model1, model2, model3, model4, model5, model6, model7, model8 };

	for (int i = 0; i < 8; i++) {
		PictureIndex model = temp[i];
		MyDrawEngine::GetInstance()->DrawAt(location, model, 1);
	}

	int random = (rand() % 4 - 1);
	if (random = 1) {
		GameObject::loadSound(L"explosion.wav");
	}
	else if (random = 2) {
		GameObject::loadSound(L"explosion1.wav");
	}
	else {
		GameObject::loadSound(L"explosion2.wav");
	}
}