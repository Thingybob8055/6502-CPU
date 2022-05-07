#include <cstdint>
#include <string>

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

typedef struct instruction{
    std::string name;
    in_type instruction_type;
    address_mode addr_mode;
    uint8_t cycles;
} Instruction;

Instruction curr_inst;
Instruction instruction_by_opcode(uint8_t code);