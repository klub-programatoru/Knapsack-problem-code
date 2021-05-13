#include "graphics.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <math.h>
#include <iterator>
#include <vector>
#include <time.h>

using namespace std;

//INPUT (only one of each item can be used)
vector<int> values = {0}; //values = value of each item;     1 <= v[i] <= 1000
vector<int> weight = {0}; //weight = weight of each item;    1 <= w[i] <= 1000
int N = 0;                //N = nuber of items               1 <= N <= 1000
int W = 0;                //W = maximal weight capacity of the knapsack     1 <= W <= 1000

//OUTPUT (output the total value of all items you put into the knapsack)
int bestValue = 0;

//The MEMO object
vector<int> memo;

//other variables
int smallest_W = -1;
int sum = 0;
int bestSum = 0;
int original_N;

int Knapsack(int n, int w, vector<int> &values, vector<int> &weight)
{
    //MEMO CHECK
    if (memo[w] > 0)
    {
        sum = memo[w];
        return 0;
    }

    //reseting the smalles weight to zero
    smallest_W = weight[0];
    //finding the new smalles weight
    for (int i = 0; i < n; i++)
    {
        if (weight[i] < smallest_W)
        {
            smallest_W = weight[i];
        }
    }

    //BASE CASE CHECK - end of branch
    if (w < smallest_W)
    {
        sum = 0;
        return 0;
    }

    //MAIN CYCLE
    for (int i = 0; i < n; i++)
    {
        //remianing capacity of the knapsack
        int remaining_W = w - weight[i];

        //ignoring unsuccesful cases
        if (remaining_W >= 0)
        {
            //the weight that is going to be deleted from vector
            int current_weight = weight[i];
            //the value that is going to be deleted from vector
            int current_value = values[i];

            //erasing the weight and the value that was currently used
            weight.erase(weight.begin() + i);
            values.erase(values.begin() + i);

            //remaining number of items
            int remaining_N = weight.size(); //int remaining_N = N-1;

            //RECURSION
            Knapsack(remaining_N, remaining_W, values, weight);

            //returning the erased weight and value to their vectors
            weight.insert(weight.begin() + i, current_weight);
            values.insert(values.begin() + i, current_value);

            //uptdating sum of values by the value that was currently used
            sum += values[i];

            //determining wheter all used items are allready in the sum vector
            if (weight.size() == original_N && sum != 0)
            {
                //if the sum is better than the bestSum, or if
                //bestSum is empty; update it
                if (sum > bestSum || bestSum == 0)
                {
                    bestSum = sum;
                }
            }

            //MEMO VALUES STORING
            if (memo[w] == 0 || sum > memo[w])
            {
                memo[w] = sum;
            }
        }
    }

    return bestSum;
}
//Creates a vector of random numbers
void Random()
{
    values.clear();
    weight.clear();

    srand(time(NULL));
    N = rand() % 10000 + 1;

    for (int i = 0; i < N; i++)
    {
        values.push_back(rand() % 10000 + 1);
        weight.push_back(rand() % 10000 + 1);
    }

    W = rand() % 10000 + 1;
}

//MAIN
int main(int arg, char *argv[])
{
    //Fillining the memo object with initial values
    for (int i = 0; i < 10005; i++)
    {
        memo.push_back(0);
    }

    //if no values are given; do random
    if (values[0] == 0 || weight[0] == 0 || W == 0 || N == 0)
    {
        //Random configuration
        Random();
    }

    //RUNNING THE FUNCTION
    bestValue = Knapsack(original_N = N, W, values, weight);

    //printing INPUT on the screen
    printf("N = %i\n", original_N);
    printf("W = %i\n", W);
    printf("\nvalues = {");
    for (int i = 0; i < values.size(); i++)
    {
        printf("%i", values[i]);
        if (i != original_N - 1)
        {
            printf(", ");
        }
    }
    printf("}\n\n");
    printf("\nweight = {");
    for (int i = 0; i < weight.size(); i++)
    {
        printf("%i", weight[i]);
        if (i != original_N - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");

    //printing the OUTPUT on the screen
    printf("\nOutput: %i\n", bestValue);

    return 1;
}