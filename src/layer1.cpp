#include "ascii85.hpp"
#include "payloads/1.hpp"

#include <bit>
#include <bitset>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string_view>
auto process(std::istream&, std::ostream&) -> void;

auto main() -> int {
    constexpr auto tmp_name = "1.result.tmp";
    std::ofstream tmp_file {tmp_name};
    decode(first_payload, std::string_view {first_payload}.size(), tmp_file);
    tmp_file.close();
    std::ofstream out {"1.result"};
    std::ifstream in {tmp_name};
    process(in, out);
    std::remove(tmp_name);
    return 0;
}

auto process(std::istream& in, std::ostream& os) -> void {
    char in_byte;
    while (in >> in_byte) {
        if (std::isspace(in_byte)) {
            continue;
        }
        auto byte = static_cast<std::uint8_t>(in_byte);

        //   1. Flip every second bit
        std::cout << "initial: " << std::bitset<8> {byte} << std::endl;
        ;
        byte ^= 0b0101'0101;
        std::cout << "after:   " << std::bitset<8> {byte} << std::endl;

        //   2. Rotate the bits one position to the right
        byte = std::rotr(byte, 1);
        os << (char)byte;
    }
}
