#include "ObjectManager.h"
#include <string>
#include <list>

ObjectManager::ObjectManager() {
	//Constructor for the ObjectManager
}

void ObjectManager::RenderAll() {
	for (GameObject* pNext : GameObjectList) {
		//Itterating through the GameObjectList, setting the currently selected element within the list to be 
		//a gameObject pointer
		if (pNext != nullptr && pNext->active!=false) {
			//Checking if the currently selected list item is either a nullpointer or inactive
			pNext->render();
			//If they are not, then the ObjectManager will then find and run that specific objects relevent
			//render function, so each object can be handled in its own way using its own relevent member functions
		}
		else if (pNext == nullptr){
			ErrorLogger::Writeln(L"Null pointer in Object Manager - RenderAll function");
			//Log that there was a null pointer, however this will later be handled by the DeleteInactive function
		}
		else{
			ErrorLogger::Writeln(L"Inactive Object in Object Manager - RenderAll function");
		}
	}
}

void ObjectManager::UpdateAll(float frametime) {
	for (GameObject* pNext : GameObjectList) {
		//Same as with RenderAll
		if (pNext != nullptr && pNext->active != false) {
			//Same functionality as RenderAll
			pNext->update();
			//Rather than running Render on all items within GameObjectList, this instead runs the update function
		}
		else if (pNext == nullptr) {
			ErrorLogger::Writeln(L"Null pointer in Object Manager - UpdateAll function");
			//Log that there was a null pointer, however this will later be handled by the DeleteInactive function
		}
		else {
			ErrorLogger::Writeln(L"Inactive Object in Object Manager - UpdateAll function");
		}
	}
}

void ObjectManager::AddObject(GameObject* pNewObject) {
	//Function that takes, as a parameter, a Pointer to a GameObject - named pNewObject
	if (pNewObject != nullptr) {
		//Checking if the provided pointer is not null
		GameObjectList.push_back(pNewObject);
		//If the pointer is not Null, then this new pointer will be pushed onto the back of the GameObjectList List
	}
	else {
		ErrorLogger::Writeln(L"Null pointer in Object Manager - AddObject function");
		//Log that a null pointer was provided
	}
}

void ObjectManager::deleteThis() {
	for (GameObject* pNext : GameObjectList) {
		//Itterating through the entire GameObject list to delete all contents of pointers, and setting those pointers to null
		delete pNext;
		pNext = nullptr;
	}
	GameObjectList.clear();
	//Clearing the entire list, making it completely empty
}

void ObjectManager::deleteInactive() {
	for (GameObject*& pNext : GameObjectList) {
		//Itterating through the entire list of GameObjectList
		if (pNext != nullptr && pNext->active == false) {
			//If the currently selected list element is NOT a nullpointer, and is set as inactive 
			delete pNext;
			//Delete this element
			pNext = nullptr;
			//Set its pointer to null
		}
	}
	GameObjectList.remove(nullptr);
	//Remove all nullpointers within the GameObjectList
}

void ObjectManager::runFunctions(){
	RenderAll();
	UpdateAll(frameTime);
	deleteInactive();
}