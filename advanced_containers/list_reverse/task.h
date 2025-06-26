#include <list>
#include<iostream>

void ReverseList(std::list<int>& l)
{
    auto beg = l.begin();
    auto end = l.end();
    end--;
    for (size_t i = 0; i < l.size()/2; i++)
    {
        std::swap(*beg,*end);
        beg++;
        end--;
    }
    
}
