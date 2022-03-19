#pragma once
#include "errortype.h"
#include "windows.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "gametimer.h"
#include "myinputs.h"
#include <string>

class GameObject {
private:
	Vector2D position;
	PictureIndex model;
	SoundIndex sound;
	//Set of variables used for allowing for having the relevent variable data to be passed into GameObject.cpp
	//This would then allow for other classes or objects to simply pass in their relevent data for the picture and sound indexes, rather than having to handle them locally
public:
	GameObject();
	//Constructor for GameObject
	void render();
	//Function to allow for drawing of a fileimage to the screen with a set location via a Vector2D
	virtual void update();
	//Virtual Update function, meant to be a default for other classes to inheret from and override locally - as each object will update and move slightly differently
	//depending on their objects characteristics within gameplay
	bool active;
	//Bool Active will allow for objects to be set to not active, which can then be handled by the ObjectManager and deleted from memory - saving on lost memory
protected:
	Vector2D pos;
	//Vector 2D for setting the new objects location within the game space
	float angle;
	//Float measured in Radians for showing the current angle of the object
	void loadImage(std::wstring fileName);
	//Function to load an image from memory, taking in a standard Wstring for handling the passing of a filename - this will be taken as a Literal
	void loadSound(std::wstring soundName);
	//This function is similar in fuctionality to the loadImage function, however this instead handles sound
};