#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
  public:
    virtual ~GameObject(){};
  	enum GOType{CREEP, HUMAN, TELE, TIME};
    float getX();
    float getY();
    GOType getType (){return type;};
    void setRemove(){remove = true;};
    bool toRemove(){return remove;};
  protected:
    bool remove{false};
    float x;
    float y;
    GOType type;
  //	virtual GameObject clone();
};

#endif