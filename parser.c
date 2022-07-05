#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "parser.h"
#include "inst.h"

void load_file(const char *filename, char **buf)
{
    FILE *program = fopen(filename, "r");
    if (program == NULL)
    {
        fprintf(stderr, "ERROR: Couldn't open the file %s. Reason: %s\n", filename, strerror(errno));
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

void parse_source(struct SVM *svm, const char *filename)
{

    char *buf = NULL;
    load_file(filename, &buf);

    char *ptr = strtok(buf, " \n");

    while (ptr != NULL)
    {
        lower_str(ptr);
        if (strcmp(ptr, "push") == 0)
        {
            // todo check if next operand is a valid operand.
            ptr = strtok(NULL, " \n");
            svm->program[svm->inst_ptr++] = (struct Instruction)PUSH(atoi(ptr));
        }
        else if (strcmp(ptr, "plus") == 0)
        {
            svm->program[svm->inst_ptr++] = (struct Instruction)PLUS;
        }
        else if (strcmp(ptr, "print") == 0)
        {
            svm->program[svm->inst_ptr++] = (struct Instruction)PRINT;
        }
        else
        {
            fprintf(stderr, "ERROR: Unexpected instruction.\n");
        }
        ptr = strtok(NULL, " \n");
    }

    free(buf);
}

void lower_str(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        str[i] = tolower(str[i]);
    }
}