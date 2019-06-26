//A header file for the Heap class. For detailed descriptions on variables and functions see Heap.cpp.
#ifndef HEAP_HPP
#define HEAP_HPP
#include "Ball.hpp"
#include <vector>
#include <string>

using namespace std;

class Heap
{
  private:
    vector<Ball *> array;
    int currentHeapSize;
    unsigned long long currentScore;
    string heapType;

  public:
    Heap(string inputType);
    int GetParentIndex(int inputIndex);
    int GetLeftChild(int inputIndex);
    int GetRightChild(int inputIndex);
    string GetHeapType();
    void InsertNode(Ball *ball);
    Ball* RemoveMaxNode();
    void Heapify(int inputIndex);
    void Print();
    void UpdateScore(unsigned long long input);
    unsigned long long GetScore();
};
#endif