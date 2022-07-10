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

int save_string_literal(struct SVM *svm, const char *str)
{
    int start = svm->mem_ptr;
    size_t len = strlen(str);

    if(str[len - 1] != '"') {
        printf("ERROR: Unclosed string! %c\n", str[len - 1]);
        exit(1);
    }

    for (size_t i = 1; i < len - 1; i++)
    {
        svm->memory_space[svm->mem_ptr++] = str[i];
    }
    svm->mem_ptr++; //Advance the null terminator.
    return start;
}

void read_string_literal(struct SVM *svm, int ptr, char **buf)
{
    size_t len = 0;
    while (svm->memory_space[ptr + len] != '\0' && len < MEM_SPACE)
    {
        len++;
    }

    *buf = malloc(sizeof(char) * len + 1);

    for (size_t i = 0; i < len; i++)
    {
        memset(*buf + i, svm->memory_space[ptr + i], sizeof(char));
    }

    memset(*buf + len, '\0', sizeof(char));
}

void dump_memory(const struct SVM *svm)
{
    for (int i = 0; i < MEM_SPACE;)
    {
        for (int j = 0; j < 16; j++)
        {
            printf("%02x ", svm->memory_space[i]);
            i++;
        }
        printf("\n");
    }
    printf("\n");
}