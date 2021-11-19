#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>

# pragma comment(lib, "secur32.lib")
# pragma comment(lib, "winmm.lib")
# pragma comment(lib, "dmoguids.lib")
# pragma comment(lib, "wmcodecdspuuid.lib")
# pragma comment(lib, "msdmo.lib")
# pragma comment(lib, "Strmiids.lib")

using namespace std;

int Knapsack(vector<int> &val, vector<int> &wt, int W, int n, vector<vector<int>> &memo)
{
    if(n < 0 || W <= 0)
    {
        return 0;
    }
    else if(memo[n][W] > -1)
    {
        return memo[n][W];
    }

    memo[n][W] = (W - wt[n] < 0) ? Knapsack(val, wt, W, n - 1, memo) : (Knapsack(val, wt, W, n - 1, memo) >= val[n] + Knapsack(val, wt, W - wt[n], n - 1, memo)) ? Knapsack(val, wt, W, n - 1, memo) : val[n] + Knapsack(val, wt, W - wt[n], n - 1, memo);
    return memo[n][W];
}

void Random(vector<int> &val, vector<int> &wt, int &W, int n, int &sum)
{
    sum = 0;
    int a = 0;
    srand(time(NULL));
    for(int i = 0; i < n; i++)
    {
        val.push_back(rand() % 1000 + 1);
        a = rand() % 1000 + 1;
        sum += a;
        wt.push_back(a);
    }
    if(sum != 0)
    {
        W = (sum * (double)(rand() / RAND_MAX + 1))/2;
    }
    else
    {
        W = 0;
    }
    
}

//MAIN
int main(int arg, char *argv[])
{
    vector<int> val;
    vector<int> wt;
    int W = 0;
    int n = 0;
    int sum  = 0;

    long startTime, endTime = 0;

    ofstream outdata;
    outdata.open("OUTPUT FILE PATH");
    outdata.close();
    
    outdata.open("OUTPUT FILE PATH", ios::app);

    for(n = 150; n < 2500; n+=150)
    {
        outdata << to_string(n) + '\t';
        for(int i = 0; i < 3; i++)
        {
            Random(val, wt, W, n, sum);
            vector<vector<int>> memo(n, vector<int> (W+1, -1));

            startTime = timeGetTime();
            Knapsack(val, wt, W, n - 1, memo);
            endTime = timeGetTime();

            if(i != 2)
            {
                outdata <<to_string(endTime - startTime) + '\t';
            }
            else
            {
                outdata <<to_string(endTime - startTime);
            }    
        }
        outdata <<endl;
    }

    // cout << "Execution time: " << executionTime * 1000 << "seconds" << endl;

    return 1;
}
