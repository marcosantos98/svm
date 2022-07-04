#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svm.h"
#include "inst.h"

void assert_ip_count(bool cond, const char* msg) {
    if(!cond) {
        printf("Error: %s [assert_ip_count]\n", msg);
        exit(1);
    } 
}

void assert_empty_stack(struct SVM svm) {
    if(svm.ip != 0) {
        printf("Error: Stack is not empty. Make sure you consume everthing on the stack. [assert_empty_stack]\n");
        dump_stack(svm);
    }
}

void push_inst(struct SVM *svm, int operand) {
    svm->stack[svm->ip++] = operand;
}

int pop(struct SVM *svm) {
    int op = svm->stack[svm->ip-1];
    svm->ip--;
    return op;
}

void dump_stack(struct SVM svm) {
    printf("Current stack:\n");
    for(size_t i  = 0; i < svm.ip; i++) {
        printf("\tIP: %ld = %i\n", i, svm.stack[i]);
    }
}