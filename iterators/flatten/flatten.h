
#pragma once
#include<iostream>
#include<vector>

template<class T>
class FlattenedVector{
    template<class R>
    class Iterator{
        private:
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = R;
            using pointer = R*;
            using reference = R&;
            using difference_type = int;

            Iterator(std::vector<std::vector<T>>& flat_vector, std::vector<int>& pre_summs,int index):
                it_vector(flat_vector),
                it_pref_summs(pre_summs),
                it_index_of_el(index){};

            reference operator[](difference_type x)const
            {
                return *(*this + x);
            }

            reference operator*() const
            {
                int left = 0;
                int right = it_vector.size();
                int middle;
                while(right - left > 1)
                {
                    middle = (right + left)/2;
                    if(it_index_of_el < it_pref_summs[middle])
                    {
                        right = middle;
                        left = left;
                    }
                    else
                    {
                        right = right;
                        left = middle;
                    }
                }
                return it_vector[right - 1][it_index_of_el - it_pref_summs[right - 1]];
            }



            Iterator& operator=(const Iterator& other)
            {
                this->it_index_of_el = other.it_index_of_el;
                this->it_pref_summs = other.it_pref_summs;
                this->it_vector = other.it_vector;
                return *this;
            }



            //сравнения <,>,<=,>=,==,!=
            bool operator==(const Iterator& other) const
            {
                return this->it_index_of_el == other.it_index_of_el;
            }
            bool operator==(difference_type x) const
            {
                return this->it_index_of_el == x;
            }

            bool operator!=(const Iterator& other) const
            {
                return !(this->it_index_of_el == other.it_index_of_el);
            }

            bool operator<(const Iterator& other) const
            {
                return this->it_index_of_el < other.it_index_of_el;
            }
            bool operator<=(const Iterator& other) const
            {
                return this->it_index_of_el <= other.it_index_of_el;
            }
            bool operator>(const Iterator& other) const
            {
                return this->it_index_of_el > other.it_index_of_el;
            }
            bool operator>=(const Iterator& other) const
            {
                return this->it_index_of_el >= other.it_index_of_el;
            }

            //операции ++,--
            Iterator& operator++()
            {
                it_index_of_el++;
                return *this;
            }
            
            Iterator& operator--()
            {
                it_index_of_el--;
                return *this;
            }
            Iterator& operator++(int)
            {
                Iterator q = *this;
                it_index_of_el++;
                return q;
            }
            Iterator& operator--(int)
            {
                Iterator q = *this;
                it_index_of_el--;
                return q;
            }

            //операторы +=,-=,-,+
            Iterator& operator+=(difference_type x)
            {
                it_index_of_el += x;
                return *this;
            }
            Iterator& operator-=(difference_type x)
            {
                it_index_of_el -= x;
                return *this;
            }

            Iterator operator+(difference_type x) const
            {
                Iterator q = *this;
                q += x;
                return q;
            }
            Iterator operator-(difference_type x) const
            {
                Iterator q = *this;
                q -= x;
                return q;
            }
            friend Iterator operator+(difference_type x,const Iterator& other)
            {
                return Iterator(other.it_vector,other.it_pref_summs,other.it_index_of_el + x);
            }
            friend Iterator operator-(difference_type x,const Iterator& other)
            {
                return Iterator(other.it_vector,other.it_pref_summs,other.it_index_of_el - x);
            }
            difference_type operator-(const Iterator& other) const
            {
                return this->it_index_of_el - other.it_index_of_el;
            }
        private:
            std::vector<std::vector<T>>& it_vector;
            std::vector<int>& it_pref_summs;
            difference_type it_index_of_el;

    };
    public:
        FlattenedVector(std::vector<std::vector<T>>& vector):
            flat_vector(vector),
            flat_pre_summs({0})
            {
                int sizex = 0;
                for (size_t i = 0; i < vector.size(); i++)
                {
                    sizex += vector[i].size();
                    flat_pre_summs.push_back(sizex);
                }
                
            };
    Iterator<T> begin()
    {
        return Iterator<T>(flat_vector,flat_pre_summs,0);
    }
    Iterator<T> end()
    {
        return Iterator<T>(flat_vector,flat_pre_summs,flat_pre_summs[flat_pre_summs.size() - 1]);
    }
    const Iterator<T> begin() const
    {
        return Iterator<T>(flat_vector,flat_pre_summs,0);
    }
    const Iterator<T> end() const
    {
        return Iterator<T>(flat_vector,flat_pre_summs,flat_pre_summs[flat_pre_summs.size() - 1]);
    }
    private:
        std::vector<std::vector<T>>& flat_vector;
        std::vector<int> flat_pre_summs;
};