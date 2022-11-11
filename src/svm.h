#ifndef SVM_H
#define SVM_H

#include <stdbool.h>

#include "inst.h"

#define MAX_STACK_SIZE 2048
#define MAX_INSTRUCTIONS_SIZE 100
#define MAX_MEM_SPOTS 6
#define MEM_SPACE 496

typedef struct SVM
{
    size_t ip;
    int stack[MAX_STACK_SIZE];
    size_t inst_ptr;
    Instruction program[MAX_INSTRUCTIONS_SIZE];
    int mems[MAX_MEM_SPOTS];
    char memory_space[MEM_SPACE];
    int mem_ptr;   
} SVM;

void assert_empty_stack(SVM);
void assert_ip_count(bool, const char *);
void assert_valid_mem_spot(int);
void push_inst(SVM *, int);
int pop(SVM *);
void dump_stack(SVM, int);
void add_instruction(SVM *, Instruction);
void set_mem(SVM *, int, int);
int get_mem(SVM, int);
int save_string_literal(SVM *, const char *);
void read_string_literal(SVM *, int, char **);
void dump_memory(const SVM*);

#endif