#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

class Actor;
class Player;
class Level;
class Exit;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
	public:
		StudentWorld(std::string assetDir)
		 : GameWorld(assetDir), sub(0), levelComplete(false)
		{
		}
		~StudentWorld() {cleanUp();};
		virtual int init();
		virtual int move();
		virtual void cleanUp();
		virtual int getCurrentSubLevel();
		int numberOfKleptos(int x, int y);
		bool kleptoAt(int x, int y);
		bool isObstacle(int x, int y);
		bool isPlayerLoc(int x, int y);
		bool exitCanAppear();
		bool clearShot(int x, int y, int px, int py, GraphObject::Direction d);
		void levelCompleted(bool b) {levelComplete = b;}
		void addActor(Actor* a, int sub_level) {actors[sub_level].push_back(a);}
		void transport(int gateNum) {sub = gateNum;}
		void setDisplayText();
		void gotHealthGoodie();
		void gotAmmoGoodie();
		void getPlayerLoc(int &x, int &y);
		string statTextFormat(int score, int level, int sublevel, int lives,
											int hp, int ammo, int time);
		vector<Actor*> anyOtherActors(int x, int y);
	
	private:
		vector<vector<Actor*>> actors;
		vector<Player*> playa;
		Exit *ex;
		int time;
		int sub;
		bool levelComplete;
};

#endif // STUDENTWORLD_H_
