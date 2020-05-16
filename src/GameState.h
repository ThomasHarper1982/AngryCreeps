#include <vector>
#include "Human.h"
#include "Item.h"
#include "Creep.h"
#include "GameObject.h"
#include "Agent.h"
#include "Array2D.h"
#include <memory>
#include <cassert>
#include "DetectionMap.h"
#ifndef GAMESTATE_H
#define GAMESTATE_H

class LevelState{
	public:
		~LevelState();
  		LevelState();
  		LevelState clone();
  		void flushAgents(bool deadOnly);
		int getTime(){return time;};
		//std::vector<GameObject*> getGameObjects();
		std::vector <GameObject*> gameObjects;
		std::vector<GameObject*> getGameObjects(){return gameObjects;};
  	private:
		int move;
  		int time;

};



class GameState{
	public:
  		void init();
		~GameState();  
		GameState(int mapX, int mapY);
		void checkCollisions(bool spare_first);
		void Update();
		void getStats();
		void endGame();
		//void setRestartGame();
		bool hasEnded(){return restartGame;};
		void HumanBehave(Human* h);
		void CreepBehave(Creep* c);
		void BoundaryCheck(Agent* a, int& del_x, int& del_y);
		void submitDetectionMap(Agent* agent);
		void submitDetectionMap();
		void placeHuman();
		void handleGameOver();
		Player* getPlayer(){return player;};
		LevelState getCurrentLevel(){return current;};
		void testCreatureShapes();
		void testCreatureShape(Creep* c);
		void testDeletionMapPopulated();
		void testDyingCreatures();
		void Teleport(Human*h);
		void setGameOver(){gameOver =true;};
		bool getGameOver(){return gameOver;};
		int getMapX(){return mapX;};
		int getMapY(){return mapY;};
  	private:
  		//std::vector <LevelState> levelStates; later version
  		LevelState current;
		Player* player;
		int mapX;
		int mapY;
		int move{0};
		bool gameOver{false};
		bool restartGame{false};
		//
		DetectionMap detectionMap;
				
		
		
};

#endif