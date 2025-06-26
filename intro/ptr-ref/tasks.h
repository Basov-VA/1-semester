#pragma once
#include <climits>
#include <limits>
#include <vector>
#include <algorithm>
#include <iostream>

namespace NPointers
{
    void Increment(int *x)
    {
        *x += 1;
    }
    int Multiply(int a, int b, bool *f)
    {
        long long ans = (long long)a * (long long)b;
        if (ans > INT_MAX)
        {
            *f = true;
        }
        else
        {
            *f = false;
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

    int SizeOfMaximumSquareOfCrosses(const char *a, int si, int sj)
    {
        auto b = a;
        std::vector<std::vector<char>> mas(si, std::vector<char>(sj));
        int ind = 0, ans = 0;
        for (int i = 0; i < si; i++)
        {
            for (int j = 0; j < sj; j++)
            {
                mas[i][j] = b[ind];
                ind++;
            }
        }

        for (int i = 0; i < si; i++)
        {
            for (int j = 0; j < sj; j++)
            {
                for (int i1 = i + 1; i1 < si; i1++)
                {
                    for (int j1 = j + 1; j1 < sj; j1++)
                    {
                        if (i1 - i == j1 - j)
                        {
                            bool ch = 1;
                            for (int i_x = i; i_x <= i1; i_x++)
                            {
                                for (int j_x = j; j_x <= j1; j_x++)
                                {
                                    ch = ch && (mas[i_x][j_x] == '+');
                                }
                            }
                            if (ch)
                            {
                                ans = std::max(ans, i1 - i + 1);
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
}
