#pragma once

#include <random>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace nuclear::random {

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
concept Arithmetic = std::is_floating_point_v<T> || std::is_integral_v<T>;

////////////////////////////////////////////////////////////////////////////////////////////////////

struct Range {
    size_t min;
    size_t max;
};

template <Arithmetic T>
class Population {
public:
    Population(T min, T max);
    explicit Population(std::vector<T> values);

    template <typename Gen>
    T Choice(Gen& gen) const;

private:
    std::variant<std::pair<T, T>, std::vector<T>> population_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class RandomGenerator {
public:
    RandomGenerator();
    explicit RandomGenerator(uint64_t seed);

    template <typename T, typename... Args>
    T Generate(Args&&... args);

    template <typename T, typename... Args>
    std::vector<T> GenerateSeq(size_t len, Args&&... args);

private:
    template <Arithmetic T>
    T GenerateNumber();

    template <Arithmetic T>
    T GenerateNumber(T min, T max);

    template <Arithmetic T>
    T GenerateNumber(const Population<T>& population);

    template <typename Container, typename... Args>
    Container GenerateContainer(size_t len, Args&&... args);

    template <typename Container, typename... Args>
    Container GenerateContainer(Range range, Args&&... args);

private:
    std::mt19937_64 generator_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename... Args>
T Random(Args&&... args);

template <typename T, typename... Args>
std::vector<T> RandomSeq(size_t len, Args&&... args);

////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace nuclear::random

#define NUCLEAR_RANDOM_INL_H_
#include "random-inl.h"
#undef NUCLEAR_RANDOM_INL_H_
