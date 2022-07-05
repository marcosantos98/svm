#ifndef SVM_H
#define SVM_H

#include <stdbool.h>

#include "inst.h"

#define MAX_STACK_SIZE 2048
#define MAX_INSTRUCTIONS_SIZE 100

struct SVM
{
    size_t ip;
    int stack[MAX_STACK_SIZE];
    size_t inst_ptr;
    struct Instruction program[MAX_INSTRUCTIONS_SIZE];
};

void assert_empty_stack(struct SVM);
void assert_ip_count(bool, const char*);
void push_inst(struct SVM *, int);
int pop(struct SVM *);
void dump_stack(struct SVM, int);

#endif