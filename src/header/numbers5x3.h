
#include <array>
#include <Arduino.h>
#include "release.h"
#pragma once



constexpr uint16_t compress5x3(const std::array<std::array<bool, 3>, 5>);
std::array<std::array<bool, 3>, 5> decompress5x3(const uint16_t);
constexpr std::array<uint16_t, 10> compress5x3();




