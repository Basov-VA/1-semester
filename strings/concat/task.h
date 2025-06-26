/*
 * Нужно написать функцию, которая принимает два указателя на C-строки и возвращает указатель на новую C-строку,
 * являющуюся конкатенацией данных строк. В реализации не использовать `memcpy`, `<cstring>` и `<string>`
 */

#include<iostream>
char* concat(const char* lhs, const char* rhs)
{
    size_t i = 0;
    size_t j = 0;
    while(lhs[i] != '\0')
    {
        i++;
    }
    while(rhs[j] != '\0')
    {
        j++;
    }
    char* ans = new char[j + i + 1];
    ans[j + i] = '\0';
    i = 0;
    j = 0;
    while(lhs[i] != '\0')
    {   
        ans[i] = lhs[i];
        i++;
    }
    while(rhs[j] != '\0')
    {
        ans[j + i] = rhs[j];
        j++;
    }

    return ans;
}
