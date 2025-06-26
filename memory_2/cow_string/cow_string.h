#include<cstring>
#include<algorithm>
class CowString {
public:
    CowString()
    : state_(new State){};

    CowString(CowString& other)
    : state_(other.state_)
    {
        state_->ref_count++;
    };

    CowString& operator=(const CowString& other) {
        if (state_ == other.state_)
            return *this;
        if (state_->ref_count > 1) {
            state_->ref_count--;
            state_ = other.state_;
            state_->ref_count++;
        } else {
            delete state_;
            state_ = other.state_;
            state_->ref_count++;
        }

        return *this;
    }


    void Resize(int new_size)
    {
        if(new_size > state_->capacity)
        {
            Reserve(new_size * 2);
        }
        state_->size = new_size;
    }

    void Reserve(int new_capacity)
    {
        char* new_data = new char[new_capacity];
        for(int i = 0; i < state_->size; i++)
        {
            new_data[i] = state_->data[i];
        }
        delete[] state_->data;
        state_->data = new_data;
        state_->capacity = new_capacity;
    }

    char& At(int index)
    {
        return state_->data[index];
    }

    char& Back()
    {
        return state_->data[state_->size - 1];
    }

    void PushBack(const char value)
    {
        if(state_->ref_count > 1)
        {
            State* new_state = state_->copy();
            state_->ref_count--;
            state_ = new_state;
        }
        if(state_->size == state_->capacity)
        {
            Reserve(state_->capacity * 2);
        }
        state_->data[state_->size] = value;
        state_->size++;
    }

    int Size()
    {
        return state_->size;
    }

    int Capacity()
    {
        return state_->capacity;
    }
    
    char& operator[](int index)
    {
        if(state_->ref_count > 1)
        {
            State* new_state = state_->copy();
            state_->ref_count--;
            state_ = new_state;
        }
        return state_->data[index];
    }

    ~CowString()
    {
        state_->ref_count--;
        if(state_->ref_count == 0)
        {
            delete state_;
        }
    }
private:
    struct State {
        int ref_count;
        char* data;
        int size;
        int capacity;

        State()
        :ref_count(1),
         data(new char[2]),
         size(0),
         capacity(2){};

        State(int ref_count_,char* data_,int size_,int capacity_)
        :ref_count(ref_count_),
         data(new char[capacity_]),
         size(size_),
         capacity(capacity_){
            for(int i = 0; i < size_; i++)
            {
                data[i] = data_[i];
            }
         };

        State* copy()
        {
            State* new_state = new State(1, this->data, this->size, this->capacity);
            return new_state;
        }

        ~State()
        {
            delete[] data;
        }
         
    };

    State* state_;
};
