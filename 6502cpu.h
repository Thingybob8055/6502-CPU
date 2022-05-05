#pragma once

#include "bus.h"
#include <stdio.h>
#include <string.h>
#include <cstdint>
#include <map>

class cpu {
public:

    //various registers on the CPU
    uint8_t  accu = 0x00;
	uint8_t  x_reg = 0x00;
	uint8_t  y_reg = 0x00;
	uint8_t  sp = 0x00;
	uint16_t pc = 0x0000;
	uint8_t  status = 0x00;

    enum cpu_flags {
		Carry = (1 << 0), //carry
		Zero = (1 << 1),  // Zero
		Disable_Interrupts = (1 << 2), // Disable Interrupts
		Decimal = (1 << 3),	// Decimal Mode (unused as NES does not require it)
		Break = (1 << 4),	// Break
		Unused = (1 << 5),	// Unused
	    Overflow = (1 << 6), // Overflow
		Negative = (1 << 7), // Negative
	};

    void reset(); //force cpu into a known state
	void interrupt_request();
	void non_mask_interrupt();
	void cpu_clock();

    bool complete();

    // Produces a map of strings, with keys equivalent to instruction start locations
	// in memory, for the specified address range
    //dissambler map from OLC NES.
	std::map<uint16_t, std::string> disassemble(uint16_t nStart, uint16_t nStop);

    cpu();
    ~cpu();
private:
    uint8_t cpu_bus_read(uint16_t address); //maps to bus reading and writing
    void cpu_bus_write(uint16_t address, uint8_t value);
    
    //flag setters and getters
    uint8_t get_flag(cpu_flags flags);
	void set_flag(cpu_flags flags, bool v);

    // The read location of data can come from two sources, a memory address, or
	// its immediately available as part of the instruction. This function decides
	// depending on address mode of instruction byte - OneLoneCoder's words
    uint8_t fetch();

    uint8_t  fetched = 0x00; // Represents the working input value to the ALU
	uint16_t temp = 0x0000; // A convenience variable used everywhere
	uint16_t addr_abs = 0x0000; // All used memory addresses end up in here
	uint16_t addr_rel = 0x00; // Represents absolute address following a branch
	uint8_t  opcode = 0x00; // Is the instruction byte
	uint8_t  cycles = 0; // Counts how many cycles the instruction has remaining
	uint32_t clock_count = 0; // A global accumulation of the number of clocks

    //added the X at the end to avoid name clash with function names
    typedef enum {
        IMPX,
        IMMX,
        ZP0X,
        ZPXX,
        ZPYX,
        RELX,
        ABSX,
        ABXX,
        ABYX,
        INDX,
        IZXX,
        IZYX
    } address_mode;
    
    typedef enum {
        XXXX,
        ADCX,
        ANDX,
        ASLX,
        BCCX,
        BCSX,
        BEQX,
        BITX,
        BMIX,
        BNEX,
        BPLX,
        BRKX,
        BVCX,
        BVSX,
        CLCX,
        CLDX,
        CLIX,
        CLVX,
        CMPX,
        CPXX,
        CPYX,
        DECX,
        DEXX,
        DEYX,
        EORX,
        INCX,
        INXX,
        INYX,
        JMPX,
        JSRX,
        LDAX,
        LDXX,
        LDYX,
        LSRX,
        NOPX,
        ORAX,
        PHAX,
        PHPX,
        PLAX,
        PLPX,
        ROLX,
        RORX,
        RTIX,
        RTSX,
        SBCX,
        SECX,
        SEDX,
        SEIX,
        STAX,
        STXX,
        STYX,
        TAXX,
        TAYX,
        TSXX,
        TXAX,
        TXSX,
        TYAX
    } in_type;

    typedef struct {
        std::string name;
        in_type instruction_type;
        address_mode addr_mode;
        uint8_t cycles;
    } Instruction;

    Instruction *curr_inst;
    Instruction instructions[0x100];
    Instruction *instruction_by_opcode(uint8_t opcode);

private:
    //addessing modes
    uint8_t IMP();
    uint8_t IMM();
	uint8_t ZP0();
    uint8_t ZPX();
	uint8_t ZPY();
    uint8_t REL();
	uint8_t ABS();
    uint8_t ABX();
	uint8_t ABY();
    uint8_t IND();
	uint8_t IZX();
    uint8_t IZY();

private:
    //functions for the various opcodes
    uint8_t ADC();
    uint8_t AND();
    uint8_t ASL();
    uint8_t BCC();
	uint8_t BCS();
    uint8_t BEQ();
    uint8_t BIT();
    uint8_t BMI();
	uint8_t BNE();
    uint8_t BPL();
    uint8_t BRK();
    uint8_t BVC();
	uint8_t BVS();
    uint8_t CLC();
    uint8_t CLD();
    uint8_t CLI();
	uint8_t CLV();
    uint8_t CMP();
    uint8_t CPX();
    uint8_t CPY();
	uint8_t DEC();
    uint8_t DEX();
    uint8_t DEY();
    uint8_t EOR();
	uint8_t INC();
    uint8_t INX();
    uint8_t INY();
    uint8_t JMP();
	uint8_t JSR();
    uint8_t LDA();
    uint8_t LDX();
    uint8_t LDY();
	uint8_t LSR();
    uint8_t NOP();
    uint8_t ORA();
    uint8_t PHA();
	uint8_t PHP();
    uint8_t PLA();
    uint8_t PLP();
    uint8_t ROL();
	uint8_t ROR();
    uint8_t RTI();
    uint8_t RTS();
    uint8_t SBC();
	uint8_t SEC();
    uint8_t SED();
    uint8_t SEI();
    uint8_t STA();
	uint8_t STX();
    uint8_t STY();
    uint8_t TAX();
    uint8_t TAY();
	uint8_t TSX();
    uint8_t TXA();
    uint8_t TXS();
    uint8_t TYA();

	//illegal opcodes go here
	uint8_t NONE();
};