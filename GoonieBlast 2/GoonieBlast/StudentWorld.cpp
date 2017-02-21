#include "StudentWorld.h"
#include <string>
#include "Level.h"
#include "Actor.h"
#include "GraphObject.h"
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
	time = 1500;
	sub = 0;
	
	ostringstream os_main;
	os_main << "level";
	if(getLevel() < 10)
		os_main << "0";
	os_main << getLevel();
	
	Level lev(assetDirectory());
	
	// loads first sub level of current main level
	string firstLevel = os_main.str() + ".dat";
	Level::LoadResult result = lev.loadLevel(firstLevel);
	
	
	// loads all sub levels of current main level
	while(sub < MAX_SUB_LEVEL && result != Level::load_sublevel_fail_file_not_found && result != Level:: load_fail_bad_format)
	{
		actors.push_back(*new vector<Actor*>);
		
		for(int x = 0; x < VIEW_WIDTH; x++)
		{
			for(int y = 0; y < VIEW_HEIGHT; y++)
			{
				Level::MazeEntry item = lev.getContentsOf(x, y, sub);
				
				switch(item)
				{
					case Level::player:
					{
						Player *p = new Player(x, y, sub, this);
						playa.push_back(p);
						actors[sub].push_back(p);
						break;
					}

					case Level::wall:
					{
						Wall *w = new Wall(x, y, sub, this);
						actors[sub].push_back(w);
						break;
					}
					
					case Level::jewel:
					{
						Jewel *j = new Jewel(x, y, sub, this);
						actors[sub].push_back(j);
						break;
					}
					
					case Level::gate0:
					{
						Gate *g = new Gate(x, y, sub, this, 0);
						actors[sub].push_back(g);
						break;
					}
					
					case Level::gate1:
					{
						Gate *g = new Gate(x, y, sub, this, 1);
						actors[sub].push_back(g);
						break;
					}
					
					case Level::gate2:
					{
						Gate *g = new Gate(x, y, sub, this, 2);
						actors[sub].push_back(g);
						break;
					}
					
					case Level::gate3:
					{
						Gate *g = new Gate(x, y, sub, this, 3);
						actors[sub].push_back(g);
						break;
					}
					
					case Level::gate4:
					{
						Gate *g = new Gate(x, y, sub, this, 4);
						actors[sub].push_back(g);
						break;
					}
					
					case Level::gate5:
					{
						Gate *g = new Gate(x, y, sub, this, 5);
						actors[sub].push_back(g);
						break;
					}
					
					case Level::exit:
					{
						Exit *e = new Exit(x, y, sub, this);
						ex = e;
						actors[sub].push_back(e);
						break;
					}
					
					case Level::hostage:
					{
						Hostage *h = new Hostage(x, y, sub, this);
						actors[sub].push_back(h);
						break;
					}
					
					case Level::horiz_snarlbot:
					{
						SnarlBot *s = new SnarlBot(x, y, GraphObject::right, sub, this);
						actors[sub].push_back(s);
						break;
					}
					
					case Level::vert_snarlbot:
					{
						SnarlBot *s = new SnarlBot(x, y, GraphObject::up, sub, this);
						actors[sub].push_back(s);
						break;
					}
					
					case Level::ammo:
					{
						AmmoGoodie *a = new AmmoGoodie(x, y, sub, this);
						actors[sub].push_back(a);
						break;
					}
					
					case Level::extra_life:
					{
						ExtraLifeGoodie *e = new ExtraLifeGoodie(x, y, sub, this);
						actors[sub].push_back(e);
						break;
					}
					
					case Level::restore_health:
					{
						RestoreHealthGoodie *r = new RestoreHealthGoodie(x, y, sub, this);
						actors[sub].push_back(r);
						break;
					}
					
					case Level::kleptobot_factory:
					{
						KleptoBotFactory *k = new KleptoBotFactory(x, y, sub, this);
						actors[sub].push_back(k);
						break;
					}
					default:
						break;
				}
			}
		}
		sub++;
		
		ostringstream os_sub;
		os_sub << "_" << sub;
		os_sub << ".dat";
		string curLevel = os_main.str() + os_sub.str();
		
		result = lev.loadLevel(curLevel, sub);
	}
	sub = 0;

    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	setDisplayText();
	for(int i = 0; i < actors[sub].size(); i++)
	{
		if(!actors[sub][i]->isDead())
		{
			actors[sub][i]->doSomething();
			
			if(playa[sub]->isDead())
			{
				decLives();
				return GWSTATUS_PLAYER_DIED;
			}
				
			if(levelComplete)
			{
				increaseScore(1000);
				increaseScore(time);
				levelComplete = false;
				return GWSTATUS_FINISHED_LEVEL;
			}
		}
				
	}
	
	for(int i = 0; i < actors[sub].size(); i++)
	{
		if(actors[sub][i]->isDead())
		{
			delete actors[sub][i];
			actors[sub].erase(actors[sub].begin() + i);
		}
	}
	
	time--;

	// reveals exit if all jewels and hostages have been collected and exit isn't already revealed
	if(exitCanAppear() && !ex->isVisible())
	{
		ex->setVisible(true);
		playSound(6);
	}
	
	if(playa[sub]->isDead() || time <= 0)
	{
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}
	
	if(levelComplete)
	{
		increaseScore(1000);
		increaseScore(time);
		levelComplete = false;
		return GWSTATUS_FINISHED_LEVEL;
	}
	
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
	for(int i = 0; i < actors.size(); i++)
	{
		for(int j = 0; j < actors[i].size(); j++)
			delete actors[i][j];
		actors[i].clear();
	}
	
	playa.clear();
}

int StudentWorld::getCurrentSubLevel()
{
    return sub;
}

bool StudentWorld::isObstacle(int x, int y)
{
	for(int i = 0; i < actors[sub].size(); i++)
		if(actors[sub][i]->getX() == x && actors[sub][i]->getY() == y)
			if(actors[sub][i]->getID() == IID_WALL || actors[sub][i]->getID() == IID_ROBOT_FACTORY || actors[sub][i]->getID() == IID_KLEPTOBOT || actors[sub][i]->getID() == IID_SNARLBOT || actors[sub][i]->getID() == IID_PLAYER)
				return true;
	
	return false;
}

bool StudentWorld::isPlayerLoc(int x, int y)
{
	return playa[sub]->getX() == x && playa[sub]->getY() == y;
}

vector<Actor*> StudentWorld::anyOtherActors(int x, int y)
{
	vector<Actor*> otherActors;
	for(int i = 0; i < actors[sub].size(); i++)
		if(actors[sub][i]->getX() == x && actors[sub][i]->getY() == y)
			otherActors.push_back(actors[sub][i]);
	
	return otherActors;
}

bool StudentWorld::exitCanAppear()
{
	for(int i = 0; i < actors.size(); i++)
		for(int j = 0; j < actors[i].size(); j++)
			if(actors[i][j]->getID() == IID_JEWEL || actors[i][j]->getID() == IID_HOSTAGE)
				return false;
	
	return true;
}

void StudentWorld::setDisplayText()
{
	int score = getScore();
	int level = getLevel(); // (e.g. 03)
	int subLevel = getCurrentSubLevel(); // (e.g. 01. 00 is for main level)
	unsigned int timeLimit = time;
	int livesLeft = getLives();
	
	// Score: 0000100 Level: 03-01 Lives: 3 Health: 70% Ammo: 216 TimeLimit: 34
	string s = statTextFormat(score, level, subLevel, livesLeft, playa[sub]->getHp(), playa[sub]->getAmmo(), timeLimit);
	
	setGameStatText(s);
}

string StudentWorld::statTextFormat(int score, int level, int sublevel, int lives, int hp, int ammo, int time)
{
	ostringstream os;
	os.fill('0');
	os << "Score: " << setw(7) << score;
	os << " Level: " << setw(2) << level << "-" << sublevel;
	
	os.fill(' ');
	os << " Lives: " << setw(2) << lives;
	os << " Health: " << setw(3) << hp << "%";
	os << " Ammo: " << setw(3) << ammo;
	os << " TimeLimit: " << setw(5) << time;
	
	return os.str();
}

void StudentWorld::gotHealthGoodie()
{
	for(int i = 0; i < playa.size(); i++)
		playa[i]->setHp(20);
}

void StudentWorld::gotAmmoGoodie()
{
	for(int i = 0; i < playa.size(); i++)
		playa[i]->incAmmo(25);
}

void StudentWorld::getPlayerLoc(int &x, int &y)
{
	x = playa[sub]->getX();
	y = playa[sub]->getY();
}

bool StudentWorld::clearShot(int x, int y, int px, int py, GraphObject::Direction d)
{
	switch(d)
	{
		case GraphObject::left:
		{
			for(int i = x-1; i > px; i--)
				if (isObstacle(i, y))
					return false;
			return true;
			break;
		}
		
		case GraphObject::right:
		{
			for(int i = x+1; i < px; i++)
				if (isObstacle(i, y))
					return false;
			return true;
			break;
		}
			
		case GraphObject::down:
		{
			for(int i = y-1; i > py; i--)
				if (isObstacle(x, i))
					return false;
			return true;
			break;
		}
		
		case GraphObject::up:
		{
			for(int i = y+1; i < py; i++)
				if (isObstacle(x, i))
					return false;
			return true;
			break;
		}
		
		default:
			break;
	}
	return true;
}

int StudentWorld::numberOfKleptos(int x, int y)
{
	int count = 0;
	
	for(int i = -3; i < 4; i++)
		for(int j = -3; j < 4; j++)
		{
			int r = x + i;
			int c = y + j;
			if(r < 0 || r >= VIEW_WIDTH || c < 0 || c >= VIEW_HEIGHT)
				break;
			
			if(kleptoAt(r, c))
				count++;
		}
	
	return count;
}

bool StudentWorld::kleptoAt(int x, int y)
{
	for(int i = 0; i < actors[sub].size(); i++)
		if(actors[sub][i]->getID() == IID_KLEPTOBOT && actors[sub][i]->getX() == x && actors[sub][i]->getY() == y)
			return true;
	
	return false;
}