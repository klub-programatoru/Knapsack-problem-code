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

int Knapsack(vector<int> &val, vector<int> &wt, int W, int n, vector<vector<int>> &table)
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= W; j++)
        {
            if(wt[i - 1] > j)
            {
                table[i][j] = table[i - 1][j];
            }
            else
            {
                table[i][j] = (table[i - 1][j - wt[i - 1]] + val[i - 1] > table[i - 1][j]) ? table[i - 1][j - wt[i - 1]] + val[i - 1] : table[i - 1][j];
            }
        }
    }
    return table[n][W];
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
    outdata.open("C:/Users/adamk/OneDrive/Plocha/Extended essay/tabulation.txt");
    outdata.close();
    
    outdata.open("C:/Users/adamk/OneDrive/Plocha/Extended essay/tabulation.txt", ios::app);

    for(n = 150; n < 2500; n += 150)
    {
        outdata << to_string(n) + '\t';
        for(int i = 0; i < 3; i++)
        {
            Random(val, wt, W, n, sum);
            vector<vector<int>> table(n + 1, vector<int> (W + 1, 0));

            startTime = timeGetTime();
            Knapsack(val, wt, W, n - 1, table);
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