#ifndef SVM_H
#define SVM_H

#include <stdbool.h>

#define MAX_STACK_SIZE 2048

struct SVM
{
    size_t ip;
    int stack[2048];
};

void assert_empty_stack(struct SVM);
void assert_ip_count(bool, const char*);
void push_inst(struct SVM *, int);
int pop(struct SVM *);
void dump_stack(struct SVM);

#endif