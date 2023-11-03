/* a minimal queue that implements only the behavior needed for flood fill. 
  Note: no overflow or underflow checks.
*/

#ifndef QUEUE_H
#define QUEUE_H

class Queue {
  private:
    int _front, _back, _size;
    int *_data;
  public:
    Queue(int size = 256) { 
      _front = 0;
      _back = 0;
      _size = size;
      _data = new int[size];   
    }
    ~Queue() {
      delete[] _data;
    }
    void push(int elem);
    int pop();
    bool empty();
};

void Queue::push(int elem) {
  _data[_back] = elem;
  _back++;
  if (_back >= _size) {
    _back = _back % _size;
  }
}

int Queue::pop() {
  int elem = _data[_front];
  _front++;
  if (_front >= _size) {
    _front = _front % _size;
  }
  return elem;
}

bool Queue::empty() {
  return _back == _front;
}

#endif