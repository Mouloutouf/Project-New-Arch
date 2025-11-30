//
// Created by maxdu on 30/11/2025.
//

#ifndef NEWARCH_RANDOM_H
#define NEWARCH_RANDOM_H

#include <random>
#include <algorithm>
#include <vector>

template<typename T>
static T GetRandomElement(const std::vector<T>& _container)
{
    thread_local std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<size_t> dist(0, _container.size() - 1);
    return _container[dist(rng)];
}

inline int GetRandomInt(const int min, const int max)
{
    thread_local std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution dist(min, max);
    return dist(rng);
}

inline float GetRandomFloat(const float min, const float max)
{
    thread_local std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution dist(min, max);
    return dist(rng);
}

#endif //NEWARCH_RANDOM_H