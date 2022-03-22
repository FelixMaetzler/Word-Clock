

#include <array>
#include <cstdlib>
#pragma once



constexpr uint64_t compress7x5(const std::array<std::array<bool, 5>, 7>);
std::array<std::array<bool, 5>, 7> decompress7x5(const uint64_t);
constexpr const std::array<uint64_t, 26> compressCapitalLetters7x5();
constexpr const std::array<uint64_t, 10> compressNumbers7x5();



