#ifndef SVM_H
#define SVM_H

#include <stdbool.h>

#include "inst.h"

#define MAX_STACK_SIZE 2048
#define MAX_INSTRUCTIONS_SIZE 100
#define MAX_MEM_SPOTS 6
#define MEM_SPACE 496

typedef char byte;

struct SVM
{
    size_t ip;
    int stack[MAX_STACK_SIZE];
    size_t inst_ptr;
    struct Instruction program[MAX_INSTRUCTIONS_SIZE];
    int mems[MAX_MEM_SPOTS];
    byte memory_space[MEM_SPACE];
    int mem_ptr;   
};

void assert_empty_stack(struct SVM);
void assert_ip_count(bool, const char *);
void assert_valid_mem_spot(int);
void push_inst(struct SVM *, int);
int pop(struct SVM *);
void dump_stack(struct SVM, int);
void add_instruction(struct SVM *, struct Instruction);
void set_mem(struct SVM *, int, int);
int get_mem(struct SVM, int);
int save_string_literal(struct SVM *, const char *);
void read_string_literal(struct SVM *, int, char **);
void dump_memory(const struct SVM*);

#endif