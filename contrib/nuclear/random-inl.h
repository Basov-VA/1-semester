#pragma once

#ifndef NUCLEAR_RANDOM_INL_H_
#error "Direct inclusion of this file is not allowed, include random.h"
#endif

#include <cassert>
#include <limits>

namespace nuclear::random {

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace details {

template <typename Container>
concept Insertable = requires (Container container) {
    container.insert(std::declval<typename Container::value_type>());
};

template <typename Container>
concept PushBackable = requires (Container container) {
    container.push_back(std::declval<typename Container::value_type>());
};

template <Insertable Container, typename T>
void AddToContainer(Container& container, T&& value) {
    container.insert(std::forward<T>(value));
}

template <PushBackable Container, typename T>
void AddToContainer(Container& container, T&& value) {
    container.push_back(std::forward<T>(value));
}

RandomGenerator* GlobalGenerator();

}  // namespace nuclear::random::details

////////////////////////////////////////////////////////////////////////////////////////////////////

template <Arithmetic T>
Population<T>::Population(T min, T max)
    : population_(std::make_pair(min, max))
{
    assert(min <= max);
}

template <Arithmetic T>
Population<T>::Population(std::vector<T> values)
    : population_(std::move(values))
{
    assert(!std::get<std::vector<T>>(population_).empty());
}

template <Arithmetic T>
template <typename Gen>
T Population<T>::Choice(Gen& gen) const {
    if (std::holds_alternative<std::pair<T, T>>(population_)) {
        const auto [min, max] = std::get<std::pair<T, T>>(population_);
        if constexpr (std::is_floating_point_v<T>) {
            return std::uniform_real_distribution<T>(min, max)(gen);
        } else {
            return std::uniform_int_distribution<T>(min, max)(gen);
        }
    } else {
        const auto& values = std::get<std::vector<T>>(population_);
        const auto idx = std::uniform_int_distribution<size_t>(0u, values.size() - 1)(gen);
        return values[idx];
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename... Args>
T RandomGenerator::Generate(Args&&... args) {
    if constexpr (std::is_arithmetic_v<T>) {
        return GenerateNumber<T>(std::forward<Args>(args)...);
    } else {
        return GenerateContainer<T>(std::forward<Args>(args)...);
    }
}

template <Arithmetic T>
T RandomGenerator::GenerateNumber() {
    if constexpr (std::is_floating_point_v<T>) {
        return GenerateNumber<T>(0, 1);
    } else {
        return GenerateNumber<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    }
}

template <Arithmetic T>
T RandomGenerator::GenerateNumber(T min, T max) {
    return GenerateNumber(Population(min, max));
}

template <Arithmetic T>
T RandomGenerator::GenerateNumber(const Population<T>& population) {
    return population.Choice(generator_);
}

template <typename T, typename... Args>
std::vector<T> RandomGenerator::GenerateSeq(size_t len, Args&&... args) {
    return GenerateContainer<std::vector<T>>(len, std::forward<Args>(args)...);
}

template <typename Container, typename... Args>
Container RandomGenerator::GenerateContainer(size_t len, Args&&... args) {
    using T = typename Container::value_type;

    Container result;
    while (std::size(result) < len) {
        details::AddToContainer(result, Generate<T>(std::forward<Args>(args)...));
    }
    return result;
}

template <typename Container, typename... Args>
Container RandomGenerator::GenerateContainer(Range range, Args&&... args) {
    const size_t len = GenerateNumber(range.min, range.max);
    return GenerateContainer<Container>(len, std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename... Args>
T Random(Args&&... args) {
    return details::GlobalGenerator()->Generate<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
std::vector<T> RandomSeq(size_t len, Args&&... args) {
    return details::GlobalGenerator()->GenerateSeq<T>(len, std::forward<Args>(args)...);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace nuclear::random
