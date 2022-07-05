#include "inst.h"

const char* inst_to_str(int inst){
    switch(inst){
        case INST_NOP: return "NOP";
        case INST_HALT: return "HALT";
        case INST_PUSH: return "PUSH";
        case INST_DUP: return "DUP";
        case INST_PLUS: return "PLUS";
        case INST_MINUS: return "MINUS";
        case INST_EQ: return "EQUAL";
        case INST_NEQ: return "NOTEQUAL";
        case INST_JMP: return "JUMP";
        case INST_JNEQ: return "JNEQ";
        case INST_LT: return "LT";
        case INST_LTEQ: return "LTEQ";
        case INST_GT: return "GT";
        case INST_GTEQ: return "GTEQ";
        case INST_DROP: return "DROP";
        case INST_DROPALL: return "DROPALL";
        case INST_PRINT: return "PRINT";
        case INST_DUMP: return "DUMP";
        default:
            return "Unreachable";
    }
}