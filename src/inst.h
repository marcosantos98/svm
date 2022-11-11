#ifndef INST_H
#define INST_H

#define EQUAL (Instruction){.type = INST_EQ, .op = 0}
#define NEQUAL (Instruction){.type = INST_NEQ, .op = 0}

#define LT (Instruction){ .type = INST_LT, .op = 0 }
#define LTEQ (Instruction){ .type = INST_LTEQ, .op = 0 }
#define GT (Instruction){ .type = INST_GT, .op = 0 }
#define GTEQ (Instruction){ .type = INST_GTEQ, .op = 0 }

#define PLUS (Instruction){.type = INST_PLUS, .op = 0}
#define MINUS (Instruction){.type = INST_MINUS, .op = 0}
#define MULT (Instruction){.type = INST_MULT, .op = 0}
#define DIV (Instruction){.type = INST_DIV, .op = 0}
#define MOD (Instruction){.type = INST_MOD, .op = 0}

#define PUSH(operand) (Instruction){.type = INST_PUSH, .op = operand}
#define HALT (Instruction){.type = INST_HALT, .op = 0}
#define JMP(addr) (Instruction){.type = INST_JMP, .op = addr}
#define JNEQ(addr) (Instruction){.type = INST_JNEQ, .op = addr }
#define DUP (Instruction){.type = INST_DUP, .op = 0}
#define DROP (Instruction){.type = INST_DROP, .op = 0}

#define PRINT (Instruction){.type = INST_PRINT, .op = 0}
#define PRINTS (Instruction){.type = INST_PRINTS, .op = 0}
#define DUMP (Instruction){.type = INST_DUMP, .op = 0}
#define DROPALL (Instruction){.type = INST_DROPALL, .op = 0}

#define MEMSET(operand) (Instruction){.type = INST_MEMSET, .op = operand}
#define MEMGET(operand) (Instruction){.type = INST_MEMGET, .op = operand}

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
    INST_PRINTS,
    INST_DUMP,
    INST_MEMSET,
    INST_MEMGET,
};

typedef struct Instruction {
    enum InstType type;
    int op;
} Instruction;

const char* inst_to_str(int);

#endif