#pragma once

#include "bus.h"
#include <cstdint>

class cpu {
private:
    uint8_t cpu_bus_read(uint16_t address); //maps to bus reading and writing
    void cpu_bus_write(uint16_t address, uint8_t value);
public:
    cpu(/* args */);
    ~cpu();
};