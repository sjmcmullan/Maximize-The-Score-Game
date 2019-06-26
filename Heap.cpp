#include "Heap.hpp"
#include "Ball.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
//Constructor.
Heap::Heap(string inputType)
{
    //This is the amount of nodes in the heap at any given time.
    this->currentHeapSize = 0;
    //The final score for the current object in each game.
    this->currentScore = 0;
    //A vector of vectors to hold the values of each node in the heap.
    //Each node is in the form <value, sumOfDigits>.
    this->array = vector<Ball *>();
    //This enables us to do different actions based on what type of heap it is.
    //Will either be a RUSTY heap or a SCOTT heap.
    this->heapType = inputType;
}

int Heap::GetParentIndex(int inputIndex)
{
    return ((inputIndex - 1) / 2);
}

int Heap::GetLeftChild(int inputIndex)
{
    return ((2 * inputIndex) + 1);
}

int Heap::GetRightChild(int inputIndex)
{
    return ((2 * inputIndex) + 2);
}

string Heap::GetHeapType()
{
    return this->heapType;
}

void Heap::InsertNode(Ball *ball)
{
    // Add the new node to the heap and increase the heap size conter.
    this->array.push_back(ball);
    this->currentHeapSize++;
    int currentNodeIndex = this->currentHeapSize - 1;
    // If this is Rusty.
    if (this->heapType == "RUSTY")
    {   
        // Get the sum of digits of the parent and of the current node.
        int parentSumOfDigits = this->array[this->GetParentIndex(currentNodeIndex)]->GetSumOfDigits();
        int currentSumOfDigits = this->array[currentNodeIndex]->GetSumOfDigits();
        // While we're not at the root and we can swap with the parent.
        while (currentNodeIndex != 0 && parentSumOfDigits <= currentSumOfDigits)
        {
           // If the parent has an equal sumOfDigits...
            if (parentSumOfDigits == currentSumOfDigits)
            {
                int parentValue = this->array[this->GetParentIndex(currentNodeIndex)]->GetValue();
                int currentValue = this->array[currentNodeIndex]->GetValue();
                // ...but the parent has a raw value less than the current node.
                if (parentValue < currentValue)
                {
                    // Swap the parent and the current node.
                    Ball *tmp;
                    tmp = this->array[currentNodeIndex];
                    this->array[currentNodeIndex] = this->array[this->GetParentIndex(currentNodeIndex)];
                    this->array[this->GetParentIndex(currentNodeIndex)] = tmp;
                    // Update these variables for the next run.
                    currentNodeIndex = this->GetParentIndex(currentNodeIndex);
                    parentSumOfDigits = this->array[this->GetParentIndex(currentNodeIndex)]->GetSumOfDigits();
                    currentSumOfDigits = this->array[currentNodeIndex]->GetSumOfDigits();
                }
                // ... but if the above case is false, break and continue.
                else 
                {
                    break;
                }
            }
            // However, if the parent just straight up has a sumOfDigits than the current node.
            else if (parentSumOfDigits < currentSumOfDigits)
            {
                // Swap the parent and the current node.
                Ball *tmp;
                tmp = this->array[currentNodeIndex];
                this->array[currentNodeIndex] = this->array[this->GetParentIndex(currentNodeIndex)];
                this->array[this->GetParentIndex(currentNodeIndex)] = tmp;
                // Update these variables for the next run.
                currentNodeIndex = this->GetParentIndex(currentNodeIndex);
                parentSumOfDigits = this->array[this->GetParentIndex(currentNodeIndex)]->GetSumOfDigits();
                currentSumOfDigits = this->array[currentNodeIndex]->GetSumOfDigits();
            }
        }
    }
    // Else this is a Scott-type heap.
    else
    {
        int parentSumOfDigits = this->array[this->GetParentIndex(currentNodeIndex)]->GetValue();
        int currentSumOfDigits = this->array[currentNodeIndex]->GetValue();
        // If the current node is not the root and we can swap it with it's parent.
        while (currentNodeIndex != 0 && parentSumOfDigits < currentSumOfDigits)
        {
            // Swap the parent and the current node.
            Ball *tmp;
            tmp = this->array[currentNodeIndex];
            this->array[currentNodeIndex] = this->array[this->GetParentIndex(currentNodeIndex)];
            this->array[this->GetParentIndex(currentNodeIndex)] = tmp;
            // Update these variables for the next run.
            currentNodeIndex = this->GetParentIndex(currentNodeIndex);
            parentSumOfDigits = this->array[this->GetParentIndex(currentNodeIndex)]->GetValue();
            currentSumOfDigits = this->array[currentNodeIndex]->GetValue();
        }
    }
}
// //Returns the root node, switches the root node with the last node and downheapifies.
Ball* Heap::RemoveMaxNode()
{
    // If there is only one node in the heap, return it and exit. No need to heapify.
    if (this->currentHeapSize == 1)
    {
        this->currentHeapSize--;
        return this->array[0];
    }
    // Else, we need to do a longer process.
    else
    {
        // Remove the root node.
        Ball* returnVal = this->array[0];
        this->currentHeapSize--; 
        // Set the last node in the heap to the root.
        this->array[0] = this->array[this->currentHeapSize];
        this->array.pop_back();
        // Heapify from the root node.
        this->Heapify(0);
        // Return the original max node.
        return returnVal;
    }
}
// //Performs a downheapify on a node at any given index.
void Heap::Heapify(int inputIndex)
{
    // Get the indices of the left and right child.
    // Will return a value greater than the current heap size if left or right child does not exist.
    int leftChildIndex = this->GetLeftChild(inputIndex);
    int rightChildIndex = this->GetRightChild(inputIndex);
  
    int largestChildIndex = inputIndex;
    // If this is Rusty.
    if (this->heapType == "RUSTY")
    {
        // If the current node actually has a left child node.
        // And if that child has either a GREATER or LESS THAN sum of digits.
        if (leftChildIndex <= this->currentHeapSize && this->array[leftChildIndex]->GetSumOfDigits() >= this->array[inputIndex]->GetSumOfDigits())
        {
            // Case 1: If the sum of digits is equal, but the child has a greater RAW VALUE.
            if (this->array[leftChildIndex]->GetSumOfDigits() == this->array[inputIndex]->GetSumOfDigits() 
                && this->array[leftChildIndex]->GetValue() > this->array[inputIndex]->GetValue())
                {
                    // Then set the largest child as the left one.
                    largestChildIndex = leftChildIndex;
                }
            // Case 2: If the left child has a sum of digits that is GREATER than the current node.
            else if (this->array[leftChildIndex]->GetSumOfDigits() > this->array[inputIndex]->GetSumOfDigits())
            {
                // Then set the largest child as the left one.
                largestChildIndex = leftChildIndex;
            }
            
        }
        // If the current node actually has a right child node.
        // And if that child has either a GREATER or LESS THAN sum of digits to the current largest node (could be current node or left child).
        if (rightChildIndex <= this->currentHeapSize && this->array[rightChildIndex]->GetSumOfDigits() >= this->array[largestChildIndex]->GetSumOfDigits())
        {
            // Case 1: If the sum of digits is equal, but the child has a greater RAW VALUE.
            if (this->array[rightChildIndex]->GetSumOfDigits() == this->array[largestChildIndex]->GetSumOfDigits()
                && this->array[rightChildIndex]->GetValue() > this->array[largestChildIndex]->GetValue())
                {
                    // Set the largest node as the right one.
                    largestChildIndex = rightChildIndex;
                }
            // Case 2: If the right child has a sum of digits that is GREATER than the current largest node (could be current node or left child).
            else if (this->array[rightChildIndex]->GetSumOfDigits() > this->array[largestChildIndex]->GetSumOfDigits())
            {
                // Set the largest node as the right one.
                largestChildIndex = rightChildIndex;
            }
            
        }
        // A last check to make sure that we can actually do a swap.
        if (largestChildIndex != inputIndex)
        {
            // Swap the current node with its highest priority child.
            Ball* tmp;
            tmp = this->array[inputIndex];
            this->array[inputIndex] = this->array[largestChildIndex];
            this->array[largestChildIndex] = tmp;
            // Recrusively heapify on that child.
            this->Heapify(largestChildIndex);
        }
    }
    // If this is Scott.
    else 
    {
        // If the left child exists and it's raw value is greater than the current node's raw value.
        if (leftChildIndex <= this->currentHeapSize && this->array[leftChildIndex]->GetValue() > this->array[inputIndex]->GetValue())
        {
            // Set the largest child as the left.
            largestChildIndex = leftChildIndex;
        }
        // If the right child exists and it's raw value is greater ther the currend largest node's raw value.
        if (rightChildIndex <= this->currentHeapSize && this->array[rightChildIndex]->GetValue() > this->array[largestChildIndex]->GetValue())
        {
            // Set the largest child as the right.
            largestChildIndex = rightChildIndex;
        }
        // A last check to make sure we can actually do a swap.
        if (largestChildIndex != inputIndex)
        {
            // Swap the current node with the highest priority child.
            Ball* tmp;
            tmp = this->array[inputIndex];
            this->array[inputIndex] = this->array[largestChildIndex];
            this->array[largestChildIndex] = tmp;
            // Recursively heapify on that child.
            this->Heapify(largestChildIndex);
        }
    }
}
// Print the heap. 
// Used for debugging.
void Heap::Print()
{
    for (int i = 0; i < this->currentHeapSize; i++)
    {
        cout << this->array[i]->GetValue() << "-" << this->array[i]->GetSumOfDigits() << ", ";
    }
}
// Update the player's total score with the value of the ball they chose.
void Heap::UpdateScore(unsigned long long value)
{
    this->currentScore += value;
}
// Return the player's score.
unsigned long long Heap::GetScore()
{
    return this->currentScore;
}