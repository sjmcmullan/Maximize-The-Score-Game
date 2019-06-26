#ifndef BALL_HPP
#define BALL_HPP
class Ball
{
  private:
    //The value given to a ball.
    unsigned long long value;
    //The sum of the digits in the value of the ball.
    unsigned long long sumOfDigits;
    //A boolean to record if the ball has been picked by a player.
    bool chosen;

  public:
    Ball(int input);
    Ball() {};
    void CalculateSumOfDigits();
    void SetChosen(bool value);
    unsigned long long GetValue();
    unsigned long long GetSumOfDigits();
    bool GetChosen();
};
#endif