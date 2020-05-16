#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "GameState.h"

class Controller {
 public:

  void HandleInput(bool &running, GameState* gameState) const;
};

#endif