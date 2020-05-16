#ifndef HUMAN_H
#define HUMAN_H

//#pragma once
#include "Agent.h"
//##include "Human.fwd.h"
//#include "Player.fwd.h"
class Player;

class Action{

    public:
        enum Type{U, D, L, R, TL, TR, BL, BR, TELE, TT, NOTHING};
        //use the index of action to denote the move instance
        //int moveInstance;
        Action(Type type_, int time_):type{type_},time{time_}{};
        Type getType(){return type;};
        ~Action();
    private:
        int time;
        Type type;
        int tele;
        Action getCurrentAction(); 
};


class Human: public Agent{
  public:
    ~Human();
    Human (float x_, float y_, float width_, float height_, float speed_);
    Human (const Human& h1); //copy constructor
    int getTele(){return tele;};
    void setTele(int tele_){tele = tele_;};
    Player* getPlayer(){return player;};
    void setPlayer(Player* player_){player=player_;};
  //	void behaviour(int mapX, int mapY) override;
  protected:


  private:
    int moveNum; //use this field to denote the player action vector
    Player* player;// if this field is null, then this is an AI and applies behaviour()
    int tele{0};

};
class Player{

    public:
        ~Player();
        Human* getHuman(){return human;};
        void setHuman(Human* human_){human = human_;};
        void setAction(Action::Type t, int time);
        
        Action* getCurrentAction(){return current;};
    private:
     //Player();
      std::vector<Action*> actions;
      Human* human;
      Action* current; //current action

   // private:
  
};
#endif