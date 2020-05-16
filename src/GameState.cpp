#include "GameState.h"
//#include "GameObject.h"

#include <random>
#include <iostream>

LevelState::~LevelState(){
 	gameObjects.clear();
}


LevelState::LevelState(){
 	gameObjects = std::vector<GameObject*>();
}

LevelState LevelState::clone(){
  LevelState l;
 	return l; 
}

void LevelState::flushAgents(bool deadOnly){
    if (!deadOnly){ //remove dead and alive
      gameObjects.clear();
    }

    for (std::vector<GameObject*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {//Error 2-4
          
          if (deadOnly && (*it)->toRemove()){ //remove only the dead
            gameObjects.erase(it);
          //  delete it;
          }
    }
}

/**
std::vector<GameObject*> LevelState::getGameObjects() {
  return gameObjects;
}**/

void GameState::testCreatureShape(Creep* c){

      Array2D<int>* shapeMap = c->getShapeMap();
      std::cout << "Creep ID: " << c->getId() << std::endl;
      std::cout << "W " << c->getWidth() << " H: " << c->getHeight() << std::endl;
      for (int i =0; i < c->getWidth(); i++){
        for (int j = 0; j < c->getHeight(); j++){
            if (shapeMap->operator()(i,j)==1){
              std::cout << "("<<i << ", " <<j  <<")"<<std::endl;
            }
        }
      }
}

void GameState::testCreatureShapes(){
  //loop over the CreatureObjects
  for (GameObject* o : current.gameObjects){
    if (o->getType() == GameObject::GOType::CREEP){
      Creep* c = dynamic_cast<Creep*>(o);
      testCreatureShape(c);
      //test now does it retain a field set within Agent
    }
  }


}

void GameState::testDeletionMapPopulated(){
  
}

void GameState::testDyingCreatures(){

}


GameState::~GameState(){
}

GameState::GameState(int mapX_, int mapY_):mapX(mapX_), mapY(mapY_){

  //detectionMap =  DetectionMap(mapX_, mapY_);
//Array2D<std::vector<Agent *, std::allocator<Agent *>> *> test = new Array2D<std::vector<Agent *, std::allocator<Agent *>> *>(mapX, mapY);
 // detectionMap =  Array2D<std::vector<Agent*>>(mapX_, mapY_);
 // detectionMap =  Array2D<std::unique_ptr<std::vector<Agent*>>>(mapX_, mapY_);
  // detectionMap = new Array2D<std::vector<Agent*>*>(mapX_, mapY_);
// typedef boost::multi_array<int, 2> array_type;
  //array_type detectionMap(boost::extents[mapX][mapY]);
  //detectionMap<Agent*>(mapX_,mapY_);
};

void GameState::placeHuman(){
  //choose random spot on map


    float x = std::rand()%mapX;
    x = std::min(std::max(x, 3.0f), mapX-3.0f);
    float y = std::rand()%mapY;
    y = std::min(std::max(y, 3.0f), mapY-3.0f);

    float width = 1;
    float height = 2;
    float speed = 1;
    //  Human* human =  new Human(x,y,width, height, speed);
     
    Human* human =  new Human(x,y,width, height, speed);
    
    current.gameObjects.emplace_back(human);
    //std::cout << "here2" << std::endl;
    player = new Player();
    human->setPlayer(player);
    player->setHuman(human);
    human->setTele(3);
  //  std::cout << "human " << human << " " << human->getType() << " player " <<  player<< std::endl;
    //std::cout << "here3" << std::endl;
}

void GameState::init(){
  //  srand(move);
    restartGame = false;
  //  std::cout << "Game init start" << std::endl;
    detectionMap =  DetectionMap(mapX, mapY);
    int num_creeps = 10;
    int num_tele = 4;
    int num_timet = 1;
    Agent::count = 0;
 //randomly initialise and determine the position of X creeps
  for (int i = 0; i < num_creeps; i++){
   // std::cout << "init creep:" << i << std::endl;
    int x = std::rand()%mapX;
    int y = std::rand()%mapY;
    int width = std::rand()%2+4;
    int height = std::rand()%2+4;
    int speed = std::rand()%1+1;
   // Creep creep(x,y,width, height, speed);
    //make this unique pointer??
  //  std::cout << x << " " << y << " " << width << " " << height << " " << speed << std::endl;
    Creep *creep = new Creep(x,y,width, height, speed);
  //  std::cout << creep << std::endl;
    //testCreatureShape(creep);

     //std::vector<Agent> test;
    //test.push_back(dynamic_cast<GameObject>(creep));
    current.gameObjects.emplace_back(creep);
    submitDetectionMap(creep);
    
  }
 
  //kill off overlapping creeps, -> later iteration keep the first remove the rest
  checkCollisions(true);
  detectionMap.clearMap();
  //getStats();
   //
  //create human player
  //TODO place human/player randomly in safe spot (in future version)
  
  placeHuman();
 
  current.flushAgents(true);
 // std::cout << "here " << std::endl;
  //exit(0);
   //seed the pseudo random number generator at every checkpoint
//  std::cout << "Game init end" << std::endl;
}

void GameState::submitDetectionMap(){
  for (GameObject* o : current.gameObjects){
    if (o->getType() == GameObject::GOType::HUMAN || o->getType() == GameObject::GOType::CREEP){
      Agent* a = dynamic_cast<Agent*>(o);
      Creep* c = dynamic_cast<Creep*>(o);


    }
    
  }
}



void GameState::submitDetectionMap(Agent* agent){
  //std::cout << "detection map " << agent->getId()  << " " << agent << std::endl;
  float x = agent->getX();
  float y = agent->getY();
  int width = agent->getWidth();
  int height = agent->getHeight();
 // std::cout << "x : " << x << "y " << y << "width : " << width << "height " << height << std::endl;
//  std::cout << "mapX : " << mapX << " mapY " << mapY <<  std::endl;
  Array2D<int> *shapeMap = agent->getShapeMap();
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
     
     if (agent->getShapeMap()->operator()(i,j)==1){
       if (x+i < mapX && y+j<mapY){
        // std::cout << "       i: " << i << " j:" << j<<"       x+i: " << x+i << " y+j:" << y+j<<std::endl;
         TileBin tileBin = detectionMap.operator()(x+i,y+j);
         
         std::vector<Agent*>* t = tileBin.getTileBin();
       //  std::cout << "t->size()" << t->size() <<std::endl;
         t->emplace_back(agent);

        
       }
      }
    }
  }
  //std::cout << "detection map: end" << agent->getId()  << " " << agent << std::endl;
}


void GameState::getStats(){
  int co = 0;
  for (GameObject* o : current.gameObjects){
    if (o->getType() == GameObject::GOType::HUMAN || o->getType() == GameObject::GOType::CREEP){
        Creep* c = dynamic_cast<Creep*>(o);
        if (!c->getDying()){
          std::cout << "ID: " <<c->getId() << " x:  " << c->getX() << " y: " << c->getY() << " width: " << c ->getWidth() << " height: " << c->getHeight() << std::endl;
          co++;
        }
    }
  }
  std::cout << "survivors : " << co << std::endl;
}

void GameState::checkCollisions(bool spare_first){

  //at this stage all Agents already submit their positions to the DetectionMap already
  for (int i = 0; i < mapX; i++){
      for (int j = 0; j < mapY; j++){
        std::vector<Agent*>* agents = detectionMap.operator()(i,j).getTileBin();
        if (agents->size()>=2){
           //  std::cout << "Bin: i: " << i << " j:" << j<< " size: " << agents->size()<< std::endl;
             int c = 1;
             for (std::vector<Agent*>::iterator it = agents->begin() ; it != agents->end(); ++it){
                 if (!(*it)->getDying()){
                    if (!spare_first || c!=1){
                      (*it)->setDeath();
                   //   std::cout << "Died: " << (*it) << "type "<<(*it)->getType() << std::endl;
                    }else{
                   //   std::cout << "Survived: " << (*it)->getId() << std::endl;
                    }
                 }

                c++;
             }
        }
    }
  }
  
//  for (GameObject gameObject : current.){
 // }
}

void GameState::BoundaryCheck(Agent* a, int& del_x, int& del_y){
//check whether shape boundary is within grid boundary -> no return
  int x = a->getX();
  int y = a->getY();
  int w = a->getWidth();
  int h = a->getHeight();
  int X0 = x+del_x ;
  int Y0 = y+del_y ;
  int X1 = x+w+del_x;
  int Y1 = y+h+del_y;
  //std::cout << "X0: " <<X0 << " Y0: " << Y0 << " X1 : " << X1 << " Y1 : " << Y1 << " mapX: " << mapX << " mapY: " << mapY << std::endl;
  if (X0 >= 0 && Y0 >= 0 && X1 < mapX && Y1 <mapY){

   // std::cout << "no overlap  " << std::endl;
    return;
  }else{
   // std::cout << "overlap  " << std::endl;
  
    //else check whether shape map collides with boundary, set del_x, del_y->0 return
    Array2D<int> *shapeMap = a->getShapeMap();
    for (int i = 0; i < w; i++){
        for (int j = 0; j < h; j++){
          //  std::cout << " i " << i << " j " << j << "map" << shapeMap->operator()(i,j) << std::endl;
            if (shapeMap->operator()(i,j) > 0){

              int X = x+i+del_x;
              int Y = y+j+del_y;
             //  std::cout << "?? X: " <<X << " Y: " << Y << std::endl;
              if (!(X >= 0 && X < mapX)){
               
                //if the boundary condition fails for any tile of agent->no move
                  del_x = 0;
                  
               }
              if (!( Y >= 0 && Y <mapY)){
               
                //if the boundary condition fails for any tile of agent->no move
                  del_y = 0;
                  
               }
            }
        }
    }
  } 

//yes -> block move
}

void GameState::Teleport(Human* h){
  int tokens = h->getTele();
  if (tokens>0){
      float new_x = std::rand()%mapX;
      float new_y = std::rand()%mapY;
      h->setX(new_x);
      h->setY(new_y);
      tokens--;
      h->setTele(tokens);
  }

}

void GameState::HumanBehave(Human* h){
 
  Player* p =h->getPlayer();
  //std::cout << "Human behave " << h <<" " << p <<  std::endl;
 // std::cout << "Player " << player <<" " << player->getHuman() <<  std::endl;
  int del_x = 0;
  int del_y = 0;
  if (h->getPlayer()!=nullptr){
  //  std::cout << "Player behave:" << " x:  " << h->getX() << " y: " << h->getY()<< std::endl;
    Action* action = player->getCurrentAction();
  //  std::cout << "here1" << action <<  std::endl;
   // std::cout << "here2" << action->getType()<<  std::endl;
    switch(action->getType()){
        case Action::Type::U:{
        //  std::cout << "here3" << std::endl;
          del_y-=h->getSpeed();
          break;
        }case Action::Type::D:{
          del_y+=h->getSpeed();
          break;
        }
        case Action::Type::L:{          
          del_x-=h->getSpeed();
          break;}
        case Action::Type::R:{
          del_x+=h->getSpeed();
          break;
        }
        case Action::Type::TL:{
          del_x-=h->getSpeed();
          del_y-=h->getSpeed();
          break;
        }

        case Action::Type::TR:{
          del_x+=h->getSpeed();
          del_y-=h->getSpeed();
          break;
        }

        case Action::Type::BL:{
          del_x-=h->getSpeed();
          del_y+=h->getSpeed();
          break;
        }

        case Action::Type::BR:{
          del_x+=h->getSpeed();
          del_y+=h->getSpeed();
          break;
        }

        case Action::Type::TELE:{
          Teleport(h);
          break;
        }

        case Action::Type::TT:{
          break;
        }

        case Action::Type::NOTHING:{
          break;
        }
    }
   // std::cout << "change del x:  " << del_x << " del y: " << del_y << std::endl;
    BoundaryCheck(h, del_x, del_y);
    if (del_x!=0 || del_y!=0){
      h->move(del_x, del_y);
    }
   //  std::cout << "Player behave: end" << " x:  " << h->getX() << " y: " << h->getY()<< std::endl;
  }else{
    //TODO : NPC behaviour if time travel feature included 
  }
  submitDetectionMap(h);
}



void GameState::CreepBehave(Creep* c){
//  std::cout << "Creep Behave " << std::endl;
  //get direction from centre of creep to player
 // std::cout <<  " x "<<c->getX()<<  " y " << c->getY()<<  " w " << c->getWidth()<<  " h " << c->getHeight()<<  " " << std::endl;
  //std::cout <<  "before: x_cen "<<c->getCenX()<<  " y_cen " << c->getCenY() << std::endl;
  c->determineCentre();
 // std::cout <<  "after: x_cen "<<c->getCenX()<<  " y_cen " << c->getCenY() << std::endl;
  int X_cen_abs = c->getX() + c->getCenX();
  int Y_cen_abs = c->getY() + c->getCenY();

  //in future, generalise this for closest human (not just player) -- TIME TRAVEL feature
  int playerX = player->getHuman()->getX();
  int playerY = player->getHuman()->getY();

  int del_x = 0;
  int del_y = 0;
    //make a delx, dely
  if (X_cen_abs > playerX){
      del_x -= c->getSpeed();
  }else if(X_cen_abs < playerX){
      del_x += c->getSpeed();
  }
  if (Y_cen_abs > playerY){
      del_y -= c->getSpeed();
  }else if(Y_cen_abs < playerY){
      del_y += c->getSpeed();
  }


  //perform Boundary Check
  BoundaryCheck(c, del_x, del_y);
  if (del_x!=0 || del_y!=0){
    c->move(del_x, del_y);
  }

  submitDetectionMap(c);
 // std::cout << "Creep behave: end" << " x:  " << c->getX() << " y: " << c->getY()<< std::endl;
  //BoundaryCheck(Agent* a, int& del_x, int& del_y)
  //move in direction of player#
 // std::cout << "Creep Behave :end " << std::endl;
}

void GameState::Update(){
  current.flushAgents(true);
 // detectionMap.clearMap();
 ///std::cout << "Update " << std::endl; 
  //iterate over all GameObjects and execute behaviour()
  std::vector<GameObject*> gos = getCurrentLevel().getGameObjects();
  for (GameObject* go : gos) {
  // std::cout << "memory ref: " << go <<std::endl;
   //std::cout << "here1 " << std::endl;
    switch(go->getType()){
      case GameObject::GOType::CREEP:{
        
        Creep* c = dynamic_cast<Creep*>(go);
        CreepBehave(c);
       // c->behaviour(mapX, mapY);
        break;}
      case GameObject::GOType::HUMAN:{
        Human* h = dynamic_cast<Human*>(go);
        HumanBehave(h);
       // h->behaviour(mapX, mapY);
        break;
      }
    }
   // std::cout << "here5" << std::endl;
  }
  //Check for collisions (creeps->player, creeps<->creeps)
 // std::cout << "player dying 0 " <<player->getHuman()->getDying() << std::endl;
  checkCollisions(false);
 // std::cout << "player dying 1 " <<player->getHuman()->getDying() << std::endl;
  if (player->getHuman()->getDying()){
    setGameOver();
  }

  detectionMap.clearMap();

  //check for GameOver -> handle memory

//std::cout << "Update :end " << std::endl; 
}


void GameState::endGame(){
 // std::cout << "restart " << std::endl; 
  restartGame =true;
  current.flushAgents(false);
 // std::cout << "flushed agents " << std::endl; 
 // init();
}
