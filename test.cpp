#include <iostream>
#include <stdio.h>
#include <array>
#include <cstdint>
#include <string>

int main(){
    std::array<uint8_t, 64 * 1024> ram;
    uint8_t memory[64*1024];
    std::string test_string = "stuff";
    printf("test string is %s\n", test_string.c_str());
    printf("%ld\n", sizeof(memory));
    printf("%ld\n", sizeof(ram));

}