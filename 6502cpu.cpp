#include "bus.h"
#include "6502cpu.h"

bus cpu_bus; //bus instance in cpu to map functions

cpu::cpu(/* args */) {
}

cpu::~cpu() {
}

uint8_t cpu::cpu_bus_read(uint16_t address) {
    if (address >= 0x0000 && address <= 0xFFFF) {
        return cpu_bus.bus_read(address);
    }
    else {
        printf("Invalid address range");
        exit(-1);
    }
}

void cpu::cpu_bus_write(uint16_t address, uint8_t value) {
    if (address >= 0x0000 && address <= 0xFFFF) {
       cpu_bus.bus_write(address, value);
    }
    else {
        printf("Invalid address range");
        exit(-1);
    }
}