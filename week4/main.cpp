#include "Tank.h"
#include "Soldier.h"
int main()
{
	//Vehicle x;
	//tank y;
	//soldier z;
	//z.move();

	gameObject* listOfObjects[5];
	listOfObjects[0] = new soldier();
	listOfObjects[1] = new soldier();
	listOfObjects[2] = new Vehicle();
	listOfObjects[3] = new Vehicle();
	listOfObjects[4] = new tank();
	std::cout << "\n";
	for (int i = 0; i < 5; i++)
	{
		listOfObjects[i]->move();
		std::cout << "\n";
	}
}
