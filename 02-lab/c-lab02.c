#include <stdio.h>

int main()
{
    const size_t SIZE = 10;
    __uint8_t arr[] = {127, 255, 2, 3, 4, 5, 6, 7, 8, 9};
    __uint8_t bitmask = 34; // same as 00100010

    __uint16_t sum = 0;
    for (int i = 0; i < SIZE; ++i)
    {
        __uint8_t res = arr[i] & bitmask;
        if (res == bitmask)
        {
            sum += arr[i];
        }
    }

    printf("%d\n", sum);

    return 0;
}