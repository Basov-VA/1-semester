#include "tasks.h"

#include <cmath>

int NOuter::NInner::DoSomething(int lhs, int rhs) {
    return lhs + rhs;
}

int NOuter::DoSomething(int lhs, int rhs) {
    return lhs - rhs;
}

int NOverload::ProcessTwoArgs(int lhs, int rhs) {
    return lhs + rhs;
}

char NOverload::ProcessTwoArgs(char lhs, char rhs) {
    if(lhs > rhs)
    {
        return lhs;
    }
    return rhs;
}

int NOverload::ProcessTwoArgs(int lhs, char rhs) {
    return lhs - rhs;
}

unsigned int NOverflow::WithOverflow(int lhs, int rhs) {
    return lhs + rhs;
}

uint64_t NOverflow::WithOverflow(int64_t lhs, int64_t rhs) {
    return lhs - rhs;
}

int NLoop::SumInRange(const int lhs, const int rhs) {
    return ((lhs + rhs) * (rhs - lhs + 1)) / 2 -rhs;
}

int NLoop::CountFixedBitsInRange(const int from, const int to, const int bitsCnt) {
    int ch = 0;
    for (int i = from; i <= to; i++)
    {
        int x = i,c,k = 0;
        while(x > 0)
        {
            c = x % 2;
            k += c;
            x = x / 2;
        }
        if(k == bitsCnt)
        {
            ch++;
        }
    }
    return ch;
}

double NMath::ComputeMathFormula(const double arg) {
    return fabs((sin(arg) / 2 + cos(arg)) * (sin(arg) / 2 + cos(arg)) + tan(arg) * atan(arg));
}

bool NMath::IsPositive(int arg) {
    return (arg > 0);
}

int NRecursion::CalculateFibonacci(const int arg) {
    int a = 0,b = 1,c;
    for (int i = 0; i < arg; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return a;
    
}