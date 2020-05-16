#include "renderer.h"
#include <iostream>
#include <string>




Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Run Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
 // sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}


void Renderer::Render(GameState* gameState) {
 // std::cout<< "rendering" << std::endl;
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  //Render player
  if (gameState->getPlayer()->getHuman()->getDying()){
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }else{
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  }

  block.x =gameState->getPlayer()->getHuman()->getX()*block.w;;
  block.y = gameState->getPlayer()->getHuman()->getY()*block.h;
  SDL_RenderFillRect(sdl_renderer, &block);
  block.y = (gameState->getPlayer()->getHuman()->getY() +1)*block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  //Render all bots and NPC humans
  
  std::vector<GameObject*> gos = gameState->getCurrentLevel().getGameObjects();
  for (GameObject* go : gos) {
  // std::cout << "memory ref: " << go <<std::endl;
   //std::cout << "here1 " << std::endl;
    switch(go->getType()){
      case GameObject::GOType::CREEP:{
       // std::cout << "here1.5" << std::endl;
       // std::cout << "isDying" << go->toRemove() << std::endl;
        Agent* c = dynamic_cast<Agent*>(go);
       // std::cout << "here2" << std::endl;
       // std::cout << " type:  " << go->getType() << std::endl;
        //std::cout << "ID: " <<c->getId() << " x:  " << c->getX() << " y: " << c->getY() << " width: " << c ->getWidth() << " height: " << c->getHeight() << std::endl;
     //   Array2D<int>* shapeMap = c->getShapeMap();
       // std::cout << "here2.5" << std::endl;
        float x = c->getX();
        float y = c->getY();
        int width = c->getWidth();
        int height = c->getHeight();
        
        if (c->getDying()){
          SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
        }else{
          SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
        }

       // std::cout << "here3" << std::endl;
        for (int i = 0; i < width; i++){
          for (int j = 0; j < height; j++){
          
            if (c->getShapeMap()->operator()(i,j)==1){
              if (x+i < grid_width && y+j<grid_height){
                 // std::cout << "       i: " << i << " j:" << j<<"       x+i: " << x+i << " y+j:" << y+j<<std::endl;
                  block.x = (x+i) * block.w;
                  block.y = (y+j) * block.h;
                  SDL_RenderFillRect(sdl_renderer, &block);
              }
            }
          }
        }
       // std::cout << "here4" << std::endl;
        break;}
      case GameObject::GOType::HUMAN:
        //TODO: NPCs only
        break;
      case GameObject::GOType::TELE:
        break;
      case GameObject::GOType::TIME:
        break;
    }
   // std::cout << "here5" << std::endl;
  }
  //std::cout << "here6" << std::endl;

  //Render Items


  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}
/**void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}
**/
void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Run  FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
