#pragma once

#include <cstdint>
#include <array>
#include "6502cpu.h"

#define RAM_SIZE 64*1024

class bus {
    public:
        bus();
        ~bus();

    public: //stuff on the bus
        cpu nes_cpu;
        uint8_t memory[RAM_SIZE];

    public: //reading and writing to the bus
        uint8_t bus_read(uint16_t address);
        void bus_write(uint16_t address, uint8_t value);
};