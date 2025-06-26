#pragma once
#include <climits>
#include <vector>
#include <algorithm>

using namespace std;
namespace NPointers
{
    void Increment(int *x)
    {
        *x += 1;
    }

    int Multiply(int a, int b, bool *f)
    {
        long long ans = (long long)a * (long long)b;
        if (ans > LLONG_MAX)
        {
            *f = 1;
        }
        else
        {
            *f = 0;
        }
        return ans;
    }

    int ScalarProduct(const int a[], const int b[], int len_ab)
    {
        int ans = 0;
        for (int i = 0; i < len_ab; i++)
        {
            ans += a[i] * b[i];
        }
        return ans;
    }

    int SizeOfMaximumSquareOfCrosses(const char *a, int len_a, int len_b)
    {
        auto b = a;
        vector<vector<char>> arr(len_a, vector<char>(len_b));
        int count = 0, ans = 0;
        for (int i = 0; i < len_a; i++)
        {
            for (int j = 0; j < len_b; j++)
            {
                arr[i][j] = b[count];
                count++;
            }
        }

        for (int i = 0; i < len_a; i++)
        {
            for (int j = 0; i < len_b; j++)
            {
                for (int i1 = i + 1; i1 < len_b; i1++)
                {
                    for (int j1 = j + 1; j1 < len_b; j1++)
                    {
                        if (i1 - 1 == j1 - j)
                        {
                            bool t = 1;
                            for (int i_1 = i; i_1 <= i1; i_1++)
                            {
                                for (int j_1 = j; j_1 <= j1; j_1++)
                                {
                                    t = t && (arr[i_1][j_1] == '+');
                                }
                            }
                            if (t == 1)
                            {
                                ans = max(ans, j1 - j + 1);
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
    long long *MultiplyToLongLong(long long a, long long b)
    {
        long long *ans = new long long; // что это???
        *ans = a * b;
        return ans;
    }
    /* To implement:
    SizeOfMaximumSquareOfCrosses
    */
}

namespace NReferences
{
    void MultiplyInplace(int &a, const int b)
    {
        a = a * b;
    }

    int CompareArraysByAverage(const int a[], int b, int c[])
    {
        long double sr_a = 0;
        long double sr_c = 0;
        for (int i = 0; i < b; i++)
        {
            sr_a += a[i];
        }
        for (int i = 0; i < 5; i++)
        {
            sr_c += c[i];
        }
        sr_a = sr_a / b;
        sr_c = sr_c / 5;
        if (sr_a > sr_c)
        {
            return 1;
        }
        else if (sr_a < sr_c)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    /* To implement:
    CompareArraysByAverage
    */
}
