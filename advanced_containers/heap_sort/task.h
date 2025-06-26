#include <vector>
#include <queue>

/*
 * Напишите функцию, которая отсортирует целые числа и вернет их в виде вектора.
 * Сортировать числа нужно с помощью использования priority_queue (см. алгоритм heap sort)
 * Подключать какие-либо файлы кроме tash.h нельзя
 */
std::vector<int> HeapSort(const std::vector<int>& v)
{
    std::vector<int> ans;
    std::priority_queue<int> sub_ans;
    for(int x : v)
    {
        sub_ans.push(x);
    }
    int i = 0;
    while(!sub_ans.empty())
    {
        ans.insert(ans.begin(),sub_ans.top());
        sub_ans.pop();
        i++;
    }
    return ans;
    
}
