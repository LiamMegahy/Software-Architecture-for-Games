#include "Vehicle.h"
Vehicle::Vehicle()
{
	fuel = 100;
	passengers = 0;
	std::cout << "A vehicle has been created.\n";
}


void loadPassengersAndGo(Vehicle& vehicle)
{
	vehicle.loadPassenger();
	vehicle.loadPassenger();
	vehicle.move();
}

void Vehicle::move()
{
	fuel = fuel - 1;
	std::cout << "Vroom! Vehicle is moving.\n";
	std::cout << "Current fuel is : " << fuel << "\n";
}
void Vehicle::loadPassenger()
{
	passengers++;
	std::cout << "The vehicle now has " << passengers << " passengers.\n";
};