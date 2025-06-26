/*#pragma once
#include<iostream>
class Range {
    public:
        class Iterator
        {
            private:
                int64_t* end;
                int64_t* step;
                int64_t* cur;
            public:
                using iterator_category = std::random_access_iterator_tag;
                using value_type = int64_t;
                using pointer = int64_t*;
                using reference = int64_t&;
                using difference_type = std::ptrdiff_t;

                Iterator(int64_t* cur):
                    cur(cur){};

                reference operator*() const
                {
                    return *cur;
                }

                Iterator& operator++()
                {
                    ++cur;
                    return *this;
                }

                Iterator operator++(int)
                {
                    Iterator x = *this;
                    cur++;
                    return x;
                }

                Iterator& operator--()
                {
                    --cur;
                    return *this;
                }

                Iterator operator--(int)
                {
                    Iterator x = *this;
                    cur--;
                    return x;
                }

                bool operator==(const Iterator& x) const
                {
                    return this->cur == x.cur;
                }

                bool operator!=(const Iterator& x) const
                {
                    return this->cur != x.cur;
                }

                Iterator& operator+=(difference_type x)
                {
                    cur+=x;
                    return *this;
                }

                Iterator& operator-=(difference_type x)
                {
                    cur-=x;
                    return *this;
                }

                Iterator operator-(difference_type x) const
                {
                    Iterator q = *this;
                    q-=x;
                    return q;
                }

                Iterator operator+(difference_type x) const
                {
                    Iterator q = *this;
                    q+=x;
                    return q;
                }

                difference_type operator-(const Iterator& x) const
                {
                    return cur - x.cur;
                }

                difference_type operator+(const Iterator& x) const
                {
                    return cur + x.cur;
                }

                

                bool operator<(const Iterator& x) const
                {
                    return cur < x.cur;
                }

                bool operator<=(const Iterator& x) const
                {
                    return cur <= x.cur;
                }

                bool operator>(const Iterator& x) const
                {
                    return cur > x.cur;
                }

                bool operator>=(const Iterator& x) const
                {
                    return cur >= x.cur;
                }

                friend Iterator operator+(difference_type n, const Iterator& it) {
                Iterator f = it;
                f += n;
                return f;
                }

                friend Iterator operator-(difference_type n, const Iterator& it) {
                Iterator f = it;
                f -= n;
                return f;
                }

            reference operator[](difference_type n) const
            {
                return*(cur + n);
            }

            pointer operator ->(){
                return cur;
            }

        };

    Iterator begin() const{
        return Iterator(start);
    }
    Iterator end() const{
        return Iterator(end + 1);
    }
    Iterator begin() {
        return Iterator(start);
    }
    Iterator end() {
        return Iterator(start);
    }


    
    Range(int64_t cur_0):
        start(0),
        end(cur_0),
        step(1),


    Range(int64_t cur_0,int64_t cur_1):
        start(cur),
        end(n),
        step(1){};

    Range(int64_t cur_0,int64_t cur_1,int64_t st):
        start(cur),
        end(n),
        step(st){};

    private:
        int64_t start;
        int64_t end;
        int64_t step;

};*/


#include <iostream>
#include <iterator>
#include <cassert>

class Range {
public:
    class Iterator {
    public:

        using iterator_category = std::random_access_iterator_tag;
        using value_type = int64_t;
        using pointer = void;
        using reference = void;
        using difference_type = std::ptrdiff_t;

        Iterator(int64_t current, int64_t step) : current_(current), step_(step) {}


        bool operator==(const Iterator& other) const {
            return current_ == other.current_;
        }


        bool operator!=(const Iterator& other) const {
            return current_ != other.current_;
        }

        int64_t operator*() const {
            return current_;
        }

        Iterator& operator++() {
            current_ += step_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator x = *this;
            current_ += step_;
            return x;
        }
        
        /*difference_type operator-(const Iterator& x) const
        {
            return current_ - x.current_;
        }*/

    private:
        int64_t current_;
        int64_t step_;
    };

    Range(int64_t end) : start_(0), end_(end), step_(1) {}

    Range(int64_t start, int64_t end) : start_(start), end_(end), step_(1) {}

    Range(int64_t start, int64_t end, int64_t step) : start_(start), end_(end), step_(step) {
        end_ = start_ + ((end_ - start_)/step + ((end_ - start_)%step!=0))*step_;
    }

    Iterator begin() const {
        return Iterator(start_, step_);
    }

    Iterator end() const {
        return Iterator(end_, step_);
    }

    int64_t Size() const
    {
        return (end_ - start_)/step_;
    }

private:
    int64_t start_;
    int64_t end_;
    int64_t step_;
};

