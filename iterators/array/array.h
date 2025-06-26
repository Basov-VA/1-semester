#include <iostream>

template<typename T>
class Array {
public:
    template<typename R>
    class Iterator
    {
        private:
            R* cur;
        public:
            using iterator_category = std::random_access_iterator_tag;
            using value_type = R;
            using pointer = R*;
            using reference = R&;
            using difference_type = std::ptrdiff_t;

            Iterator(R* cur):
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

    Iterator<T> begin() const{
        return Iterator<T>(data_);
    }
    Iterator<T> end() const{
        return Iterator<T>(data_+size_);
    }
    Iterator<T> begin() {
        return Iterator<T>(data_);
    }
    Iterator<T> end() {
        return Iterator<T>(data_+size_);
    }


    


    Array(std::ostream& ostream):
        Ostream_(ostream),
        size_(0),
        capacity_(2),
        data_(new T[capacity_])
        {
            Ostream_ << "Constructed. " << *this << std::endl;
        }; 

    Array(const Array<T>& array):
        Ostream_(array.Ostream_),
        size_(array.size_),
        capacity_(array.capacity_),
        data_(new T[capacity_]){
            for (size_t i = 0; i < size_; i++)
            {
                data_[i] = array.data_[i];
            }
            Ostream_ << "Constructed from another Array. " << *this << std::endl;
            
        };

    Array(size_t size, std::ostream& ostream = std::cout, T defaultValue = T()):
        Ostream_(ostream),
        size_(size),
        capacity_(size_*2),
        data_(new T[capacity_]){
            for (size_t i = 0; i < size_; i++)
            {
                data_[i] = defaultValue;
            }
            Ostream_ << "Constructed with default. " << *this << std::endl;
            
        };
    ~Array(){
        Ostream_ << "Destructed " << size_ << std::endl;
        delete[] data_;
    }
    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void Reserve(size_t newCapacity) {
        if(newCapacity <= capacity_)
        {
            return;
        }
        else
        {
            T* newData_ = new T[newCapacity];
            for (size_t i = 0; i < newCapacity; i++)
            {
                if(i < size_)
                {
                newData_[i] = data_[i];
                }
                else{
                    newData_[i] = 0;
                }
            }
            delete[] data_;
            data_ = newData_;
            size_ = size_;
            capacity_ = newCapacity;
            
        }
        
    }

    void Resize(size_t newSize) {
        if(size_ > newSize)
        {
            size_ = newSize;
            return;
        }
        if(size_ == newSize)
        {
            return;
        }
        if(size_ < newSize)
        {
            T* newData_ = new T[newSize];
            for (size_t i = 0; i < newSize; i++)
            {
                if(i < size_)
                {
                newData_[i] = data_[i];
                }
                else{
                    newData_[i] = 0;
                }
            }
            delete[] data_;
            data_ = newData_;
            size_ = newSize;
            capacity_ = size_;
            
        }
    }

    void PushBack(T value = 0) 
    {
        if(size_ == capacity_)
        {
            T* newData_ = new T[capacity_*2];
            capacity_ *=2;
            for (size_t i = 0; i < size_; i++)
            {
                newData_[i] = data_[i];
            }
            delete[] data_;
            data_ = newData_;

            
        }
        data_[size_] = value;
        size_++;
    };

    void PopBack() {
        size_--;
    }

    const T& operator [](const size_t i) const {
        return const_cast<Array*>(this)->operator[](i);
    }
    T& operator [](const size_t i) {
        return data_[i];
    }

    explicit operator bool() const {
        return size_ != 0;
    }

    bool operator <(const Array<T>& it) const {
        for (size_t i = 0; i < std::min(this->size_,it.size_); i++)
        {
            if(this->data_[i] < it.data_[i])
            {
                return true;
            }
        }
        return this->size_<it.size_;
        
    }

    bool operator>(const Array& it) const
    {
        return it < *this;
    }
    bool operator!=(const Array& it) const
    {
        return (it < *this) || (*this < it);
    }
    bool operator==(const Array& it) const
    {
        return !(it != *this);
    }
    bool operator<=(const Array& it) const
    {
        return (*this < it) || (*this == it);
    }
    bool operator>=(const Array& it) const
    {
        return (it < *this) || (*this == it);
    }

    Array& operator<<(const T value)
    {
        PushBack(value);
        return *this;
    };
    Array& operator<<(const Array<T>& it)
    {
        for (size_t i = 0; i < it.size_; i++)
        {
            this->PushBack(it.data_[i]);
        }
        return *this;
        
    }

    bool Insert(size_t pos, const T& value) {
        if(size_ < pos)
        {
            return false;
        }
        if(size_ == capacity_)
        {
            T* newData_ = new T[capacity_*2];
            capacity_ *=2;
            for (size_t i = 0; i < size_; i++)
            {
                newData_[i] = data_[i];
            }
            delete[] data_;
            data_ = newData_;

            
        }
        for (size_t i = size_; i > pos; i--)
        {
            data_[i] = data_[i-1];
        }
        data_[pos] = value;
        size_++;
        return true;
    }

    bool Erase(size_t pos) {
        if(size_ < pos)
        {
            return false;
        }
        for (size_t i = pos; i < size_-1; i++)
        {
            data_[i] = data_[i+1];
        }
        size_--;
        return true;
    }

    //friend std::ostream& operator<<(std::ostream& ostream, const Array<T>& array);

private:
    std::ostream& Ostream_;
    size_t size_,capacity_;
    T* data_;
};

template<typename T>
std::ostream& operator<<(std::ostream& ostream, const Array<T>& array) {
    ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << array.Size();
    if(array.Size() == 0){
        return ostream;
    }
    ostream << ", elements are: ";
    ostream << array[0];
    for (size_t i = 1; i < array.Size(); i++)
    {
        ostream << ", " <<  array[i];
    }
    return ostream;
}