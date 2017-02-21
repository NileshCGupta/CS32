#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include <cstdlib>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject
{
    public:
        Actor(int image_ID, int x, int y, Direction start = none, int sub_level = 0, StudentWorld* sw = nullptr):
        GraphObject(image_ID, x, y, start, sub_level) {world = sw;};
        virtual void doSomething() = 0;
		virtual bool isDead() = 0;
		StudentWorld* getWorld() {return world;};
		virtual void damage() = 0;
	
	private:
		StudentWorld* world;
	
};

class Player: public Actor
{
    public:
        Player(int x, int y, int sub_level, StudentWorld* sw):
        Actor(0, x, y, right, sub_level, sw)
        {hp = 20; ammo = 0; setVisible(true);};
		void doSomething();
		bool isDead() {return hp == 0;}
		void damage();
		int getHp() {return (int)(hp/20.0 * 100);}
		int getAmmo() {return ammo;}
		void setHp(int hitp) {hp = hitp;}
		void incAmmo(int am) {ammo += am;}
	
    private:
        int hp;
        int ammo;
};

class Wall: public Actor
{
    public:
        Wall(int x, int y, int sub_level, StudentWorld* sw):
        Actor(6, x, y, none, sub_level, sw)
        {setVisible(true);};
		void doSomething() {};
		bool isDead() {return false;}
		void damage() {}

};

class Gate: public Actor
{
	public:
		Gate(int x, int y, int sub_level, StudentWorld *sw, int gNum):
		Actor(8, x, y, none, sub_level, sw) {gateNum = gNum; hp = 1; setVisible(true);}
		void doSomething();
		bool isDead() {return hp == 0;}
		void damage() {}

	private:
		int gateNum;
		int hp;
	
};

class Jewel: public Actor
{
	public:
		Jewel(int x, int y, int sub_level, StudentWorld *sw):
		Actor(9, x, y, none, sub_level, sw) {hp = 1; setVisible(true);}
		void doSomething();
		bool isDead() {return hp == 0;}
		void damage() {}
	
	private:
		int hp;
};

class Hostage: public Actor
{
	public:
		Hostage(int x, int y, int sub_level, StudentWorld *sw):
		Actor(3, x, y, none, sub_level, sw) {hp = 1; setVisible(true);}
		void doSomething();
		bool isDead() {return hp == 0;}
		void damage() {}
	
	private:
		int hp;
	
};

class Exit: public Actor
{
	public:
		Exit(int x, int y, int sub_level, StudentWorld *sw):
		Actor(7, x, y, none, sub_level, sw) {}
		void doSomething();
		bool isDead() {return false;}
		void damage() {}
};

class Bullet: public Actor
{
	public:
		Bullet(int x, int y, Direction dir, int sub_level, StudentWorld* sw):
		Actor(5, x, y, dir, sub_level, sw) {hp = 1; setVisible(true);};
		void doSomething();
		bool isDead() {return hp == 0;}
		void damage() {}

	private:
		int hp;
};

class ExtraLifeGoodie: public Actor
{
	public:
		ExtraLifeGoodie(int x, int y, int sub_level, StudentWorld *sw):
		Actor(11, x, y, none, sub_level, sw) {hp = 1; setVisible(true);};
		void doSomething();
		void damage() {hp = 0;}
		bool isDead() {return hp == 0;}

	private:
		int hp;
};

class RestoreHealthGoodie: public Actor
{
	public:
		RestoreHealthGoodie(int x, int y, int sub_level, StudentWorld *sw):
		Actor(10, x, y, none, sub_level, sw) {hp = 1; setVisible(true);};
		void doSomething();
		bool isDead() {return hp == 0;}
		void damage() {hp = 0;}
		
	private:
		int hp;
};

class AmmoGoodie: public Actor
{
	public:
		AmmoGoodie(int x, int y, int sub_level, StudentWorld *sw):
		Actor(12, x, y, none, sub_level, sw) {hp = 1; setVisible(true);};
		void doSomething();
		bool isDead() {return hp == 0;}
		void damage() {hp = 0;}
		
	private:
		int hp;
};
class SnarlBot: public Actor
{
	public:
		SnarlBot(int x, int y, Direction dir, int sub_level, StudentWorld *sw):
		Actor(1, x, y, dir, sub_level, sw), ticksCount(0) {hp = 15; setVisible(true);
														ticks = (28 - getWorld()->getLevel())/4;
														if(ticks < 3)
															ticks = 3;}
		void doSomething();
		bool isDead() {return hp == 0;}
		void damage();
	
	private:
		int hp;
		int ticks;
		int ticksCount;
};

class KleptoBot: public Actor
{
	public:
		KleptoBot(int x, int y, int sub_level, StudentWorld *sw):
		Actor(2, x, y, right, sub_level, sw), ticksCount(0), distanceMoved(0) {hp = 9; setVisible(true); goodieID = 0;
																			ticks = (28 - getWorld()->getLevel())/4;
																			distanceBeforeTurning = rand() & 3 + 1;
																			if(ticks < 3)
																				ticks = 3;}
		void doSomething();
		bool isDead() {return hp == 0;}
		void damage();
		
	private:
		int hp;
		int ticks;
		int ticksCount;
		int distanceBeforeTurning;
		int distanceMoved;
		int goodieID;
};

class KleptoBotFactory: public Actor
{
	public:
		KleptoBotFactory(int x, int y, int sub_level, StudentWorld *sw):
		Actor(4, x, y, none, sub_level, sw) {setVisible(true);}
		void doSomething();
		bool isDead() {return false;};
		void damage() {};	
};

#endif // ACTOR_H_
