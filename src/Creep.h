#ifndef CREEP_H
#define CREEP_H

#include "Agent.h"

class Creep: public Agent{
 
	public:
		Creep (float x, float y, float width, float height, float speed);
		Creep (const Creep& c1); //copy constructor
		int test2{1};
		void determineCentre();
		//void behaviour(int mapX, int mapY) override;
	protected:

		void initShape();
		void updateShape();

		void recurseShape(int x, int y, float prob);

};

#endif