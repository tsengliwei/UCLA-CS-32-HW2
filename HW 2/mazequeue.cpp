//
//  mazequeue.cpp
//  HW 2
//
//  Created by Li-Wei Tseng on 4/26/14.
//  Copyright (c) 2014 Li-Wei Tseng. All rights reserved.
//

#define QUEUE
#ifdef QUEUE


#include <iostream>
#include <queue>
#include <cassert>
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


bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise
    
    queue<Coord> coordQueue; // declare a queue of Coords
    
    //Push the starting coordinate (sr,sc) onto the coordinate queue and
    //update maze[sr][sc] to indicate that the algorithm has encountered
    //it (i.e., set maze[sr][sc] to have a value other than '.').
    
    Coord startPoint(sr, sc);
    coordQueue.push(startPoint);
    maze[sr][sc] = '#';
    
    while(!coordQueue.empty()) //While the queue is not empty
    {
        //Pop the top coordinate off the queue. This gives you the current
        //(r,c) location that your algorithm is exploring.
        Coord cur = coordQueue.front();
        //cerr << '(' << cur.r() << ',' << cur.c() << ')'<< endl;
        
        coordQueue.pop();
        
        if(cur.r() == er && cur.c() == ec)//If the current (r,c) coordinate is equal to the ending coordinate,
            return true;    //then we've solved the maze so return true!
        
        //Check each place you can move from the current cell:
        if(maze[cur.r()-1][cur.c()] == '.') //try to move NORTH
        {
            Coord curPoint(cur.r()-1, cur.c());
            coordQueue.push(curPoint);
            maze[cur.r()-1][cur.c()] = '#'; //update maze[r-1][c] to indicate the algorithm has encountered it.
        }
        if(maze[cur.r()][cur.c()+1] == '.') //try to move EAST
        {
            Coord curPoint(cur.r(), cur.c()+1);
            coordQueue.push(curPoint);
            maze[cur.r()][cur.c()+1] = '#'; //update maze[r][c+1] to indicate the algorithm has encountered it.
        }
        if(maze[cur.r()+1][cur.c()] == '.') //try to move SOUTH
        {
            Coord curPoint(cur.r()+1, cur.c());
            coordQueue.push(curPoint);
            maze[cur.r()+1][cur.c()] = '#'; //update maze[r+1][c] to indicate the algorithm has encountered it.
        }
        if(maze[cur.r()][cur.c()-1] == '.') //try to move WEST
        {
            Coord curPoint(cur.r(), cur.c()-1);
            coordQueue.push(curPoint);
            maze[cur.r()][cur.c()-1] = '#'; //update maze[r][c-1] to indicate the algorithm has encountered it.
        }
        
    }
    return false;
}

int main(int argc, const char * argv[])
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','.','.','.','.','.','.','.','X'},
        { 'X','X','.','X','.','X','X','X','X','X'},
        { 'X','.','.','X','.','X','.','.','.','X'},
        { 'X','.','.','X','.','.','.','X','.','X'},
        { 'X','X','X','X','.','X','X','X','.','X'},
        { 'X','.','.','X','.','.','.','X','X','X'},
        { 'X','.','.','X','X','.','X','X','.','X'},
        { 'X','.','.','.','X','.','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
    
    assert(pathExists(maze, 6,4, 1,1));
    char maze1[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','X','.','.','X','.','.','.','X'},
        { 'X','.','X','X','.','X','.','X','X','X'},
        { 'X','.','.','.','.','X','.','X','.','X'},
        { 'X','X','.','X','.','X','.','.','.','X'},
        { 'X','X','X','.','.','X','.','X','.','X'},
        { 'X','.','.','.','X','.','.','.','X','X'},
        { 'X','.','X','X','.','.','X','.','X','X'},
        { 'X','.','.','.','.','X','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
    assert(pathExists(maze1, 8, 6, 1, 1));
    char maze2[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','.','X','.','.','X','.','.','.','X'},
        { 'X','X','X','X','.','X','.','X','X','X'},
        { 'X','.','.','.','.','X','.','X','.','X'},
        { 'X','X','.','X','.','X','.','.','.','X'},
        { 'X','X','X','.','.','X','.','X','.','X'},
        { 'X','.','.','.','X','.','.','.','X','X'},
        { 'X','.','X','X','.','.','X','.','X','X'},
        { 'X','.','.','.','.','X','.','.','.','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
        
    };
    assert(!pathExists(maze2, 8, 6, 1, 1));
    char maze3[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','X','.','.','.','.','.','X','X','X'},
        { 'X','.','.','X','X','.','.','.','.','X'},
        { 'X','.','.','.','X','.','.','.','X','X'},
        { 'X','.','X','.','X','X','X','.','.','X'},
        { 'X','X','X','X','.','.','X','.','.','X'},
        { 'X','X','.','.','.','.','X','.','.','X'},
        { 'X','.','.','.','.','.','.','.','X','X'},
        { 'X','.','.','X','X','X','X','X','X','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
        
    };
    assert(pathExists(maze3, 4, 3, 7, 1));
    char maze4[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X'},
        { 'X','X','.','.','.','.','.','X','X','X'},
        { 'X','.','.','X','X','.','.','.','.','X'},
        { 'X','.','.','.','X','.','.','.','X','X'},
        { 'X','.','X','.','X','X','X','.','.','X'},
        { 'X','X','X','X','.','.','X','.','.','X'},
        { 'X','X','.','.','.','.','X','.','.','X'},
        { 'X','.','X','.','.','.','.','.','X','X'},
        { 'X','.','.','X','X','X','X','X','X','X'},
        { 'X','X','X','X','X','X','X','X','X','X'}
    };
    assert(!pathExists(maze4, 4, 3, 7, 1));
    cerr << "pass all test!" << endl;
}

#endif
