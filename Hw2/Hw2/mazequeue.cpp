//
//  mazequeue.cpp
//  Hw2
//
//  Created by Nilesh Gupta on 7/9/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

#include <queue>
#include <iostream>
#include <string>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr,sc));
    
    maze[sr][sc] = '$';
    
    while(!coordQueue.empty())
    {
        Coord current = coordQueue.front();
        coordQueue.pop();
        
        if(current.r() == er && current.c() == ec)
            return true;
        if(maze[current.r()-1][current.c()] == '.')
        {
            coordQueue.push(Coord(current.r()-1, current.c()));
            maze[current.r()-1][current.c()] = '$';
        }
        if(maze[current.r()][current.c()+1] == '.')
        {
            coordQueue.push(Coord(current.r(), current.c()+1));
            maze[current.r()][current.c()+1] = '$';
        }
        if(maze[current.r()+1][current.c()] == '.')
        {
            coordQueue.push(Coord(current.r()+1, current.c()));
            maze[current.r()+1][current.c()] = '$';
        }
        if(maze[current.r()][current.c()-1] == '.')
        {
            coordQueue.push(Coord(current.r(), current.c()-1));
            maze[current.r()][current.c()-1] = '$';
        }
    }
    return false;
}

