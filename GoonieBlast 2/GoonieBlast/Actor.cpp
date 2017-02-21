#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

void Player::doSomething()
{
	if(isDead())
		return;
	int ch;
	if(getWorld()->getKey(ch))
	{
		// user hit a key
		switch(ch)
		{
			case KEY_PRESS_LEFT:
				if(getWorld()->isObstacle(getX() - 1, getY()))
					break;
				moveTo(getX() - 1, getY());
				setDirection(left);
				break;
				
			case KEY_PRESS_RIGHT:
				if(getWorld()->isObstacle(getX() + 1, getY()))
					break;
				moveTo(getX() + 1, getY());
				setDirection(right);
				break;
				
			case KEY_PRESS_UP:
				if(getWorld()->isObstacle(getX(), getY() + 1))
					break;
				moveTo(getX(), getY() + 1);
				setDirection(up);
				break;
				
			case KEY_PRESS_DOWN:
				if(getWorld()->isObstacle(getX(), getY() - 1))
					break;
				moveTo(getX(), getY() - 1);
				setDirection(down);
				break;
				
			case KEY_PRESS_SPACE:
				// add new bullet in square in front of player
				if(ammo != 0)
				{
					Direction dir = getDirection();
					switch(dir)
					{
						case up:
						{
							Bullet *bill = new Bullet(getX(), getY() + 1, dir, getWorld()->getCurrentSubLevel(), getWorld());
							getWorld()->addActor(bill, getWorld()->getCurrentSubLevel());
							break;
						}
						case down:
						{
							Bullet *bill = new Bullet(getX(), getY() - 1, dir, getWorld()->getCurrentSubLevel(), getWorld());
							getWorld()->addActor(bill, getWorld()->getCurrentSubLevel());
							break;
						}
						case left:
						{
							Bullet *bill = new Bullet(getX() - 1, getY(), dir, getWorld()->getCurrentSubLevel(), getWorld());
							getWorld()->addActor(bill, getWorld()->getCurrentSubLevel());
							break;
						}
						case right:
						{
							Bullet *bill = new Bullet(getX() + 1, getY(), dir, getWorld()->getCurrentSubLevel(), getWorld());
							getWorld()->addActor(bill, getWorld()->getCurrentSubLevel());
							break;
						}
						default:
							break;
					}
					getWorld()->playSound(4);
					ammo--;
				}
				break;
				
			case KEY_PRESS_ESCAPE:
				hp = 0;
				break;
			
		}
	}
}

void Player::damage()
{
	hp -= 3;
	if(hp <= 0)
	{
		hp = 0;
		getWorld()->playSound(2);
	}
	getWorld()->playSound(10);
}
void Bullet::doSomething()
{
	if(isDead())
		return;
	
	vector<Actor*> sameSquare = getWorld()->anyOtherActors(getX(), getY());
	if(sameSquare.size() != 1)
		for(int i = 0; i < sameSquare.size(); i++)
		{
		// checks if other actors on the same square can be damaged
			if(sameSquare[i]->getID() == IID_PLAYER || sameSquare[i]->getID() == IID_KLEPTOBOT || sameSquare[i]->getID() == IID_SNARLBOT)
			{
				sameSquare[i]->damage();
				hp = 0;
				return;
			}
			if(sameSquare[i]->getID() == IID_WALL || sameSquare[i]->getID() == IID_ROBOT_FACTORY)
			{
				hp = 0;
				return;
			}
		}
	
	// if there are no interactable actors in its square then it moves in its current direction
	Direction dir = getDirection();
	switch(dir)
	{
		case up:
			moveTo(getX(), getY() + 1);
			break;
		case down:
			moveTo(getX(), getY() - 1);
			break;
		case left:
			moveTo(getX() - 1, getY());
			break;
		case right:
			moveTo(getX() + 1, getY());
			break;
		default:
			break;
	}
	
	// checks if there are any interactable actors in its new square
	sameSquare = getWorld()->anyOtherActors(getX(), getY());
	if(sameSquare.size() != 1)
		for(int i = 0; i < sameSquare.size(); i++)
		{
			// checks if other actors on the same square can be damaged
			if(sameSquare[i]->getID() == IID_PLAYER || sameSquare[i]->getID() == IID_KLEPTOBOT || sameSquare[i]->getID() == IID_SNARLBOT)
			{
				sameSquare[i]->damage();
				hp = 0;
				return;
			}
			if(sameSquare[i]->getID() == IID_WALL || sameSquare[i]->getID() == IID_ROBOT_FACTORY)
			{
				hp = 0;
				return;
			}
		}
}

void Gate::doSomething()
{
	if(isDead())
		return;
	
	if(getWorld()->isPlayerLoc(getX(), getY()))
	{
		hp = 0;
		getWorld()->transport(gateNum);
	}
}

void Jewel::doSomething()
{
	if(isDead())
		return;
	
	if(getWorld()->isPlayerLoc(getX(), getY()))
	{
		getWorld()->increaseScore(100);
		hp = 0;
		getWorld()->playSound(5);
	}
}

void Hostage::doSomething()
{
	if(isDead())
		return;
	
	if(getWorld()->isPlayerLoc(getX(), getY()))
	{
		hp = 0;
		getWorld()->playSound(5);
	}
}

void Exit::doSomething()
{
	if(getWorld()->isPlayerLoc(getX(), getY()) && isVisible())
	{
		getWorld()->playSound(7);
		getWorld()->levelCompleted(true);
	}
}

void ExtraLifeGoodie::doSomething()
{
	if(isDead())
		return;
	
	if(getWorld()->isPlayerLoc(getX(), getY()) && isVisible())
	{
		getWorld()->increaseScore(500);
		hp = 0;
		getWorld()->playSound(5);
		getWorld()->incLives();
	}
}

void RestoreHealthGoodie::doSomething()
{
	if(isDead())
		return;
	
	if(getWorld()->isPlayerLoc(getX(), getY()) && isVisible())
	{
		getWorld()->increaseScore(1000);
		hp = 0;
		getWorld()->playSound(5);
		getWorld()->gotHealthGoodie();
	}
}

void AmmoGoodie::doSomething()
{
	if(isDead())
		return;
	
	if(getWorld()->isPlayerLoc(getX(), getY()) && isVisible())
	{
		getWorld()->increaseScore(200);
		hp = 0;
		getWorld()->playSound(5);
		getWorld()->gotAmmoGoodie();
	}
}

void SnarlBot::doSomething()
{
	if(isDead())
		return;
	
	ticksCount++;
	if(ticksCount % ticks != 0)
		return;
	
	int x, y;
	getWorld()->getPlayerLoc(x, y);
	
	Direction dir = getDirection();
	// checks if player is in line of fire and if there are no obstructions
	if((dir == left && getY() == y && x < getX() && getWorld()->clearShot(getX(), getY(), x, y, dir))	||
	   (dir == right && getY() == y && x > getX() && getWorld()->clearShot(getX(), getY(), x, y, dir))	||
	   (dir == up && getX() == x && y > getY() && getWorld()->clearShot(getX(), getY(), x, y, dir))		||
	   (dir == down && getX() == x && y < getY() && getWorld()->clearShot(getX(), getY(), x, y, dir)))
	{
		switch(dir)
		{
			case up:
			{
				Bullet *bill = new Bullet(getX(), getY() + 1, dir, getWorld()->getCurrentSubLevel(), getWorld());
				getWorld()->addActor(bill, getWorld()->getCurrentSubLevel());
				break;
			}
			case down:
			{
				Bullet *bill = new Bullet(getX(), getY() - 1, dir, getWorld()->getCurrentSubLevel(), getWorld());
				getWorld()->addActor(bill, getWorld()->getCurrentSubLevel());
				break;
			}
			case left:
			{
				Bullet *bill = new Bullet(getX() - 1, getY(), dir, getWorld()->getCurrentSubLevel(), getWorld());
				getWorld()->addActor(bill, getWorld()->getCurrentSubLevel());
				break;
			}
			case right:
			{
				Bullet *bill = new Bullet(getX() + 1, getY(), dir, getWorld()->getCurrentSubLevel(), getWorld());
				getWorld()->addActor(bill, getWorld()->getCurrentSubLevel());
				break;
			}
			default:
				break;
		}
		getWorld()->playSound(3);
		return;
	}
	
	if(dir == left)
	{
		if(getWorld()->isObstacle(getX() - 1, getY()))
			setDirection(right);
		else
			moveTo(getX() - 1, getY());
		return;
	}
	
	if(dir == right)
	{
		if(getWorld()->isObstacle(getX() + 1, getY()))
			setDirection(left);
		else
			moveTo(getX() + 1, getY());
		return;
	}
	if(dir == up)
	{
		if(getWorld()->isObstacle(getX(), getY() + 1))
			setDirection(down);
		else
			moveTo(getX(), getY() + 1);
		return;
	}
	if(dir == down)
	{
		if(getWorld()->isObstacle(getX(), getY() - 1))
			setDirection(up);
		else
			moveTo(getX(), getY() - 1);
		return;
	}
}

void SnarlBot::damage()
{
	hp -= 2;
	
	if(!(hp <= 0))
		getWorld()->playSound(9);
	else
	{
		hp = 0;
		getWorld()->playSound(1);
		getWorld()->increaseScore(200);
	}
}

void KleptoBot::doSomething()
{
	if(isDead())
		return;
	
	ticksCount++;
	if(ticksCount % ticks != 0)
		return;
	
	vector<Actor*> actorsSharingSquare = getWorld()->anyOtherActors(getX(), getY());
	for(int i = 0; i < actorsSharingSquare.size(); i++)
	{
		// checks for goodies, if Klepto hasn't picked up a goodie, and makes sure it's a 20% chance
		if((actorsSharingSquare[i]->getID() == IID_EXTRA_LIFE || actorsSharingSquare[i]->getID() == IID_RESTORE_HEALTH || actorsSharingSquare[i]->getID() == IID_AMMO) && goodieID == 0 && rand() % 5 + 1 == 1)
		{
			goodieID = actorsSharingSquare[i]->getID();
			actorsSharingSquare[i]->damage();
			getWorld()->playSound(11);
			return;
		}
	}
	
	Direction dir = getDirection();
	if(distanceMoved < distanceBeforeTurning)
	{
		if(dir == left)
		{
			if(!(getWorld()->isObstacle(getX() - 1, getY())))
			{
				moveTo(getX() - 1, getY());
				distanceMoved++;
				return;
			}
		}
		if(dir == right)
		{
			if(!(getWorld()->isObstacle(getX() + 1, getY())))
			{
				moveTo(getX() + 1, getY());
				distanceMoved++;
				return;
			}
		}
		if(dir == up)
		{
			if(!(getWorld()->isObstacle(getX(), getY() + 1)))
			{
				moveTo(getX(), getY() + 1);
				distanceMoved++;
				return;
			}
		}
		if(dir == down)
		{
			if(!(getWorld()->isObstacle(getX(), getY() - 1)))
			{
				moveTo(getX(), getY() - 1);
				distanceMoved++;
				return;
			}
		}
	}
	
	distanceMoved = 0;
	distanceBeforeTurning = rand() % 3 + 1;
	
	int random = rand() % 4 + 1;
	Direction rand;
	
	switch(random)
	{
		case 1: rand = left;	break;
		case 2: rand = right;	break;
		case 3: rand = up;		break;
		case 4: rand = down;	break;
		default:				break;
	}
	
	Direction randDir = rand;
	
	for(int i = 0; i < 4; i++)
	{
		switch(randDir)
		{
			case left:
				if(!(getWorld()->isObstacle(getX() - 1, getY())))
				{
					setDirection(randDir);
					moveTo(getX() - 1, getY());
					distanceMoved++;
					return;
				}
				break;
			
			case right:
				if(!(getWorld()->isObstacle(getX() + 1, getY())))
				{
					setDirection(randDir);
					moveTo(getX() + 1, getY());
					distanceMoved++;
					return;
				}
				break;
				
			case up:
				if(!(getWorld()->isObstacle(getX(), getY() + 1)))
				{
					setDirection(randDir);
					moveTo(getX(), getY() + 1);
					distanceMoved++;
					return;
				}
				break;
				
			case down:
				if(!(getWorld()->isObstacle(getX(), getY() - 1)))
				{
					setDirection(randDir);
					moveTo(getX(), getY() - 1);
					distanceMoved++;
					return;
				}
				break;
				
			default:
				break;
		}
		
		if(randDir == left)
			randDir = right;
		else if(randDir == right)
			randDir = up;
		else if(randDir == up)
			randDir = down;
		else if(randDir == down)
			randDir = left;
	}
	setDirection(rand);
}

void KleptoBot::damage()
{
	hp -= 2;
	
	if(!(hp <= 0))
	{
		getWorld()->playSound(9);
		return;
	}
	hp = 0;
	getWorld()->playSound(1);
	getWorld()->increaseScore(20);

	if(goodieID != 0)
	{
		switch(goodieID)
		{
			case IID_AMMO:
			{
				AmmoGoodie *a = new AmmoGoodie(getX(), getY(), getWorld()->getCurrentSubLevel(), getWorld());
				getWorld()->addActor(a, getWorld()->getCurrentSubLevel());
				break;
			}
				
			case IID_RESTORE_HEALTH:
			{
				RestoreHealthGoodie *a = new RestoreHealthGoodie(getX(), getY(), getWorld()->getCurrentSubLevel(), getWorld());
				getWorld()->addActor(a, getWorld()->getCurrentSubLevel());
				break;
			}
				
			case IID_EXTRA_LIFE:
			{
				ExtraLifeGoodie *a = new ExtraLifeGoodie(getX(), getY(), getWorld()->getCurrentSubLevel(), getWorld());
				getWorld()->addActor(a, getWorld()->getCurrentSubLevel());
				break;
			}
			
			default:
				break;
		}
	}
}

void KleptoBotFactory::doSomething()
{
	// checks if # of kleptos is less than 3, there is no klepto already on its square, and the 1 in 50 condition
	if(getWorld()->numberOfKleptos(getX(), getY()) < 3 && !getWorld()->kleptoAt(getX(), getY()) && rand() % 50 + 1 == 1)
	{
		KleptoBot *k = new KleptoBot(getX(), getY(), getWorld()->getCurrentSubLevel(), getWorld());
		getWorld()->addActor(k, getWorld()->getCurrentSubLevel());
		getWorld()->playSound(8);
	}
}
