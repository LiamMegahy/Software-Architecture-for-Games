#include "Tank.h"
tank::tank() {
	ammo = 10;
	std::cout << "A tank has been created" << "\n";
}
void tank::shoot()
{
	if (ammo > 0) {
		std::cout << "BANG!" << "\n";
		ammo = ammo - 1;
		std::cout << "Current ammo remaining is : " << ammo << "\n";
	}
	if (ammo <= 0) {
		std::cout << "*CLICK*" << "\n";
		ammo = 0;
		std::cout << "We're out of shells!" << "\n";
	}
}
void tank::magDump()
{
	while (ammo > 0) {
		if (ammo > 0) {
			std::cout << "BANG!" << "\n";
			ammo = ammo - 1;
			std::cout << "Current ammo remaining is : " << ammo << "\n";
		}
		if (ammo <= 0) {
			std::cout << "*CLICK*" << "\n";
			ammo = 0;
			std::cout << "We're out of shells!" << "\n";
		}
	}
}

void tank::move() {
	fuel = fuel - 5;
	std::cout << "CHONK CHONK CHONK, HERE COME LE TONK" << "\n";
	std::cout << "Current fuel is : " << fuel << "\n";
}