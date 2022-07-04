#include <stdio.h>
#include <stdlib.h>

#include "svm.h"
#include "inst.h"

#define MAX_INSTRUCTIONS 100

struct Instruction program[MAX_INSTRUCTIONS] = {
    PUSH(0), //0
    PRINT, //empty
    PUSH(1), //1
    DUP, //1, 1
    PUSH(10), //1, 1, 10
    LTEQ, //1, 1
    JNEQ(12), //DROPALL
    DUP, //1, 1
    PRINT, //1
    DUP, //1, 1
    PUSH(1), //1, 1, 1
    PLUS, //1, 2
    JMP(3), //goto first dup
    DROPALL, //Hacky way to clean the stack at the end xd
    HALT,
};

int main(void)
{
    struct SVM svm = {0};

    for (size_t i = 0; i < MAX_INSTRUCTIONS; i++)
    {
        if (program[i].type == INST_PUSH)
        {
            push_inst(&svm, program[i].op);
        }
        else if (program[i].type == INST_DUP)
        {
            int top = svm.stack[svm.ip - 1];
            svm.stack[svm.ip++] = top;
        }
        else if (program[i].type == INST_DROP)
        {
            (void)pop(&svm);
        }
        else if (program[i].type == INST_PLUS)
        {
            assert_ip_count(svm.ip >= 2, "Stack underflow. PLUS operation requires two values on the stack.");
            int op2 = pop(&svm);
            int op1 = pop(&svm);
            push_inst(&svm, op1 + op2);
        }
        else if (program[i].type == INST_MINUS)
        {
            assert_ip_count(svm.ip >= 2, "Stack underflow. MINUS operation requires two values on the stack.");
            int op2 = pop(&svm);
            int op1 = pop(&svm);
            push_inst(&svm, op2 - op1);
        }
        else if (program[i].type == INST_EQ)
        {
            assert_ip_count(svm.ip >= 2, "Stack underflow. EQUAL operation requires two values on the stack.");
            int op2 = pop(&svm);
            int op1 = pop(&svm);
            push_inst(&svm, op1 == op2 ? 1 : 0);
        }
        else if (program[i].type == INST_LT)
        {
            assert_ip_count(svm.ip >= 2, "Stack underflow. LESS_THEN operation requires two values on the stack.");
            int op2 = pop(&svm);
            int op1 = pop(&svm);
            push_inst(&svm, op1 < op2 ? 1 : 0);
        }
        else if (program[i].type == INST_LTEQ)
        {
            assert_ip_count(svm.ip >= 2, "Stack underflow. LESS_THEN_OR_EQUAL operation requires two values on the stack.");
            int op2 = pop(&svm);
            int op1 = pop(&svm);
            push_inst(&svm, op1 <= op2 ? 1 : 0);
        }
        else if (program[i].type == INST_JMP)
        {
            i = program[i].op - 1;
        }
        else if (program[i].type == INST_JNEQ)
        {
            int top = pop(&svm);
            if (top != 1)
                i = program[i].op;
        }
        else if (program[i].type == INST_HALT)
        {
            break;
        }
        else if (program[i].type == INST_PRINT)
        {
            int op = pop(&svm);
            printf("%d\n", op);
        }
        else if (program[i].type == INST_DUMP)
        {
            dump_stack(svm);
        }
        else if (program[i].type == INST_DROPALL)
        {
            svm.ip = 0;
        }
    }

    assert_empty_stack(svm);

    return 0;
}