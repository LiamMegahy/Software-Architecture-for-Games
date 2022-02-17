#include "gameObject.h"
class Vehicle : public gameObject
{
protected:
	double fuel;
private:
	int passengers;
public:
	Vehicle();
	virtual void move();
	void loadPassenger();
};