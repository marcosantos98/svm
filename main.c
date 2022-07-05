#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#include "svm.h"
#include "inst.h"

#define MAX_INSTRUCTIONS 100

struct Instruction program[MAX_INSTRUCTIONS];

void read_file_to_buf(const char *filename, char **buf)
{
    FILE *program = fopen(filename, "r");
    if (program == NULL)
    {
        fprintf(stderr, "ERROR: Couldn't open the file %s. Reason: %s\n", filename, strerror(errno));
        fclose(program);
        exit(1);
    }

    if (fseek(program, 0L, SEEK_END) == -1)
    {
        fprintf(stderr, "ERROR: %s\n", strerror(errno));
        fclose(program);
        exit(1);
    }

    long len = ftell(program);
    if (len == -1)
    {
        fprintf(stderr, "ERROR: %s\n", strerror(errno));
        fclose(program);
        exit(1);
    }

    if (fseek(program, 0L, SEEK_SET) == -1)
    {
        fprintf(stderr, "ERROR: %s\n", strerror(errno));
        fclose(program);
        exit(1);
    }

    *buf = malloc(sizeof(char) * (len + 1));

    if (fread(*buf, sizeof(char), len, program) == 0)
    {
        if (ferror(program))
        {
            fprintf(stderr, "ERROR: %s\n", strerror(errno));
            fclose(program);
            exit(1);
        }
        else if (feof(program))
        {
            fprintf(stderr, "ERROR: Reached end of file!\n");
            fclose(program);
            exit(1);
        }
    }

    buf[len + 1] = '\0';

    // This can also fail, but do I care?
    fclose(program);
}

void str_to_lower(char *str) {
    for(size_t i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}

void read_file_into_program(const char *filename)
{

    char *buf = NULL;
    read_file_to_buf(filename, &buf);

    char *ptr = strtok(buf, " \n");

    size_t inst_cnt;
    while (ptr != NULL)
    {
        str_to_lower(ptr);
        if (strcmp(ptr, "push") == 0)
        {
            ptr = strtok(NULL, " \n");
            program[inst_cnt++] = (struct Instruction)PUSH(atoi(ptr));
        }
        else if (strcmp(ptr, "plus") == 0)
        {
            program[inst_cnt++] = (struct Instruction)PLUS;
        }
        else if (strcmp(ptr, "print") == 0)
        {
            program[inst_cnt++] = (struct Instruction)PRINT;
        }
        else {
            fprintf(stderr, "ERROR: Unexpected instruction.\n");
        }
        ptr = strtok(NULL, " \n");
    }

    free(buf);
}

int main(int argc, char **argv)
{
    (void)argc;

    (void)*argv++;
    if(*argv == NULL) {
        fprintf(stderr, "ERROR: ./svm <input.svm>\n");
        exit(1);
    }

    char *input_file = *argv++;

    read_file_into_program(input_file);
    
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