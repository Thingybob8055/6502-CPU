#include <iostream>
#include <stdio.h>
#include <array>
#include <cstdint>

int main(){
    std::array<uint8_t, 64 * 1024> ram;
    uint8_t memory[64*1024];

    printf("%ld\n", sizeof(memory));
    printf("%ld\n", sizeof(ram));

}