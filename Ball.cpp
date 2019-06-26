#include "Ball.hpp"
//Constructor
Ball::Ball(int inputValue) 
{
    this->value = inputValue;
    CalculateSumOfDigits();
    this->chosen = false;
}
// Calculates the sum of digits for the balls raw value.
void Ball::CalculateSumOfDigits()
{
    int sum = 0;
    int actualValue = this->value;
    while (actualValue != 0)
    {
        sum = sum + actualValue % 10;
        actualValue = actualValue / 10;
    }
    this->sumOfDigits = sum;
}

void Ball::SetChosen(bool value)
{
    this->chosen = value;
}

unsigned long long Ball::GetValue() 
{
    return this->value;
}

unsigned long long Ball::GetSumOfDigits()
{
    return this->sumOfDigits;
}

bool Ball::GetChosen()
{
    return this->chosen;
}