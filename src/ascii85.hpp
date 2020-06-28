#include <cctype>
#include <cstddef>
#include <cstdint>
#include <ostream>

static auto decode(const char* base85, std::size_t length, std::ostream& os)
    -> void {
    auto ipow = [](int base, int exponent) -> int {
        int result = 1;
        for (auto i = 0; i < exponent; i++) {
            result *= base;
        }
        return result;
    };

    std::size_t start = 2;            // skip over initial <~
    std::size_t end   = length - 2;   // ignore ~>

    std::size_t number_of_bytes_added_for_padding = 0;

    auto get = [&]() -> char {
        if (std::isspace(base85[start])) {
            start++;
        }

        if (start < end) {
            return base85[start++] - '!';
        } else {
            number_of_bytes_added_for_padding++;
            return 'u' - '!';
        }
    };

    while (start < end) {
        auto first  = get();
        auto second = get();
        auto third  = get();
        auto fourth = get();
        auto fifth  = get();

        std::uint32_t group_as_32bit_value =
            first * ipow(85, 4) + second * ipow(85, 3) + third * ipow(85, 2)
            + fourth * ipow(85, 1) + fifth * ipow(85, 0);

        const char bytes[4] {
            (char)((group_as_32bit_value & 0xff'00'00'00) >> 24),
            (char)((group_as_32bit_value & 0x00'ff'00'00) >> 16),
            (char)((group_as_32bit_value & 0x00'00'ff'00) >> 8),
            (char)((group_as_32bit_value & 0x00'00'00'ff))};

        for (std::size_t i            = 0,
                         bytes_to_add = 4 - number_of_bytes_added_for_padding;
             i < bytes_to_add; ++i) {
            os << bytes[i];
        }
    }
}