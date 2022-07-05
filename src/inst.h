#ifndef INST_H
#define INST_H

#define EQUAL {.type = INST_EQ, .op = 0}
#define LT { .type = INST_LT, .op = 0 }
#define LTEQ { .type = INST_LTEQ, .op = 0 }
#define PLUS {.type = INST_PLUS, .op = 0}
#define MINUS {.type = INST_MINUS, .op = 0}
#define PUSH(operand) {.type = INST_PUSH, .op = operand}
#define HALT {.type = INST_HALT, .op = 0}
#define JMP(addr) {.type = INST_JMP, .op = addr}
#define JNEQ(addr) {.type = INST_JNEQ, .op = addr }
#define DUP {.type = INST_DUP, .op = 0}
#define DROP {.type = INST_DROP, .op = 0}

#define PRINT {.type = INST_PRINT, .op = 0}
#define DUMP {.type = INST_DUMP, .op = 0}
#define DROPALL {.type = INST_DROPALL, .op = 0}

enum InstType {
    INST_NOP = 0,
    INST_HALT,
    INST_PUSH,
    INST_DUP,
    INST_PLUS,
    INST_MINUS,
    INST_EQ,
    INST_LT,
    INST_LTEQ,
    INST_JMP,
    INST_JNEQ,
    INST_DROP,
    INST_DROPALL,
    INST_PRINT,
    INST_DUMP,
};

struct Instruction {
    enum InstType type;
    int op;
};

const char* inst_to_str(int);

#endif