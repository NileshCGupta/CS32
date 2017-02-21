//
//  History.cpp
//  Project1
//
//  Created by Nilesh Gupta on 6/27/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include <iostream>
#include "History.h"
using namespace std;

History::History(int nRows, int nCols)
{
    rows = nRows;
    columns = nCols;
    rounds = 0;
}

bool History::record(int r, int c)
{
    if(r > MAXROWS || r <= 0 || c > MAXCOLS || c <= 0)
        return false;
    xHistory[rounds] = r;
    yHistory[rounds] = c;
    rounds++;
    return true;
}
void History::display() const
{
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows; r++)
        for (c = 0; c < columns; c++)
            grid[r][c] = '.';
    
    // Fill grid with history
    for(int i = 0; i < rounds; i++)
    {
        char& gridChar = grid[xHistory[i]-1][yHistory[i]-1];
        switch(gridChar)
        {
            case '.':  gridChar = 'A'; break;
            case 'Z':  gridChar = 'Z'; break;
            default:   gridChar++; break;  // 'A' through 'Y'

        }

    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows; r++)
    {
        for (c = 0; c < columns; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
}