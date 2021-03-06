#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <boost/multi_array.hpp>


int main() {


  //std::initializer_list<size_t> l;

  //boost::multi_array<double, 3> A(boost::extent<int[1][1][1],1>);
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  
  game.Run(controller, renderer, kMsPerFrame);
  //std::cout << "Game has terminated successfully!\n";
//  std::cout << "Score: " << game.GetScore() << "\n";
 // std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}