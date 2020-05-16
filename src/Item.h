#include "GameObject.h" 
#ifndef ITEM_H
#define ITEM_H
class Item: public GameObject{
	 protected:
		Item(float x, float y);
		Item (const Item& i2); //copy constructor
		bool taken{false};
};


class TeleportToken: public Item{
	public:
		TeleportToken(float x, float y);
		
};

class TimeTravelToken: public Item{
	public:
		TimeTravelToken(float x, float y);
		
};
#endif
