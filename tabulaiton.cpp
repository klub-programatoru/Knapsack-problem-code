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
vector<int> values = {0}; //values = value of each item
vector<int> weight = {0}; //weight = weight of each item
int N = 0;                //N = nuber of items
int W = 0;                //W = maximal weight capacity of the knapsack

//OUTPUT (output the total value of all items you put into the knapsack)
int bestValue = 0;
int original_N;

void Knapsack(int n, int w, vector<int> &values, vector<int> &weight)
{
    vector<vector<int>> vector3(2, vector<int>(1, 0));
    vector3[1] = weight;

    vector<vector<vector<int>>> table(w, vector<vector<int>>(vector3));

    for (int i = 0; i < w; i++)
    {
        if (i == 0 || table[i][0][0] != 0)
        {
            for (int j = 0; j < table[i][1].size(); j++)
            {
                if (i + weight[j] < w)
                {
                    if (table[i][1][j] != 0)
                    {
                        table[weight[j]][0][0] += values[j];
                        table[weight[j]][1][j] == 0;
                    }
                }
            }

            if (table[i][0][0] > bestValue)
            {
                bestValue = table[i][0][0];
            }
        }
    }
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

    if (values[0] == 0 || weight[0] == 0 || W == 0 || N == 0)
    {
        //Random configuration
        Random();
    }

    //Running the function
    Knapsack(original_N = N, W, values, weight);

    //INPUT printed on the screen
    printf("N = \t%i\n", original_N);
    printf("W = \t%i\n", W);
    printf("\nvalues = \t{");
    for (int i = 0; i < values.size(); i++)
    {
        printf("%i", values[i]);
        if (i != original_N - 1)
        {
            printf(", ");
        }
    }
    printf("}\n\n");
    printf("\nweight = \t{");
    for (int i = 0; i < weight.size(); i++)
    {
        printf("%i", weight[i]);
        if (i != original_N - 1)
        {
            printf(", ");
        }
    }
    printf("}\n");

    //printing out the OUTPUT
    printf("\nOutput: \t%i\n\n", bestValue);

    return 1;
}