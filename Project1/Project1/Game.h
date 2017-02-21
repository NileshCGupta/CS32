//
//  Game.h
//  Project1
//
//  Created by Nilesh Gupta on 6/27/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#ifndef __Project1__Game__
#define __Project1__Game__

#include <stdio.h>

class Pit;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nSnakes);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Pit* m_pit;
};

#endif /* defined(__Project1__Game__) */