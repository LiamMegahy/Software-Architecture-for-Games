#pragma once
#include "GameObject.h"
#include <list>
#include <string>

class ObjectManager{
public:
	ObjectManager();
	//Constructor for the ObjectManager
	void UpdateAll(float frametime);
	//Update all takes the list of all current game objects, check if they are a null pointer or a inactive game object
	//If neither of these return true, it will access the specific objects "Update" function and run it
	//This allows for different objects to have their own relevent functions to be run instead of a generic default
	//This is also an example of Polymorphism
	void RenderAll();
	//Render all functions the same as UpdateAll, except it will instead run the relevent "Render" function of the 
	//Currently selected GameObject, while still performing the same checks on nullpointers and active status of the game object
	void AddObject(GameObject* pNewObject);
	//The add Object function will take in a GameObject pointer and check if this pointer is null, if it is not then it will add 
	//This new Pointer onto a list of other GameObject pointers, so they can then be used and worked on by the previously
	//Mentioned functions, which all use this "GameObjectList"
	void deleteThis();
	//This function deletes all currently stored GameObjects within "GameObjectList" once the game is over - this is called within GameCode.cpp
	//when the end of the game state has been reached
	void deleteInactive();
	//This function will take the full list of all GameObjects, and check if they are either a NullPointer or are currently set to inactive
	//If either of these are true, it will delete the contents of the pointer and then also delete the pointer - removing it from the list
	//This will also prevent possible memory leaks
	void runFunctions();
	const float frameTime = 0.016f;
	//Setting the value of frame time to 0.016 caps the framerate and correlating movement to a 60 frames per second limit
private:
	std::list<GameObject*> GameObjectList;
	//A list of GameObject pointers that will be used to store all gameObjects within the game
	//This will also be used to allow for the creation of new gameobjects to be easier to make and handle the functionality of running and updating
};

