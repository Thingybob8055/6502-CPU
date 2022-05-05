#include "bus.h"
#include <stdio.h>

bus::bus() {
    memory[RAM_SIZE] = {0}; //initialise memory to 0
}

bus::~bus() {
}

uint8_t bus::bus_read(uint16_t address) {
    if (address >= 0x0000 && address <= 0xFFFF) {
        return memory[address]; //return value at address
    }
    else {
        printf("Invalid address range");
        exit(-1);
    }
}

void bus::bus_write(uint16_t address, uint8_t value) {
    if (address >= 0x0000 && address <= 0xFFFF) {
        memory[address] = value; //insert value at address
    }
    else {
        printf("Invalid address range");
        exit(-1);
    }
}