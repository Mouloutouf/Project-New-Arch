//
// Created by maxdu on 29/11/2025.
//

#ifndef NEWARCH_UTILITY_H
#define NEWARCH_UTILITY_H

#include <random>
#include <algorithm>
#include <chrono>
#include <vector>

const time_t CURRENT_TIME = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

const std::string ASSETS_FOLDER = "Assets/";

static std::string GetSpritePath(const std::string& _spriteName) { return ASSETS_FOLDER + _spriteName + ".png"; }

template<typename T>
static T GetRandomElementFromContainer(const std::vector<T>& _container)
{
    std::vector<T> result;
    sample(_container.begin(), _container.end(), back_inserter(result), 1, std::mt19937{std::random_device {}() });
    return result.front();
}

template<typename T>
static T GetRandomElementFrom(const std::vector<T>& _container)
{
    thread_local std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<size_t> dist(0, _container.size() - 1);
    return _container[dist(rng)];
}

inline int RandomInt(const int min, const int max)
{
    thread_local std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution dist(min, max);
    return dist(rng);
}

inline float RandomFloat(const float min, const float max)
{
    thread_local std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution dist(min, max);
    return dist(rng);
}

#endif //NEWARCH_UTILITY_H