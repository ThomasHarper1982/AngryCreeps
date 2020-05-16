#ifndef AGENT_H
#define AGENT_H

#include "GameObject.h"
#include "Array2D.h"

class Agent : public GameObject{
//	public:
	protected:
		//Agent(float x, float y, float speed);
  		
  		float speed;
  		bool dying{false};
		int id;
		
		int height;
		int width;
		int x_cen; //relative to top left shape map x
		int y_cen; //relative to top left shape map y
		Array2D<int>* shapeMap;
	//	virtual void behaviour(int mapX, int mapY){}; 
	public:
		
	    ~Agent();
		void move(int del_x, int del_y);
		float getX(){return x;};
		float getY(){return y;};
		void setX(float x_){x=x_;};
		void setY(float y_){y=y_;};
		int getCenX(){return x_cen;};
		int getCenY(){return y_cen;};
		float getSpeed(){return speed;};
		int getWidth(){return width;};
		int getHeight(){return height;};
		int getId(){return id;};
		void setDeath();
		bool getDying(){return dying;};
		Array2D<int>* getShapeMap(){return shapeMap;};
		int test1{1};
		static int count; // use this for the ID
	
};
#endif