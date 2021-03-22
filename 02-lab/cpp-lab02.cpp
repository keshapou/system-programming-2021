#include <iostream>
#include <array>

int main()
{
    std::array<uint8_t, 10> arr{127, 255, 2, 3, 4, 5, 6, 7, 8, 9};
    uint8_t bitmask = 34; // same as 00100010

    uint16_t sum = 0;
    for (auto i : arr)
    {
        uint8_t res = bitmask & i;
        if (res == bitmask)
        {
            sum += i;
        }
    }

    std::cout << sum << '\n'; 

    return 0;
}