//
//  Pit.h
//  Project1
//
//  Created by Nilesh Gupta on 6/27/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//


#ifndef __Project1__Pit__
#define __Project1__Pit__

#include <string>
#include "History.h"
#include "globals.h"

class Snake;
class Player;

class Pit
{
public:
    // Constructor/destructor
    Pit(int nRows, int nCols);
    ~Pit();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     snakeCount() const;
    int     numberOfSnakesAt(int r, int c) const;
    void    display(std::string msg) const;
    
    // Mutators
    bool   addSnake(int r, int c);
    bool   addPlayer(int r, int c);
    bool   destroyOneSnake(int r, int c);
    bool   moveSnakes();
    History& history();
    
private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Snake*  m_snakes[MAXSNAKES];
    History m_history;
    int     m_nSnakes;
};

#endif /* defined(__Project1__Pit__) */
