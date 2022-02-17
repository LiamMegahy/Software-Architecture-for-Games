#include "Vehicle.h"
#include "gameObject.h"
class tank : public Vehicle {
private:
	int ammo;
public:
	tank();
	void shoot();
	void magDump();
	void move();
	int getAmmo() const;
};

