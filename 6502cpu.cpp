#include "bus.h"
#include "6502cpu.h"

bus cpu_bus; //bus instance in cpu to map functions

cpu::cpu() {
    //opcode table
    Instruction instructions[0x100] = {
        { "BRK", BRKX, IMMX, 7 },
        { "ORA", ORAX, IZXX, 6 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "???", NOPX, IMPX, 3 },
        { "ORA", ORAX, ZP0X, 3 },
        { "ASL", ASLX, ZP0X, 5 },
        { "???", XXXX, IMPX, 5 },
        { "PHP", PHPX, IMPX, 3 },
        { "ORA", ORAX, IMMX, 2 },
        { "ASL", ASLX, IMPX, 2 },
        { "???", XXXX, IMPX, 2 },
        { "???", NOPX, IMPX, 4 },
        { "ORA", ORAX, ABSX, 4 },
        { "ASL", ASLX, ABSX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "BPL", BPLX, RELX, 2 },
        { "ORA", ORAX, IZYX, 5 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "???", NOPX, IMPX, 4 },
        { "ORA", ORAX, ZPXX, 4 },
        { "ASL", ASLX, ZPXX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "CLC", CLCX, IMPX, 2 },
        { "ORA", ORAX, ABYX, 4 },
        { "???", NOPX, IMPX, 2 },
        { "???", XXXX, IMPX, 7 },
        { "???", NOPX, IMPX, 4 },
        { "ORA", ORAX, ABXX, 4 },
        { "ASL", ASLX, ABXX, 7 },
        { "???", XXXX, IMPX, 7 },
        { "JSR", JSRX, ABSX, 6 },
        { "AND", ANDX, IZXX, 6 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "BIT", BITX, ZP0X, 3 },
        { "AND", ANDX, ZP0X, 3 },
        { "ROL", ROLX, ZP0X, 5 },
        { "???", XXXX, IMPX, 5 },
        { "PLP", PLPX, IMPX, 4 },
        { "AND", ANDX, IMMX, 2 },
        { "ROL", ROLX, IMPX, 2 },
        { "???", XXXX, IMPX, 2 },
        { "BIT", BITX, ABSX, 4 },
        { "AND", ANDX, ABSX, 4 },
        { "ROL", ROLX, ABSX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "BMI", BMIX, RELX, 2 },
        { "AND", ANDX, IZYX, 5 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "???", NOPX, IMPX, 4 },
        { "AND", ANDX, ZPXX, 4 },
        { "ROL", ROLX, ZPXX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "SEC", SECX, IMPX, 2 },
        { "AND", ANDX, ABYX, 4 },
        { "???", NOPX, IMPX, 2 },
        { "???", XXXX, IMPX, 7 },
        { "???", NOPX, IMPX, 4 },
        { "AND", ANDX, ABXX, 4 },
        { "ROL", ROLX, ABXX, 7 },
        { "???", XXXX, IMPX, 7 },
        { "RTI", RTIX, IMPX, 6 },
        { "EOR", EORX, IZXX, 6 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "???", NOPX, IMPX, 3 },
        { "EOR", EORX, ZP0X, 3 },
        { "LSR", LSRX, ZP0X, 5 },
        { "???", XXXX, IMPX, 5 },
        { "PHA", PHAX, IMPX, 3 },
        { "EOR", EORX, IMMX, 2 },
        { "LSR", LSRX, IMPX, 2 },
        { "???", XXXX, IMPX, 2 },
        { "JMP", JMPX, ABSX, 3 },
        { "EOR", EORX, ABSX, 4 },
        { "LSR", LSRX, ABSX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "BVC", BVCX, RELX, 2 },
        { "EOR", EORX, IZYX, 5 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "???", NOPX, IMPX, 4 },
        { "EOR", EORX, ZPXX, 4 },
        { "LSR", LSRX, ZPXX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "CLI", CLIX, IMPX, 2 },
        { "EOR", EORX, ABYX, 4 },
        { "???", NOPX, IMPX, 2 },
        { "???", XXXX, IMPX, 7 },
        { "???", NOPX, IMPX, 4 },
        { "EOR", EORX, ABXX, 4 },
        { "LSR", LSRX, ABXX, 7 },
        { "???", XXXX, IMPX, 7 },
        { "RTS", RTSX, IMPX, 6 },
        { "ADC", ADCX, IZXX, 6 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "???", NOPX, IMPX, 3 },
        { "ADC", ADCX, ZP0X, 3 },
        { "ROR", RORX, ZP0X, 5 },
        { "???", XXXX, IMPX, 5 },
        { "PLA", PLAX, IMPX, 4 },
        { "ADC", ADCX, IMMX, 2 },
        { "ROR", RORX, IMPX, 2 },
        { "???", XXXX, IMPX, 2 },
        { "JMP", JMPX, INDX, 5 },
        { "ADC", ADCX, ABSX, 4 },
        { "ROR", RORX, ABSX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "BVS", BVSX, RELX, 2 },
        { "ADC", ADCX, IZYX, 5 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "???", NOPX, IMPX, 4 },
        { "ADC", ADCX, ZPXX, 4 },
        { "ROR", RORX, ZPXX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "SEI", SEIX, IMPX, 2 },
        { "ADC", ADCX, ABYX, 4 },
        { "???", NOPX, IMPX, 2 },
        { "???", XXXX, IMPX, 7 },
        { "???", NOPX, IMPX, 4 },
        { "ADC", ADCX, ABXX, 4 },
        { "ROR", RORX, ABXX, 7 },
        { "???", XXXX, IMPX, 7 },
        { "???", NOPX, IMPX, 2 },
        { "STA", STAX, IZXX, 6 },
        { "???", NOPX, IMPX, 2 },
        { "???", XXXX, IMPX, 6 },
        { "STY", STYX, ZP0X, 3 },
        { "STA", STAX, ZP0X, 3 },
        { "STX", STXX, ZP0X, 3 },
        { "???", XXXX, IMPX, 3 },
        { "DEY", DEYX, IMPX, 2 },
        { "???", NOPX, IMPX, 2 },
        { "TXA", TXAX, IMPX, 2 },
        { "???", XXXX, IMPX, 2 },
        { "STY", STYX, ABSX, 4 },
        { "STA", STAX, ABSX, 4 },
        { "STX", STXX, ABSX, 4 },
        { "???", XXXX, IMPX, 4 },
        { "BCC", BCCX, RELX, 2 },
        { "STA", STAX, IZYX, 6 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 6 },
        { "STY", STYX, ZPXX, 4 },
        { "STA", STAX, ZPXX, 4 },
        { "STX", STXX, ZPYX, 4 },
        { "???", XXXX, IMPX, 4 },
        { "TYA", TYAX, IMPX, 2 },
        { "STA", STAX, ABYX, 5 },
        { "TXS", TXSX, IMPX, 2 },
        { "???", XXXX, IMPX, 5 },
        { "???", NOPX, IMPX, 5 },
        { "STA", STAX, ABXX, 5 },
        { "???", XXXX, IMPX, 5 },
        { "???", XXXX, IMPX, 5 },
        { "LDY", LDYX, IMMX, 2 },
        { "LDA", LDAX, IZXX, 6 },
        { "LDX", LDXX, IMMX, 2 },
        { "???", XXXX, IMPX, 6 },
        { "LDY", LDYX, ZP0X, 3 },
        { "LDA", LDAX, ZP0X, 3 },
        { "LDX", LDXX, ZP0X, 3 },
        { "???", XXXX, IMPX, 3 },
        { "TAY", TAYX, IMPX, 2 },
        { "LDA", LDAX, IMMX, 2 },
        { "TAX", TAXX, IMPX, 2 },
        { "???", XXXX, IMPX, 2 },
        { "LDY", LDYX, ABSX, 4 },
        { "LDA", LDAX, ABSX, 4 },
        { "LDX", LDXX, ABSX, 4 },
        { "???", XXXX, IMPX, 4 },
        { "BCS", BCSX, RELX, 2 },
        { "LDA", LDAX, IZYX, 5 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 5 },
        { "LDY", LDYX, ZPXX, 4 },
        { "LDA", LDAX, ZPXX, 4 },
        { "LDX", LDXX, ZPYX, 4 },
        { "???", XXXX, IMPX, 4 },
        { "CLV", CLVX, IMPX, 2 },
        { "LDA", LDAX, ABYX, 4 },
        { "TSX", TSXX, IMPX, 2 },
        { "???", XXXX, IMPX, 4 },
        { "LDY", LDYX, ABXX, 4 },
        { "LDA", LDAX, ABXX, 4 },
        { "LDX", LDXX, ABYX, 4 },
        { "???", XXXX, IMPX, 4 },
        { "CPY", CPYX, IMMX, 2 },
        { "CMP", CMPX, IZXX, 6 },
        { "???", NOPX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "CPY", CPYX, ZP0X, 3 },
        { "CMP", CMPX, ZP0X, 3 },
        { "DEC", DECX, ZP0X, 5 },
        { "???", XXXX, IMPX, 5 },
        { "INY", INYX, IMPX, 2 },
        { "CMP", CMPX, IMMX, 2 },
        { "DEX", DEXX, IMPX, 2 },
        { "???", XXXX, IMPX, 2 },
        { "CPY", CPYX, ABSX, 4 },
        { "CMP", CMPX, ABSX, 4 },
        { "DEC", DECX, ABSX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "BNE", BNEX, RELX, 2 },
        { "CMP", CMPX, IZYX, 5 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "???", NOPX, IMPX, 4 },
        { "CMP", CMPX, ZPXX, 4 },
        { "DEC", DECX, ZPXX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "CLD", CLDX, IMPX, 2 },
        { "CMP", CMPX, ABYX, 4 },
        { "NOP", NOPX, IMPX, 2 },
        { "???", XXXX, IMPX, 7 },
        { "???", NOPX, IMPX, 4 },
        { "CMP", CMPX, ABXX, 4 },
        { "DEC", DECX, ABXX, 7 },
        { "???", XXXX, IMPX, 7 },
        { "CPX", CPXX, IMMX, 2 },
        { "SBC", SBCX, IZXX, 6 },
        { "???", NOPX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "CPX", CPXX, ZP0X, 3 },
        { "SBC", SBCX, ZP0X, 3 },
        { "INC", INCX, ZP0X, 5 },
        { "???", XXXX, IMPX, 5 },
        { "INX", INXX, IMPX, 2 },
        { "SBC", SBCX, IMMX, 2 },
        { "NOP", NOPX, IMPX, 2 },
        { "???", SBCX, IMPX, 2 },
        { "CPX", CPXX, ABSX, 4 },
        { "SBC", SBCX, ABSX, 4 },
        { "INC", INCX, ABSX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "BEQ", BEQX, RELX, 2 },
        { "SBC", SBCX, IZYX, 5 },
        { "???", XXXX, IMPX, 2 },
        { "???", XXXX, IMPX, 8 },
        { "???", NOPX, IMPX, 4 },
        { "SBC", SBCX, ZPXX, 4 },
        { "INC", INCX, ZPXX, 6 },
        { "???", XXXX, IMPX, 6 },
        { "SED", SEDX, IMPX, 2 },
        { "SBC", SBCX, ABYX, 4 },
        { "NOP", NOPX, IMPX, 2 },
        { "???", XXXX, IMPX, 7 },
        { "???", NOPX, IMPX, 4 },
        { "SBC", SBCX, ABXX, 4 },
        { "INC", INCX, ABXX, 7 },
        { "???", XXXX, IMPX, 7 }
    };
}

cpu::~cpu() {
}

void cpu::cpu_clock() {
    
    if(cycles == 0) {
        opcode = cpu_bus_read(pc);
        pc++;
        curr_inst = instruction_by_opcode(opcode);
        set_flag(Unused, true);
        uint8_t addition_cycle1 = 0x00;
        uint8_t addition_cycle2 = 0x00;

        switch (curr_inst->addr_mode) {
            case IMPX:
                addition_cycle1	= IMP();
            break;
            case IMMX:
                addition_cycle1	= IMM();
            break;
            case ZP0X:
                addition_cycle1	= ZP0();
            break;
            case ZPXX:
                addition_cycle1	= ZPX();
            break;
            case ZPYX:
                addition_cycle1	= ZPY();
            break;
            case RELX:
                addition_cycle1	= REL();
            break;
            case ABSX:
                addition_cycle1	= ABS();
            break;
            case ABXX:
                addition_cycle1	= ABX();
            break;
            case ABYX:
                addition_cycle1	= ABY();
            break;
            case INDX:
                addition_cycle1	= IND();
            break;
            case IZXX:
                addition_cycle1	= IZX();
            break;
            case IZYX:
                addition_cycle1	= IZY();
            break;
            default:
                printf("Unknown Addressing Mode");
                exit(-7);
            break;
        }


    }
    


}

uint8_t cpu::IMP() {
    return 0;
    //TODO:
}
uint8_t cpu::IMM() {
    return 0;
    //TODO:
}
uint8_t cpu::ZP0() {
    return 0;
    //TODO:
}
uint8_t cpu::ZPX() {
    return 0;
    //TODO:
}
uint8_t cpu::ZPY() {
    return 0;
    //TODO:
}
uint8_t cpu::REL() {
    return 0;
    //TODO:
}
uint8_t cpu::ABS() {
    return 0;
    //TODO:
}
uint8_t cpu::ABX() {
    return 0;
    //TODO:
}
uint8_t cpu::ABY() {
    return 0;
    //TODO:
}
uint8_t cpu::IND() {
    return 0;
    //TODO:
}
uint8_t cpu::IZX() {
    return 0;
    //TODO:
}
uint8_t cpu::IZY() {
    return 0;
    //TODO:
}

void cpu::set_flag(cpu_flags flags, bool v) {
    //TODO:
}

cpu::Instruction *cpu::instruction_by_opcode(uint8_t opcode) {
    return &instructions[opcode];
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