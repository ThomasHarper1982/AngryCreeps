#include "Item.h"


Item::Item(float x_, float y_){
    x = x_;
    y = y_;
}

TeleportToken::TeleportToken(float x, float y):Item(x,y){
    type = GameObject::GOType::TELE;
}

TimeTravelToken::TimeTravelToken(float x, float y):Item(x,y){
    type = GameObject::GOType::TIME;
}