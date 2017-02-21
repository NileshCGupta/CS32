//
//  Snake.h
//  Project1
//
//  Created by Nilesh Gupta on 6/27/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#ifndef __Project1__Snake__
#define __Project1__Snake__

class Pit;  // This is needed to let the compiler know that Pit is a
// type name, since it's mentioned in the Snake declaration.

class Snake
{
public:
    // Constructor
    Snake(Pit* pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    
private:
    Pit* m_pit;
    int  m_row;
    int  m_col;
};

#endif /* defined(__Project1__Snake__) */
