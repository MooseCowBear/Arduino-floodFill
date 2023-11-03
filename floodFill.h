/*
  input maze is an m x n matrix. 
  all uses of m, n below refer to the number of maze rows, cols respectively.
  assumes destination sqaure is reachable from source square.
*/

#ifndef FLOOD_FILL_H
#define FLOOD_FILL_H

#include "Queue.h"
#include <limits.h>

bool onBoard(int i, int j, int m, int n) {
  return 0 <= i && i < m && 0 <= j && j < n;
}

int convertIndex(int rowIndex, int colIndex, int n) {
  // helper function to convert from maze squares 2d to 1d 
  return rowIndex * n + colIndex;
}

int getNeighbor(int sq, int neighborIndex, int n) {
  // helper function to return the N, S, E, W neighbor's indices
  switch(neighborIndex) {
    case 0:
      return sq - n;
    case 1:
      return sq + n;
    case 2:
      return sq + 1;
    default:
      return sq - 1;
  }
}

void getInitialNeighbors(int m, int n, int neighbors[][4]) {
  /* records the edges of the maze */
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      int sq = convertIndex(i, j, n);
      if (onBoard(i - 1, j, m, n)) {
        neighbors[sq][0] = 1; //north 
      }
      if (onBoard(i + 1, j, m, n)) {
        neighbors[sq][1] = 1; //south
      }
      if (onBoard(i, j + 1, m, n)) { 
        neighbors[sq][2] = 1; //east
      }
      if (onBoard(i, j - 1, m, n)) {
        neighbors[sq][3] = 1; //west
      }
    }
  }
}

void flood(int maze[], int dest, int m, int n, int neighbors[][4]) {
  /* the flood procedure rewrites robot's maze knowledge.
  -1 indicates an unvisited square, a value > -1 indicates the square's min manhattan
  distance from the target destination
  */
  for (int i = 0; i < m * n; i++) {
    maze[i] = -1;
  }
  Queue q(m * n);
  maze[dest] = 0;
  q.push(dest);
  
  while (!q.empty()) {
    int curr = q.pop();
    for (int i = 0; i < 4; i++) {
      if (neighbors[curr][i] == 1 && maze[getNeighbor(curr, i, n)] == -1) { 
        maze[getNeighbor(curr, i, n)] = maze[curr] + 1;
        q.push(getNeighbor(curr, i, n));
      }
    }
  }
}

int advance(int curr, int neighbors[][4], int maze[], int n) { 
  /* finding the next square to move to means checking current square's 
  neighbors for the one with the smallest distance */
  int minSq;
  int minVal = INT_MAX;
  for (int i = 0; i < 4; i++) {
    if (neighbors[curr][i] == 0) {
      continue;
    }
    if (maze[getNeighbor(curr, i, n)] < minVal) {
      minSq = getNeighbor(curr, i, n);
      minVal = maze[getNeighbor(curr, i, n)];
    }
  }
  return minSq;
}

void updateNeighbors(int sq, int neighbors[][4], int walls[4], int n) {
  /* walls here is a length 4 arr indicating the north, south, east, west walls for curr sq.
  these will be the walls that the robot "sees" from its current position.
  bc neighborness is symmetric, update both sides of the relation */
  for (int i = 0; i < 4; i++) {
    if (walls[i] == 1) {
      neighbors[sq][i] = 0;
      neighbors[getNeighbor(sq, i, n)][(i == 0 || i == 2) ? i + 1 : i - 1] = 0; 
    }
  }
}

void getWallsForSquare(int sq, int walls[4], int mazeStandIn[][4]) {
  /* returns wall info for square from input maze.
  for actual robot, this will be replaced by info from sensors
  */
  for (int i = 0; i < 4; i++) {
    walls[i] = mazeStandIn[sq][i];
  }
}

void floodFill(int startRow, int startCol, int destRow, int destCol, const int m, const int n, int robotMazeKnowledge[], int neighbors[][4], int mazeStandIn[][4]) {
  getInitialNeighbors(m, n, neighbors);

  int start = convertIndex(startRow, startCol, n);
  int dest = convertIndex(destRow, destCol, n);
  
  int curr = start;
  int walls[4] = {0};
  
  while (curr != dest) {
    getWallsForSquare(curr, walls, mazeStandIn); // will need replace this function, remove mazeStandIn param from above
    updateNeighbors(curr, neighbors, walls, n);
    flood(robotMazeKnowledge, dest, m, n, neighbors);
    curr = advance(curr, neighbors, robotMazeKnowledge, n);
  }
  // the robot can now traverse the maze from start to destination by choosing the neighbor with the lowest value
}

#endif