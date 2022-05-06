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

void cpu::reset() {
    //TODO
}
void cpu::interrupt_request() {
    //TODO
}
void cpu::non_mask_interrupt() {
    //TODO
}

void cpu::cpu_clock() {
    
    if(cycles == 0) {
        opcode = cpu_bus_read(pc);
        pc++;
        curr_inst = instruction_by_opcode(opcode);
        set_flag(Unused, true);
        cycles = curr_inst->cycles;
        uint8_t addition_cycle1 = 0x00; //instruction/address mode can impact a cpu cycle
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

        switch (curr_inst->instruction_type)
        {
            case ADCX:
                addition_cycle2 = ADC();
            break;
            case ANDX:
                addition_cycle2 = AND();
            break;
            case ASLX:
                addition_cycle2 = ASL();
            break;
            case BCCX:
                addition_cycle2 = BCC();
            break;
            case BCSX:
                addition_cycle2 = BCS();
            break;
            case BEQX:
                addition_cycle2 = BEQ();
            break;
            case BITX:
                addition_cycle2 = BIT();
            break;
            case BMIX:
                addition_cycle2 = BMI();
            break;
            case BNEX:
                addition_cycle2 = BNE();
            break;
            case BPLX:
                addition_cycle2 = BPL();
            break;
            case BRKX:
                addition_cycle2 = BRK();
            break;
            case BVCX:
                addition_cycle2 = BVC();
            break;
            case BVSX:
                addition_cycle2 = BVS();
            break;
            case CLCX:
                addition_cycle2 = CLC();
            break;
            case CLDX:
                addition_cycle2 = CLD();
            break;
            case CLIX:
                addition_cycle2 = CLI();
            break;
            case CLVX:
                addition_cycle2 = CLV();
            break;
            case CMPX:
                addition_cycle2 = CMP();
            break;
            case CPXX:
                addition_cycle2 = CPX();
            break;
            case CPYX:
                addition_cycle2 = CPY();
            break;
            case DECX:
                addition_cycle2 = DEC();
            break;
            case DEXX:
                addition_cycle2 = DEX();
            break;
            case DEYX:
                addition_cycle2 = DEY();
            break;
            case EORX:
                addition_cycle2 = EOR();
            break;
            case INCX:
                addition_cycle2 = INC();
            break;
            case INXX:
                addition_cycle2 = INX();
            break;
            case INYX:
                addition_cycle2 = INY();
            break;
            case JMPX:
                addition_cycle2 = JMP();
            break;
            case JSRX:
                addition_cycle2 = JSR();
            break;
            case LDAX:
                addition_cycle2 = LDA();
            break;
            case LDXX:
                addition_cycle2 = LDX();
            break;
            case LDYX:
                addition_cycle2 = LDY();
            break;
            case LSRX:
                addition_cycle2 = LSR();
            break;
            case NOPX:
                addition_cycle2 = NOP();
            break;
            case ORAX:
                addition_cycle2 = ORA();
            break;
            case PHAX:
                addition_cycle2 = PHA();
            break;
            case PHPX:
                addition_cycle2 = PHP();
            break;
            case PLAX:
                addition_cycle2 = PLA();
            break;
            case PLPX:
                addition_cycle2 = PLP();
            break;
            case ROLX:
                addition_cycle2 = ROL();
            break;
            case RORX:
                addition_cycle2 = ROR();
            break;
            case RTIX:
                addition_cycle2 = RTI();
            break;
            case RTSX:
                addition_cycle2 = RTS();
            break;
            case SBCX:
                addition_cycle2 = SBC();
            break;
            case SECX:
                addition_cycle2 = SEC();
            break;
            case SEDX:
                addition_cycle2 = SED();
            break;
            case SEIX:
                addition_cycle2 = SEI();
            break;
            case STAX:
                addition_cycle2 = STA();
            break;
            case STXX:
                addition_cycle2 = STX();
            break;
            case STYX:
                addition_cycle2 = STY();
            break;
            case TAXX:
                addition_cycle2 = TAX();
            break;
            case TAYX:
                addition_cycle2 = TAY();
            break;
            case TSXX:
                addition_cycle2 = TSX();
            break;
            case TXAX:
                addition_cycle2 = TXA();
            break;
            case TXSX:
                addition_cycle2 = TXS();
            break;
            case TYAX:
                addition_cycle2 = TYA();
            break;
            case XXXX:
                addition_cycle2 = NONE();
            break;
            default:
                printf("Unknown Instruction: %s\n", curr_inst->name.c_str());
                exit(-7);
            break;
        }
        cycles += (addition_cycle1 & addition_cycle2);
        set_flag(Unused, true);
        clock_count++;
    }
    cycles--;

}

//----------------------------------------ADDRESSING MODES----------------------------------------//
uint8_t cpu::IMP() {
    //no additional data required
    //set the fetched value to value from the accumulator
    fetched = accu;
    return 0;
}
uint8_t cpu::IMM() {
    // The instruction expects the next byte to be used as a value, so we'll prep
    // the read address to point to the next byte
    addr_abs = pc++;
    return 0;
}
uint8_t cpu::ZP0() {
    //operand is zeropage address (hi-byte is zero, address = $00LL)
    addr_abs = cpu_bus_read(pc);	
	pc++;
	addr_abs &= 0x00FF;
    return 0;
}
uint8_t cpu::ZPX() {
    //operand is zeropage address; effective address is address incremented by X without carry
    addr_abs = cpu_bus_read(pc + x_reg);	
	pc++;
	addr_abs &= 0x00FF;
    return 0;
}
uint8_t cpu::ZPY() {
    //operand is zeropage address; effective address is address incremented by Y without carry
    addr_abs = cpu_bus_read(pc + y_reg);	
	pc++;
	addr_abs &= 0x00FF;
    return 0;
}
uint8_t cpu::REL() {
    //branch target is PC + signed offset BB
    addr_rel = cpu_bus_read(pc);
	pc++;
	if (addr_rel & 0x80)
		addr_rel |= 0xFF00;
    return 0;
}
uint8_t cpu::ABS() {
    //full 16 bit address
    uint16_t lo = cpu_bus_read(pc);
	pc++;
	uint16_t hi = cpu_bus_read(pc);
	pc++;
	addr_abs = (hi << 8) | lo;
    return 0;
}
uint8_t cpu::ABX() {
    //operand is address; effective address is address incremented by X **with** carry
    //an additional clock cycle may be required if content changes
    uint16_t lo = cpu_bus_read(pc);
	pc++;
	uint16_t hi = cpu_bus_read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += x_reg;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}
uint8_t cpu::ABY() {
    uint16_t lo = cpu_bus_read(pc);
	pc++;
	uint16_t hi = cpu_bus_read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += y_reg;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}
uint8_t cpu::IND() {
    //indirect
	uint16_t ptr_lo = cpu_bus_read(pc);
	pc++;
	uint16_t ptr_hi = cpu_bus_read(pc);
	pc++;

	uint16_t ptr = (ptr_hi << 8) | ptr_lo;

    //hardware bug
	if (ptr_lo == 0x00FF) { 
		addr_abs = (cpu_bus_read(ptr & 0xFF00) << 8) | cpu_bus_read(ptr + 0);
	}
    //normal behavoir
	else {
		addr_abs = (cpu_bus_read(ptr + 1) << 8) | cpu_bus_read(ptr + 0);
	}
	
	return 0;
}
uint8_t cpu::IZX() {
    //indirect with x reg offset
    uint16_t t = cpu_bus_read(pc);
	pc++;

	uint16_t lo = cpu_bus_read((uint16_t)(t + (uint16_t)x_reg) & 0x00FF);
	uint16_t hi = cpu_bus_read((uint16_t)(t + (uint16_t)x_reg + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
    return 0;
}
uint8_t cpu::IZY() {
    //indirect with x reg offset
    //addititional clock cycle required upon content change
    uint16_t t = cpu_bus_read(pc);
	pc++;

	uint16_t lo = cpu_bus_read(t & 0x00FF);
	uint16_t hi = cpu_bus_read((t + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	addr_abs += y_reg;
	
	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

//----------------------------------------INSTRUCTIONS----------------------------------------//
uint8_t cpu::ADC() {
    //add with carry
    // Grab the data that we are adding to the accumulator
	fetch();
	
	// Add is performed in 16-bit domain for emulation to capture any
	// carry bit, which will exist in bit 8 of the 16-bit word
	temp = (uint16_t)accu + (uint16_t)fetched + (uint16_t)get_flag(Carry);
	
	// The carry flag out exists in the high byte bit 0
	set_flag(Carry, temp > 255);
	
	// The Zero flag is set if the result is 0
	set_flag(Zero, (temp & 0x00FF) == 0);
	
	// The signed Overflow flag is set based on all that up there! :D
	set_flag(Overflow, (~((uint16_t)accu ^ (uint16_t)fetched) & ((uint16_t)accu ^ (uint16_t)temp)) & 0x0080);
	
	// The negative flag is set to the most significant bit of the result
	set_flag(Negative, temp & 0x80);
	
	// Load the result into the accumulator (it's 8-bit dont forget!)
	accu = temp & 0x00FF;
	
	// This instruction has the potential to require an additional clock cycle
	return 1;
}
uint8_t cpu::AND() {
    //LOGICAL AND on accumulator and fetched data
    fetch();
	accu = accu & fetched;
	set_flag(Zero, accu == 0x00);
	set_flag(Negative, accu & 0x80);
	return 1;
}
uint8_t cpu::ASL() {
    //bit shift left
    fetch();
	temp = (uint16_t)fetched << 1;
	set_flag(Carry, (temp & 0xFF00) > 0);
	set_flag(Zero, (temp & 0x00FF) == 0x00);
	set_flag(Negative, temp & 0x80);
	if (curr_inst->addr_mode == IMPX)
		accu = temp & 0x00FF;
	else
		cpu_bus_write(addr_abs, temp & 0x00FF);
	return 0;
}
uint8_t cpu::BCC() {
    //branch if carry clear
    if(get_flag(Carry) == 0) {
        cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
    }
    return 0;
}
uint8_t cpu::BCS() {
    //branch if carry bit is set
    if(get_flag(Carry) == 1) {
        cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
    }
    return 0;
}
uint8_t cpu::BEQ() {
    //branch if equal
    if (get_flag(Zero) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
    return 0;
}
uint8_t cpu::BIT() {
    fetch();
	temp = accu & fetched;
	set_flag(Zero, (temp & 0x00FF) == 0x00);
	set_flag(Negative, fetched & (1 << 7));
	set_flag(Overflow, fetched & (1 << 6));
    return 0;
}
uint8_t cpu::BMI() {
    //branch if negative
    if (get_flag(Negative) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
    return 0;
}
uint8_t cpu::BNE() {
    //branch if not equal
    if (get_flag(Zero) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
    return 0;
}
uint8_t cpu::BPL() {
    //branch if positive
    if (get_flag(Negative) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
    return 0;
}
uint8_t cpu::BRK() {
    //break
    pc++;
	
	set_flag(Disable_Interrupts, 1);
	cpu_bus_write(0x0100 + sp, (pc >> 8) & 0x00FF);
	sp--;
	cpu_bus_write(0x0100 + sp, pc & 0x00FF);
	sp--;

	set_flag(Break, 1);
	cpu_bus_write(0x0100 + sp, status);
	sp--;
	set_flag(Break, 0);

	pc = (uint16_t)cpu_bus_read(0xFFFE) | ((uint16_t)cpu_bus_read(0xFFFF) << 8);
    return 0;
}
uint8_t cpu::BVC() {
    //branch if overflow clear
    if (get_flag(Overflow) == 0)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
    return 0;
}
uint8_t cpu::BVS() {
    //branch if overflow set
    if (get_flag(Overflow) == 1)
	{
		cycles++;
		addr_abs = pc + addr_rel;

		if ((addr_abs & 0xFF00) != (pc & 0xFF00))
			cycles++;

		pc = addr_abs;
	}
    return 0;
}
uint8_t cpu::CLC() {
    //clears the carry flag
    set_flag(Carry, false);
    return 0;
}
uint8_t cpu::CLD() {
    //clears the decimal flag
    set_flag(Decimal, false);
    return 0;
}
uint8_t cpu::CLI() {
    //clears interrupt flag
    set_flag(Disable_Interrupts, false);
    return 0;
}
uint8_t cpu::CLV() {
    //clears overflow flag
    set_flag(Overflow, false);
    return 0;
}
uint8_t cpu::CMP() {
    // Instruction: Compare Accumulator
    // Function:    C <- A >= M      Z <- (A - M) == 0
    // Flags Out:   N, C, Z
    fetch();
	temp = (uint16_t)accu - (uint16_t)fetched;
	set_flag(Carry, accu >= fetched);
	set_flag(Zero, (temp & 0x00FF) == 0x0000);
	set_flag(Negative, temp & 0x0080);
    return 1;
}
uint8_t cpu::CPX() {
    //compare X register
    fetch();
	temp = (uint16_t)x_reg - (uint16_t)fetched;
	set_flag(Carry, x_reg >= fetched);
	set_flag(Zero, (temp & 0x00FF) == 0x0000);
	set_flag(Negative, temp & 0x0080);
	return 0;
}
uint8_t cpu::CPY() {
    //compare Y register
    fetch();
	temp = (uint16_t)y_reg - (uint16_t)fetched;
	set_flag(Carry, y_reg >= fetched);
	set_flag(Zero, (temp & 0x00FF) == 0x0000);
	set_flag(Negative, temp & 0x0080);
    return 0;
}
uint8_t cpu::DEC() {
    //decrement value at memory location
    fetch();
	temp = fetched - 1;
	cpu_bus_write(addr_abs, temp & 0x00FF);
	set_flag(Zero, (temp & 0x00FF) == 0x0000);
	set_flag(Negative, temp & 0x0080);
    return 0;
}
uint8_t cpu::DEX() {
    //decrement x register
    x_reg--;
	set_flag(Zero, x_reg == 0x00);
	set_flag(Negative, x_reg & 0x80);
    return 0;
}
uint8_t cpu::DEY() {
    y_reg--;
	set_flag(Zero, y_reg == 0x00);
	set_flag(Negative, y_reg & 0x80);
    return 0;
}
uint8_t cpu::EOR() {
    //bitwise logic XOR
    fetch();
	accu = accu ^ fetched;	
	set_flag(Zero, accu == 0x00);
	set_flag(Negative, accu & 0x80);
	return 1;
}
uint8_t cpu::INC() {
    //Increment data in memory
    fetch();
	temp = fetched + 1;
	cpu_bus_write(addr_abs, temp & 0x00FF);
	set_flag(Zero, (temp & 0x00FF) == 0x0000);
	set_flag(Negative, temp & 0x0080);
    return 0;
}
uint8_t cpu::INX() {
    //increment x reg
    x_reg++;
	set_flag(Zero, x_reg == 0x00);
	set_flag(Negative, x_reg & 0x80);
    return 0;
}
uint8_t cpu::INY() {
    //increment y_reg
    y_reg++;
	set_flag(Zero, y_reg == 0x00);
	set_flag(Negative, y_reg & 0x80);
    return 0;
}
uint8_t cpu::JMP() {
    //jump to location
    pc = addr_abs;
    return 0;
}
uint8_t cpu::JSR(){
    return 0;
    //TODO:
}
uint8_t cpu::LDA(){
    return 0;
    //TODO:
}
uint8_t cpu::LDX(){
    return 0;
    //TODO:
}
uint8_t cpu::LDY(){
    return 0;
    //TODO:
}
uint8_t cpu::LSR(){
    return 0;
    //TODO:
}
uint8_t cpu::NOP() {
    // Sadly not all NOPs are equal, added a few here
	// based on https://wiki.nesdev.com/w/index.php/CPU_unofficial_opcodes
	switch (opcode) {
	case 0x1C:
	case 0x3C:
	case 0x5C:
	case 0x7C:
	case 0xDC:
	case 0xFC:
		return 1;
		break;
	}
	return 0;
}
uint8_t cpu::ORA() {
    //logic OR
    fetch();
	accu = accu | fetched;
	set_flag(Zero, accu == 0x00);
	set_flag(Negative, accu & 0x80);
	return 1;
}
uint8_t cpu::PHA() {
    //pushes accumulator to the stack
    cpu_bus_write(0x0100 + sp, accu);
	sp--;
    return 0;
}
uint8_t cpu::PHP() {
    //push status register to stack
    cpu_bus_write(0x0100 + sp, status | Break | Unused);
	set_flag(Break, 0);
	set_flag(Unused, 0);
	sp--;
    return 0;
}
uint8_t cpu::PLA() {
    //POP accumulator off stack
    sp++;
	accu = cpu_bus_read(0x0100 + sp);
	set_flag(Zero, accu == 0x00);
	set_flag(Negative, accu & 0x80);
    return 0;
}
uint8_t cpu::PLP() {
    //pop status register off stack
    sp++;
	status = cpu_bus_read(0x0100 + sp);
	set_flag(Unused, 1);
	return 0;
}
uint8_t cpu::ROL(){
    return 0;
    //TODO:
}
uint8_t cpu::ROR(){
    return 0;
    //TODO:
}
uint8_t cpu::RTI(){
    return 0;
    //TODO:
}
uint8_t cpu::RTS(){
    return 0;
    //TODO:
}
uint8_t cpu::SBC() {
    fetch();
	
	// Operating in 16-bit domain to capture carry out
	
	// We can invert the bottom 8 bits with bitwise xor
	uint16_t value = ((uint16_t)fetched) ^ 0x00FF;
	
	// Notice this is exactly the same as addition from here!
	temp = (uint16_t)accu + value + (uint16_t)get_flag(Carry);
	set_flag(Carry, temp & 0xFF00);
	set_flag(Zero, ((temp & 0x00FF) == 0));
	set_flag(Overflow, (temp ^ (uint16_t)accu) & (temp ^ value) & 0x0080);
	set_flag(Negative, temp & 0x0080);
	accu = temp & 0x00FF;
	return 1;
}
uint8_t cpu::SEC() {
    //sets carry flag
    set_flag(Carry, true);
    return 0;
}
uint8_t cpu::SED() {
    //sets decimal flag
    set_flag(Decimal, true);
    return 0;
}
uint8_t cpu::SEI() {
    //sets interrupt flag
    set_flag(Disable_Interrupts, true);
    return 0;
}
uint8_t cpu::STA(){
    return 0;
    //TODO:
}
uint8_t cpu::STX(){
    return 0;
    //TODO:
}
uint8_t cpu::STY(){
    return 0;
    //TODO:
}
uint8_t cpu::TAX(){
    return 0;
    //TODO:
}
uint8_t cpu::TAY(){
    return 0;
    //TODO:
}
uint8_t cpu::TSX(){
    return 0;
    //TODO:
}
uint8_t cpu::TXA(){
    return 0;
    //TODO:
}
uint8_t cpu::TXS(){
    return 0;
    //TODO:
}
uint8_t cpu::TYA(){
    return 0;
    //TODO:
}
uint8_t cpu::NONE() {
    return 0;
}

uint8_t cpu::fetch()
{
	if (!(curr_inst->addr_mode == IMPX))
		fetched = cpu_bus_read(addr_abs);
	return fetched;
}

bool cpu::complete()
{
	return cycles == 0;
}

void cpu::set_flag(cpu_flags flags, bool v) {
    if (v) {
        status = status | flags;
    }
    else {
        status = status & ~flags;
    }
}

uint8_t cpu::get_flag(cpu_flags flags) {
    //returns the specific bit needed from the status register based on the cpu flag
    return ((status & flags) > 0) ? 1 : 0;
}

//returns the instruction from the table via the opcode
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