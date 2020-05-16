#include "Agent.h"

int Agent::count = 0;

void Agent::setDeath(){
    dying=true;
    setRemove();
};

//boundary collisions already checked within game logic
void Agent::move(int del_x, int del_y){
    //update positon
    x+=del_x;
    y+=del_y;


}

Agent::~Agent(){
    shapeMap->clear();
}