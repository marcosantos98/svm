#ifndef INST_H
#define INST_H

#define EQUAL (struct Instruction){.type = INST_EQ, .op = 0}
#define NEQUAL (struct Instruction){.type = INST_NEQ, .op = 0}

#define LT (struct Instruction){ .type = INST_LT, .op = 0 }
#define LTEQ (struct Instruction){ .type = INST_LTEQ, .op = 0 }
#define GT (struct Instruction){ .type = INST_GT, .op = 0 }
#define GTEQ (struct Instruction){ .type = INST_GTEQ, .op = 0 }

#define PLUS (struct Instruction){.type = INST_PLUS, .op = 0}
#define MINUS (struct Instruction){.type = INST_MINUS, .op = 0}
#define MULT (struct Instruction){.type = INST_MULT, .op = 0}
#define DIV (struct Instruction){.type = INST_DIV, .op = 0}
#define MOD (struct Instruction){.type = INST_MOD, .op = 0}

#define PUSH(operand) (struct Instruction){.type = INST_PUSH, .op = operand}
#define HALT (struct Instruction){.type = INST_HALT, .op = 0}
#define JMP(addr) (struct Instruction){.type = INST_JMP, .op = addr}
#define JNEQ(addr) (struct Instruction){.type = INST_JNEQ, .op = addr }
#define DUP (struct Instruction){.type = INST_DUP, .op = 0}
#define DROP (struct Instruction){.type = INST_DROP, .op = 0}

#define PRINT (struct Instruction){.type = INST_PRINT, .op = 0}
#define DUMP (struct Instruction){.type = INST_DUMP, .op = 0}
#define DROPALL (struct Instruction){.type = INST_DROPALL, .op = 0}

#define MEMSET(operand) (struct Instruction){.type = INST_MEMSET, .op = operand}
#define MEMGET(operand) (struct Instruction){.type = INST_MEMGET, .op = operand}

enum InstType {
    INST_NOP = 0,
    INST_HALT,
    INST_PUSH,
    INST_DUP,
    INST_PLUS,
    INST_MINUS,
    INST_MULT,
    INST_DIV,
    INST_MOD,
    INST_EQ,
    INST_NEQ,
    INST_LT,
    INST_LTEQ,
    INST_GT,
    INST_GTEQ,
    INST_JMP,
    INST_JNEQ,
    INST_DROP,
    INST_DROPALL,
    INST_PRINT,
    INST_DUMP,
    INST_MEMSET,
    INST_MEMGET,
};

struct Instruction {
    enum InstType type;
    int op;
};

const char* inst_to_str(int);

#endif