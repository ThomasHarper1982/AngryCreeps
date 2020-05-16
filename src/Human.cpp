#include "Human.h"
#include <iostream>

void Player::setAction(Action::Type t, int time){
    //add to action history
    Action* a =  new Action(t, time);
    actions.push_back(a);

    current = a;
    //set human behaviour

}

Player::~Player(){
  actions.clear();
  human = nullptr;
}

Human::~Human(){
  player = nullptr;
};

Action::~Action(){

}

Human::Human(float x_, float y_, float width_, float height_, float speed_){
   x = x_;
   y = y_;
   width = width_; 
   height = height_; 
   shapeMap = new Array2D<int> (width, height);
   //define Shape
  // std::cout << "here" <<std::endl;
 
   for (int i=0; i<width;i++){
      for (int j=0; j<height;j++){
        shapeMap->operator()(i,j) = 1;
  
      }  
   }
  // std::cout << "here1" <<std::endl;
   speed = speed_;
   type = GOType::HUMAN;
   Agent::count++;;
   id=Agent::count;
}
/**void Human::behaviour(int mapX, int mapY){
  //implement player behaviour ()
  if (player!=nullptr){
    Action* action = player->getCurrentAction();
    switch(action->getType()){
        case Action::Type::U:
          break;
        case Action::Type::D:
          break;
        case Action::Type::L:
          break;
        case Action::Type::R:
          break;
        case Action::Type::TL:
          break;
        case Action::Type::TR:
          break;
        case Action::Type::BL:
          break;
        case Action::Type::BR:
          break;
        case Action::Type::TELE:
          break;
        case Action::Type::TT:
          break;
    }

  }**/

  //TODO implement player/clone behaviour



