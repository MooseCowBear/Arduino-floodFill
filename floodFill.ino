#include "FloodFill.h"

void setup() {
  Serial.begin(9600);
}

bool cont = true;

void loop() {
  if (cont) {
    const int M = 6;
    const int N = 4;
    int neighbors[M * N][4] = {{0}};
    int robotMazeKnowledge[M * N]; 

    int testMaze[M * N][4] = {
      {0, 1, 0, 0}, //0
      {0, 1, 0, 0}, //1
      {0, 1, 0, 0}, //2
      {0, 0, 0, 0}, //3
      {1, 0, 0, 0}, //4
      {1, 1, 0, 0}, //5
      {1, 0, 1, 0}, //6
      {0, 0, 0, 1}, //7
      {0, 0, 1, 0}, //8
      {1, 0, 1, 1}, //9
      {0, 1, 1, 1}, //10
      {0, 0, 0, 1}, //11
      {0, 1, 0, 0}, //12
      {0, 0, 0, 0}, //13
      {1, 1, 0, 0}, //14
      {0, 0, 0, 0}, //15
      {1, 0, 1, 0}, //16
      {0, 1, 0, 1}, //17
      {1, 1, 1, 0}, //18
      {0, 0, 0, 1}, //19
      {0, 0, 0, 0}, //20
      {1, 0, 0, 0}, //21
      {1, 0, 0, 0}, //22
      {0, 0, 0, 0} //23
    };

    floodFill(5, 0, 2, 2, M, N, robotMazeKnowledge, neighbors, testMaze);
    cont = false;

    printMaze(robotMazeKnowledge, M, N);
  }
}

void printMaze(int arr[], int m, int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      Serial.print(arr[convertIndex(i, j, n)]);
      Serial.print(", ");
    }
    Serial.print("\n");
  }
  Serial.print("\n");
}