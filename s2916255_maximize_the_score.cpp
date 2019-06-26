#include "Heap.hpp"
#include "Ball.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char **argv)
{
    //This first bit is just reading in the data.
    int gameCount = 0;
    int fileLineCount = 0;
    string inputGameCount; 
    ifstream inputFile(argv[1]);
    if (fileLineCount < 1)
    {
        getline(inputFile, inputGameCount);
        fileLineCount++;
    }
    gameCount = stoi(inputGameCount);
    string inStr;
    vector<string> inputData;
    if (inputFile.is_open())
    {
        while (getline(inputFile, inStr))
        {
            inputData.push_back(inStr);
        }
    }
    //Starting the game.
    //startIndex will increase by three every time a game is over so that it reads in the correct data.
    int startIndex = 0;
    //For every game that is in the input.
    for (int i = 1; i <= gameCount; i++)
    {
        //A heap for each player.
        Heap *player1;
        Heap *player2;
        //The next 10 lines is extracting the number of balls and number of turns.
        int tmp[2] = {0, 0};
        stringstream ss(inputData[startIndex]);
        int index = 0;
        for (int j = 0; ss >> j;)
        {
            tmp[index] = j;
            index++;
        }
        int numberOfBalls = tmp[0];
        int numberOfTurns = tmp[1];
        //Storing the result of the coin flip.
        string coinValue = inputData[startIndex + 2];
        //If the coin toss is tails, then Rusty will go first each round.
        if (coinValue == "TAILS")
        {
            player1 = new Heap("RUSTY");
            player2 = new Heap("SCOTT");
        }
        //If the coin toss is heads, Scott will go first each round.
        else
        {
            player1 = new Heap("SCOTT");
            player2 = new Heap("RUSTY");
        }
        //Create an array of ball references.
        Ball *balls[numberOfBalls];
        int ballIndices = 0;
        stringstream ss1(inputData[startIndex + 1]);
        for (int j = 0; ss1 >> j;)
        {
            Ball *tmpBall = new Ball(j);
            balls[ballIndices] = tmpBall;
            ballIndices++;
        }
        //Add all of the references to both heaps.
        for (int j = 0; j < numberOfBalls; j++)
        {
            player1->InsertNode(balls[j]);
            player2->InsertNode(balls[j]);
        }
        //While there are balls to be chosen.
        while (numberOfBalls > 0)
        {
            //This is the loop for the player1 to choose.
            //Keep choosing while they have turns left and there are balls to choose from.
            for (int j = 0; j < numberOfTurns && numberOfBalls > 0;)
            {
                //Remove the ball reference from the heap.
                Ball * tmp = player1->RemoveMaxNode();
                //If the ball has not been chosen by the other player.
                if (tmp->GetChosen() == false)
                {
                    //Update the score of player1 with the chosen ball.
                    player1->UpdateScore(tmp->GetValue());
                    //Record this ball has having been chosen.
                    tmp->SetChosen(true);
                    //Decrease the number of balls on the table.
                    numberOfBalls--;
                    //Decrease the number of turns for the current player.
                    j++;
                }
            }
            //This is the loop for the player1 to choose.
            //Keep choosing while they have turns left and there are balls to choose from.
            for (int j = 0; j < numberOfTurns && numberOfBalls > 0;)
            {
                //Remove the ball reference from the heap.
                Ball* tmp = player2->RemoveMaxNode();
                 //If the ball has not been chosen by the other player.
                if (tmp->GetChosen() == false)
                {
                    //Update the score of player1 with the chosen ball.
                    player2->UpdateScore(tmp->GetValue());
                    //Record this ball has having been chosen.
                    tmp->SetChosen(true);
                    //Decrease the number of balls on the table.
                    numberOfBalls--;
                    //Decrease the number of turns for the current player.
                    j++;
                }
            }
        }
        //This just prints out the scores. 
        //Will always print Scott's score, then Rusty's.
        if (player1->GetHeapType() == "SCOTT")
        {
            cout << player1->GetScore() << " ";
            cout << player2->GetScore();
        }
        else
        {
            cout << player2->GetScore() << " ";
            cout << player1->GetScore();
        }
        cout << endl;
        //Increment the start index to get the next relevant data.
        startIndex += 3;
    }
    return 0;
}