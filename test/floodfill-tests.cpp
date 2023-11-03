#include "../floodFill.h"
#include <iostream>

using namespace std;

const int M = 2;
const int N = 2;

int testMaze[M * N][4] = {
  {0, 1, 0, 0},
  {0, 0, 0, 0},
  {1, 0, 0, 0},
  {0, 0, 0, 0}
};

void onBoardTest() {
  bool pass = true;

  if (!onBoard(0, 1, 2, 2)) {
    cout << "Square expected to be on board but wasn't\n";
    pass = false;
  }
  if (onBoard(2, 0, 2, 2)) {
    cout << "Square expected to not be on board but was\n";
    pass = false;
  }
  if (onBoard(0, 2, 2, 2)) {
    cout << "Square expected to not be on board but was\n";
    pass = false;
  }

  if (pass) {
    cout << "Pass\n";
  }
}

void convertIndexTest() {
  bool pass = true;

  if (convertIndex(0, 1, 2) != 1) {
    cout << "Did not convert index correctly for first row\n";
    pass = false;
  }
  if (convertIndex(1, 1, 2) != 3) {
    cout << "Did not convert index correctly for row after first\n";
    pass = false;
  }

  if (pass) {
    cout << "Pass\n";
  }
}

void getNeighborTest() {
  bool pass = true; 

  if(getNeighbor(2, 0, 2) != 0) {
    cout << "Did not return north neighbor as expected\n";
    pass = false;
  }
  if (getNeighbor(0, 1, 2) != 2) {
    cout << "Did not return south neighbor as expected\n";
    pass = false;
  }
  if (getNeighbor(0, 2, 2) != 1) {
    cout << "Did not return east neighbor as expected\n";
    pass = false;
  }
  if (getNeighbor(1, 3, 2) != 0) {
    cout << "Did not return west neighbor as expected\n";
    pass = false;
  }

  if (pass) {
    cout << "Pass\n";
  }
}

void getInitialNeighborsTest() {
  bool pass = true;
  int neighbors[M * N][4] = {{0}};

  getInitialNeighbors(M, N, neighbors);
  int expected[M * N][4] = {
    {0, 1, 1, 0},
    {0, 1, 0, 1},
    {1, 0, 1, 0},
    {1, 0, 0, 1}
  };

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (neighbors[i][j] != expected[i][j]) {
        cout << "Did not calculate initial neighbors as expected.\n";
        pass = false;
        break;
      }
    }
  }

  if (pass) {
    cout << "Pass\n";
  }
}

void floodTest() {
  bool pass = true;
  int neighbors[M * N][4] = {{0}};
  int robotMazeKnowledge[M * N]; 

  getInitialNeighbors(M, N, neighbors); // setup

  flood(robotMazeKnowledge, 0, M, N, neighbors);

  int expected[4] = { 0, 1, 1, 2 };

  for (int i = 0; i < 4; i++) {
    if (robotMazeKnowledge[i] != expected[i]) {
      cout << "Did not flood as expected\n";
      pass = false;
      break;
    }
  }

  if (pass) {
    cout << "Pass\n";
  }
}

void updateNeighborsTest() {
  int neighbors[M * N][4] = {{0}};
  getInitialNeighbors(M, N, neighbors); //setup

  updateNeighbors(2, neighbors, testMaze[2], N);

  if (neighbors[2][0] != 0 || neighbors[0][1] != 0) {
    cout << "Did not update neighbors as expected\n";
  } else {
    cout << "Pass\n";
  }
}

void advanceTest() {
  int neighbors[M * N][4] = {{0}};
  int robotMazeKnowledge[M * N]; 

  getInitialNeighbors(M, N, neighbors); 
  updateNeighbors(2, neighbors, testMaze[2], N);
  flood(robotMazeKnowledge, 0, M, N, neighbors); //setup

  int res = advance(2, neighbors, robotMazeKnowledge, N);

  if (res != 3) {
    cout << "Did not choose the next square as expected\n";
  } else {
    cout << "Pass\n";
  }
}

void floodFillTest() {
  bool pass = true;

  int neighbors[M * N][4] = {{0}};
  int robotMazeKnowledge[M * N];

  floodFill(1, 0, 0, 0, M, N, robotMazeKnowledge, neighbors, testMaze);

  int expect[4] = {0, 1, 3, 2};

  for (int i = 0; i < 4; i++) {
    if (robotMazeKnowledge[i] != expect[i]) {
      cout << "Flood fill did not work as expected\n";
      pass = false;
      break;
    }
  }

  if (pass) {
    cout << "Pass\n";
  }
}

int main() {
  onBoardTest();
  convertIndexTest();
  getNeighborTest();
  getInitialNeighborsTest();
  floodTest();
  updateNeighborsTest();
  advanceTest();
  floodFillTest();

  return 0;
}