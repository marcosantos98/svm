#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svm.h"

void assert_ip_count(bool cond, const char *msg)
{
    if (!cond)
    {
        printf("Error: %s [assert_ip_count]\n", msg);
        exit(1);
    }
}

void assert_empty_stack(struct SVM svm)
{
    if (svm.ip != 0)
    {
        printf("Error: Stack is not empty. Make sure you consume everthing on the stack. [assert_empty_stack]\n");
        dump_stack(svm, 0);
    }
}

void assert_valid_mem_spot(int spot)
{
    if (spot > MAX_MEM_SPOTS || spot < 0)
    {
        printf("Error: Given memory spot isn't valid. Spot need to be > 0 && < %d [assert_valid_mem_spot]\n", MAX_MEM_SPOTS);
        exit(1);
    }
}

void push_inst(struct SVM *svm, int operand)
{
    svm->stack[svm->ip++] = operand;
}

int pop(struct SVM *svm)
{
    int op = svm->stack[svm->ip - 1];
    svm->ip--;
    return op;
}

void dump_stack(struct SVM svm, int ip)
{
    printf("Current stack at %d:\n", ip);
    for (size_t i = 0; i < svm.ip; i++)
    {
        printf("\tIP: %ld = %i\n", i, svm.stack[i]);
    }
}

void add_instruction(struct SVM *svm, struct Instruction inst)
{
    svm->program[svm->inst_ptr++] = inst;
}

void set_mem(struct SVM *svm, int index, int value)
{
    svm->mems[index] = value;
}

int get_mem(struct SVM svm, int index)
{
    return svm.mems[index];
}