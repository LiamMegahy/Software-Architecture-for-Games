#include "Rock.h"
#include <iostream>

Rock::Rock() {
	active = true;
	loadImage(L"rock1.bmp");
}

void Rock::update() {
	fall();
}

void Rock::fall() {
	Vector2D drop = { 0, -5 };
	pos = pos - drop;
}