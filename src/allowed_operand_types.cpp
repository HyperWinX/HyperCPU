#include <cpu.hpp>

uint8_t HyperCPU::allowed_op_types[][14]{
    /*             RM_R */
    /*                R_RM */
    /*                   RM_IMM */
    /*                      R_IMM */
    /*                         RM_M */
    /*                            R_M */
    /*                               M_R */
    /*                                  M_RM */
    /*                                     R_R */
    /*                                        R */
    /*                                           M */
    /*                                              IMM */
    /*                                                 NOARG */
    /* ADC  */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* ADD  */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* AND  */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* ANDN */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* CALL */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    /* CLC  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    /* INC  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    /* DEC  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    /* HLT  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    /* MOV  */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* PUSH */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    /* POP  */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    /* CMP  */ {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    /* BSWP */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}
};

uint8_t HyperCPU::CPU::verify_operand_types(HyperCPU::instruction_t &instruction){
    return allowed_op_types[static_cast<int>(instruction._instrtp)][static_cast<int>(instruction.args)];
}