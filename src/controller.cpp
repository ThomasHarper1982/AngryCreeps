#include "controller.h"
#include <iostream>
#include "SDL.h"


void Controller::HandleInput(bool &running, GameState* gameState) const {
  SDL_Event e;
  Action::Type a;
 // std::cout << "handle input : start " << std::endl;

  bool waiting_for_input = true;
  while(waiting_for_input){
      if(SDL_PollEvent(&e)){
          if(e.type == SDL_QUIT){
              waiting_for_input = false;
          }else if(e.type == SDL_KEYDOWN){

            if (!gameState->getGameOver()){
              switch (e.key.keysym.sym) {
                case SDLK_w:{
                  a = Action::Type::U;
                  waiting_for_input = false;
                  break;
                }
                case SDLK_s:{
                  a = Action::Type::D;
                  waiting_for_input = false;
                  break;
                }
                case SDLK_a:{
                  a = Action::Type::L;
                  waiting_for_input = false;
                  break;
                }
                case SDLK_d:{
                  a = Action::Type::R;
                  waiting_for_input = false;
                  break;
                }
                case SDLK_q:{
                  a = Action::Type::TL;
                  waiting_for_input = false;
                  break;
                }
                case SDLK_e:{
                  a = Action::Type::TR;
                  waiting_for_input = false;
                  break;
                }
                case SDLK_z:{
                  a = Action::Type::BL;
                  waiting_for_input = false;
                  break;
                }
                case SDLK_c:{
                a = Action::Type::BR;
                waiting_for_input = false;
                  break;
                }
                case SDLK_r:{
                  a = Action::Type::TELE;
                  waiting_for_input = false;
                  break;
                }
                case SDLK_f:{
                  a = Action::Type::TT;
                  waiting_for_input = false;
                  break;
                }
                case SDLK_v:{
                  a = Action::Type::NOTHING;
                  waiting_for_input = false;
                  break;
                }
                case SDLK_b:{
                  exit(0);
                  break;
                }
              }
            }
            switch (e.key.keysym.sym) {
              case SDLK_n:{//quit game
                gameState->endGame();
                exit(0);
                waiting_for_input = false;
                break;
              }
              case SDLK_m:{
                //lets make this restart the game
                gameState->endGame();
                waiting_for_input = false;
               // exit(0);
                break;
              }

            }
        }
      }
  }

  gameState->getPlayer()->setAction(a, gameState->getCurrentLevel().getTime());
// std::cout << "handle input : end " << a << std::endl;
}