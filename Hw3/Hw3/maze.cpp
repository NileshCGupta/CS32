//
//  maze.cpp
//  Hw3
//
//  Created by Nilesh Gupta on 7/27/15.
//  Copyright (c) 2015 Nilesh Gupta. All rights reserved.
//

//If the start location is equal to the ending location, then we've
//solved the maze, so return true.
//Mark the start location as visted.
//For each of the four directions,
//If the location one step in that direction (from the start
//											location) is unvisited,
//then call pathExists starting from that location (and
//												  ending at the same ending location as in the
//												  current call).
//If that returned true,
//then return true.
//Return false.

#include <string>

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

bool pathExists(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	if(sr == er && sc == ec)
		return true;
	
	maze[sr][sc] = '$';
	
	if(maze[sr-1][sc] == '.')
		if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
			return true;
	if(maze[sr+1][sc] == '.')
		if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
			return true;
	if(maze[sr][sc-1] == '.')
		if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
			return true;
	if(maze[sr][sc+1] == '.')
		if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
			return true;
	
	return false;

}