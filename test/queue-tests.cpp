#include "../Queue.h"
#include <iostream>

using namespace std;

void testEmpty() {
  Queue q(3);

  bool start = q.empty();
  q.push(1);
  bool after_push = q.empty();
  q.pop();
  bool after_pop = q.empty();

  if (start && !after_push && after_pop) {
    cout << "Pass\n";
  } else {
    cout << "Expected q to be empty at first, not empty after push, empty again after pop but wasn't.\n";
  }
}

void testPushingAndPopping() {
  Queue q(3);
  q.push(1);
  q.push(2);
  q.push(3);
  int one = q.pop();
  int two = q.pop();
  int three = q.pop();

  if (one == 1 && two == 2 && three == 3 && q.empty()) {
    cout << "Pass\n";
  } else {
    cout << "Expected q to push and pop three values but didn't\n";
  }
}

void testWrapping() {
  Queue q(3);
  q.push(1);
  q.push(2);
  q.push(3);
  q.pop();
  q.pop();
  q.pop();
  q.push(4);
  int front = q.pop();
  q.push(5);
  int new_front = q.pop();

  if (front == 4 && new_front == 5) {
    cout << "Pass\n";
  } else {
    cout << "Expected q to correctly return values after wrapping, but didn't\n";
  }
}

int main() {
  testEmpty();
  testPushingAndPopping();
  testWrapping();

  return 0;
}