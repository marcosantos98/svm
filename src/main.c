#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svm.h"
#include "parser.h"
#include "inst.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)*argv++;
    if (*argv == NULL)
    {
        fprintf(stderr, "ERROR: ./svm <input.svm>\n");
        exit(1);
    }

    char *input_file = *argv++;

    struct SVM svm = {0};

    parse_source(&svm, input_file);

    for (size_t i = 0; i < svm.inst_ptr; i++)
    {
        if (svm.program[i].type == INST_PUSH)
        {
            push_inst(&svm, svm.program[i].op);
        }
        else if (svm.program[i].type == INST_DUP)
        {
            int top = svm.stack[svm.ip - 1];
            svm.stack[svm.ip++] = top;
        }
        else if (svm.program[i].type == INST_DROP)
        {
            (void)pop(&svm);
        }
        else if (svm.program[i].type == INST_PLUS)
        {
            assert_ip_count(svm.ip >= 2, "Stack underflow. PLUS operation requires two values on the stack.");
            int op2 = pop(&svm);
            int op1 = pop(&svm);
            push_inst(&svm, op1 + op2);
        }
        else if (svm.program[i].type == INST_MINUS)
        {
            assert_ip_count(svm.ip >= 2, "Stack underflow. MINUS operation requires two values on the stack.");
            int op2 = pop(&svm);
            int op1 = pop(&svm);
            push_inst(&svm, op2 - op1);
        }
        else if (svm.program[i].type == INST_EQ)
        {
            assert_ip_count(svm.ip >= 2, "Stack underflow. EQUAL operation requires two values on the stack.");
            int op2 = pop(&svm);
            int op1 = pop(&svm);
            push_inst(&svm, op1 == op2 ? 1 : 0);
        }
        else if (svm.program[i].type == INST_LT)
        {
            assert_ip_count(svm.ip >= 2, "Stack underflow. LESS_THEN operation requires two values on the stack.");
            int op2 = pop(&svm);
            int op1 = pop(&svm);
            push_inst(&svm, op1 < op2 ? 1 : 0);
        }
        else if (svm.program[i].type == INST_LTEQ)
        {
            assert_ip_count(svm.ip >= 2, "Stack underflow. LESS_THEN_OR_EQUAL operation requires two values on the stack.");
            int op2 = pop(&svm);
            int op1 = pop(&svm);
            push_inst(&svm, op1 <= op2 ? 1 : 0);
        }
        else if (svm.program[i].type == INST_JMP)
        {
            i = svm.program[i].op - 1;
        }
        else if (svm.program[i].type == INST_JNEQ)
        {
            int top = pop(&svm);
            if (top != 1) 
                i = svm.program[i].op;
        }
        else if (svm.program[i].type == INST_HALT)
        {
            break;
        }
        else if (svm.program[i].type == INST_PRINT)
        {
            int op = pop(&svm);
            printf("stdout:%d\n", op);
        }
        else if (svm.program[i].type == INST_DUMP)
        {
            dump_stack(svm, i);
        }
        else if (svm.program[i].type == INST_DROPALL)
        {
            svm.ip = 0;
        }
    }

    assert_empty_stack(svm);

    return 0;
}