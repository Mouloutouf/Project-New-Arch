//
// Created by maxdu on 29/11/2025.
//

#ifndef NEWARCH_UTILITY_H
#define NEWARCH_UTILITY_H

#include <chrono>

const time_t CURRENT_TIME = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

const std::string ASSETS_FOLDER = "Assets/";

static std::string GetSpritePath(const std::string& _spriteName) { return ASSETS_FOLDER + _spriteName + ".png"; }

#endif //NEWARCH_UTILITY_H