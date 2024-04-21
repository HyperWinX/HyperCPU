#include <cpu.hpp>

HyperCPU::_allowed_operand_types HyperCPU::_allowed_op_types[]{
    /* ADC  */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* ADD  */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* AND  */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* ANDN */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* CLC  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    /* INC  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    /* DEC  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    /* HLT  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    /* MOV  */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* PUSH */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    /* POP  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    /* CMP  */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* BSWP */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}
};

int HyperCPU::CPU::_verify_operand_types(HyperCPU::_instruction_t &instruction){
    return _allowed_op_types[static_cast<int>(instruction._instrtp)][static_cast<int>(instruction.args)];
}