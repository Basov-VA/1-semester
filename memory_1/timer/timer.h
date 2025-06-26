#include<iostream>
#include<chrono>
#include <thread>



class Timer {
private:
    std::chrono::steady_clock::time_point start;
    std::chrono::milliseconds time;
public:
template<typename T>
    Timer(const std::chrono::duration<T>& x):
    start(std::chrono::steady_clock::now()),
    time(std::chrono::duration_cast<std::chrono::milliseconds>(x))
    {}

    bool Expired() const
    {
        auto t = std::chrono::steady_clock::now();
        auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(t - start);
        return t1 >= time;
    }

};


class TimeMeasurer {
private:
    std::ostream& Ostream_;
    std::chrono::steady_clock::time_point start_;
public:
    TimeMeasurer(std::ostream& istream_ = std::cout):
        Ostream_(istream_),
        start_(std::chrono::steady_clock::now())
        {}
    ~TimeMeasurer()
    {
        Ostream_ << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start_).count() << "\n";
    }

};
