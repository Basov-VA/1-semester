#include <cstdlib>
#include <iterator>
#include<cstdint>
#include<vector>
/*
 * Нужно написать функцию, которая принимает на вход диапазон, применяет к каждому элементу данную операцию и затем складывает результат применения операции в новый диапазон
 * Входной диапазон задан итераторами [firstIn; lastIn)
 * Выходной диапазон начинается с firstOut и имеет такую же длину как входной диапазон
 * Операция является функцией с одним аргументом (унарная функция), возвращающая результат такого типа, который можно положить в OutputIt
 */

template<class InputIt, class OutputIt, class UnaryOperation>
void Transform(InputIt firstIn, InputIt lastIn, OutputIt firstOut, UnaryOperation op) {

    InputIt begin = firstIn;
    InputIt end = lastIn;
    while(begin != end)
    {
        *firstOut = op(*begin);
        begin++;
        firstOut++;
    }

}

/*
 * Нужно написать функцию, которая принимает на вход диапазон и переставляет элементы в нем таким образом, чтобы элементы,
 * которые удовлетворяют условию p, находились ближе к началу диапазона, чем остальные элементы.
 * Входной диапазон задан итераторами [first; last)
 * p является функцией с одним аргументом (унарная функция), возвращающая результат типа bool
 */

template<class BidirIt, class UnaryPredicate>
void Partition(BidirIt first, BidirIt last, UnaryPredicate p) {
    BidirIt begin = first + 1;
    while(begin < last)
    {
        if(p(*begin))
        {
            BidirIt q = begin - 1;
            while(q != first - 1)
            {   
                BidirIt q1 = q + 1;
                std::swap(*q,*q1);
                q--;
            }
        }
        begin++;

    }
}

/*
 * Нужно написать функцию, которая принимает на вход два отстотированных диапазона и объединяет их в новый отсортированный диапазон, содержащий все элементы обоих входных диапазонов.
 */
template<class InputIt1, class InputIt2, class OutputIt>
void Merge(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, OutputIt firstOut) {
    InputIt1 begin1 = first1;
    InputIt2 begin2 = first2;
    OutputIt begin3 = firstOut;
    while(begin1 != last1)
    {
        *firstOut = *begin1;
        firstOut++;
        begin1++;
    }
    while(begin2 != last2)
    {
        *firstOut = *begin2;
        firstOut++;
        begin2++;
    }
    sort(begin3,firstOut);
}

/*
 * Напишите класс "диапазон чисел Фибоначчи"
 * Экземпляр класса представляет из себя диапазон от первого до N-го числа Фибоначчи (1, 2, 3, 5, 8, 13 и т.д.)
 * С помощью функций begin и end можно получить итераторы и пробежать по диапазону или передать их в STL-алгоритмы
 */
class FibonacciRange {
public:
    /*
    class Iterator {
        friend class FibonacciRange;
    public:
        using value_type = uint64_t;
        using difference_type = ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::input_iterator_tag;

        value_type operator *() const {
            return 
        }

        Iterator& operator ++() {
            // prefix increment
        }

        Iterator operator ++(int) {
            // postfix increment
        }

        bool operator ==(const Iterator& rhs) const {
        }

        bool operator <(const Iterator& rhs) const {
        }
    };
    */

    FibonacciRange(size_t amount) {
        Fibonacci.resize(amount);
        Fibonacci[0] = 1;
        Fibonacci[1] = 2;
        size_t i = 2;
        while(i != amount)
        {
            Fibonacci[i] = Fibonacci[i-1] + Fibonacci[i-2];
            i+=1;
        }
        




    }

    auto begin() const {
        return Fibonacci.begin();
    }

    auto end() const {
        return Fibonacci.end();
    }

    size_t size() const {
        return Fibonacci.size();
    }
    private:
        std::vector<uint64_t> Fibonacci;


};
