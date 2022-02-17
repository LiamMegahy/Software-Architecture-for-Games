#include "gameObject.h"
class soldier : public gameObject
{
private:
	int ammo;
public:
	soldier();
	void move();
};