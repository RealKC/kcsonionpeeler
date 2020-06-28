#include "ascii85.hpp"
#include "payloads/0.hpp"

#include <array>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string_view>

auto main() -> int {
    std::ofstream out {"0.result"};
    decode(zeroth_payload, std::string_view {zeroth_payload}.size(), out);
}