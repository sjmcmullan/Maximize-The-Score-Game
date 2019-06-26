An interesting problem a lecture of mine came up with.

**Problem Description:**

Scott and Rusty are playing a game named "Maximize The Score". In this game, there are n balls placed on the table. Each ball has a value written on it.

The game starts with a toss. If head comes, then Scott starts the game, else Rusty starts the game. The game is played in the form of rounds. Hence, if Scott wins the toss, the first round will be played by Scott, second round will be played by Rusty, third round will be played by Scott and so on. In each round, the player is allowed to take at max k turns. In each turn, the player picks one ball from the table.

Please note that each round is entirely played by one player only so if it is Scott's round, then he will play xturns (x <= k) and the next round will be played by Rusty.

Rusty is little bit crazy about sum of digits and so he will only pick the ball, whose sum of digits of the value is maximum (for e.g. if 4 and 11 are present on the table, he will pick 4 as the sum of digits of 4 is greater than that of 11). If more than one ball have maximum sum of digits, then he can pick any one of them. Scott doesn't care about sum of digits so he can pick any ball from table. They both want to maximize their score and so both of them will play optimally. Score of a player is the sum of values of all the balls taken by the player. 

Your task is to print the score Scott and Rusty will achieve if they both play optimally. 

**Input Format:**

First line contains an integer T, denoting the number of test-cases. 

Next 3T lines contain the test-cases as shown below:

First line contains two integers n and k, representing the number of balls present on the table and the maximum number of turns allowed per round. 

Second line contains n space separated integers (a1, a2, ... an). Here, ai indicates the score written on ith ball.

Third line contains result of the toss. Here, "HEADS" indicates Scott starts the game, while "TAILS"indicates Rusty starts the game. 

**Sample Input:**
2 
3 
2 
1000 
99 
98 
TAILS 
2 
1 
5 
6 
HEADS 

**Sample Output:**
1000 197
6 5

**To Run:**


1. To compile use command: > g++ -O3 ball.hpp ball.cpp heap.hpp heap.cpp s2916255_maximize_the_score.cpp -o out.exe
2. Then run with command: > ./out.exe {fileName}.txt
3. Output is in tabular format, displaying SCOTT's and then RUSTY's score. Each line is a new game.
