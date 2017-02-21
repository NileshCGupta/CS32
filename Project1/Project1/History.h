//
//  History.h
//  Project1
//
//  Created by Nilesh Gupta on 6/27/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#ifndef __Project1__History__
#define __Project1__History__

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int rows, columns;
    int rounds;
    int xHistory[MAXSNAKES];
    int yHistory[MAXSNAKES];
};

#endif /* defined(__Project1__History__) */
