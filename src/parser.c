#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inst.h"
#include "parser.h"

#include <io.h>
#include <strb.h>

size_t parse_ident(const char *buf, size_t cursor, strb *str) {
    size_t end = cursor;
    while (isalpha(buf[end])) {
        strb_append_single(str, buf[end]);
        end++;
    }

    return end;
}

size_t parse_number(const char *buf, size_t cursor, strb *str) {
    size_t end = cursor;
    while (isdigit(buf[end])) {
        strb_append_single(str, buf[end]);
        end++;
    }

    return end;
}

void new_parse_source(SVM *svm, const char *filename) {

    size_t len = 0;
    char *buf = read_file(filename, &len);

    strb str = strb_init(1024);

    Instruction current = {0};

    size_t cursor = 0;
    while (cursor < len) {
        switch (buf[cursor]) {
        case ';': {
            add_instruction(svm, current);
            current.op = 0;
            cursor++;
        } break;
        case '\n':
        case '\r':
        case '\t':
        case ' ':
            cursor++;
            break;
        default: {
            if (isalpha(buf[cursor])) {
                cursor = parse_ident(buf, cursor, &str);
                lower_str(str.str);
                if (strncmp(str.str, "push", 4) == 0)
                    current.type = INST_PUSH;
                else if (strncmp(str.str, "plus", 4) == 0)
                    current.type = INST_PLUS;
                else if (strncmp(str.str, "print", 5) == 0)
                    current.type = INST_PRINT;
                else {
                    printf("Unexpected ident: %s.\n", str.str);
                    free(buf);
                    strb_free(str);
                    exit(0);
                }
                str.cnt = 0;
            } else if (isdigit(buf[cursor])) {
                cursor = parse_number(buf, cursor, &str);
                current.op = atoi(str.str);
                str.cnt = 0;
            } else {
                printf("Unexpected char: %c\n", buf[cursor]);
                free(buf);
                strb_free(str);
                exit(0);
            }
        } break;
        }
    }

    for (size_t i = 0; i < svm->inst_ptr; i++) {
        printf("[%zu] Inst:\n", i);
        printf("   %s\n", inst_to_str(svm->program[i].type));
        printf("   %d\n", svm->program[i].op);
    }

    free(buf);
    strb_free(str);
}

void parse_source(SVM *svm, const char *filename) {

    size_t len = 0;
    char *buf = read_file(filename, &len);

    char *ptr = strtok(buf, " \n");

    while (ptr != NULL) {
        lower_str(ptr);
        if (strcmp(ptr, "push") == 0) {
            // todo check if next operand is a valid operand.
            ptr = strtok(NULL, "\n");
            if (ptr[0] == '"') {
                int mem_ptr = save_string_literal(svm, ptr);
                add_instruction(svm, PUSH(mem_ptr));
            } else {
                add_instruction(svm, PUSH(atoi(ptr)));
            }
        } else if (strcmp(ptr, "jmp") == 0) {
            // todo check if next operand is a valid operand.
            ptr = strtok(NULL, " \n");
            add_instruction(svm, JMP(atoi(ptr)));
        } else if (strcmp(ptr, "jneq") == 0) {
            // todo check if next operand is a valid operand.
            ptr = strtok(NULL, " \n");
            add_instruction(svm, JNEQ(atoi(ptr)));
        } else if (strcmp(ptr, "plus") == 0) {
            add_instruction(svm, PLUS);
        } else if (strcmp(ptr, "minus") == 0) {
            add_instruction(svm, MINUS);
        } else if (strcmp(ptr, "mult") == 0) {
            add_instruction(svm, MULT);
        } else if (strcmp(ptr, "div") == 0) {
            add_instruction(svm, DIV);
        } else if (strcmp(ptr, "mod") == 0) {
            add_instruction(svm, MOD);
        } else if (strcmp(ptr, "print") == 0) {
            add_instruction(svm, PRINT);
        } else if (strcmp(ptr, "prints") == 0) {
            add_instruction(svm, PRINTS);
        } else if (strcmp(ptr, "drop") == 0) {
            add_instruction(svm, DROP);
        } else if (strcmp(ptr, "equal") == 0) {
            add_instruction(svm, EQUAL);
        } else if (strcmp(ptr, "dup") == 0) {
            add_instruction(svm, DUP);
        } else if (strcmp(ptr, "lt") == 0) {
            add_instruction(svm, LT);
        } else if (strcmp(ptr, "lteq") == 0) {
            add_instruction(svm, LTEQ);
        } else if (strcmp(ptr, "gt") == 0) {
            add_instruction(svm, GT);
        } else if (strcmp(ptr, "gteq") == 0) {
            add_instruction(svm, GTEQ);
        } else if (strcmp(ptr, "dropall") == 0) {
            add_instruction(svm, DROPALL);
        } else if (strcmp(ptr, "halt") == 0) {
            add_instruction(svm, HALT);
        } else if (strcmp(ptr, "dump") == 0) {
            add_instruction(svm, DUMP);
        } else if (strcmp(ptr, "nequal") == 0) {
            add_instruction(svm, NEQUAL);
        } else if (strcmp(ptr, "memset") == 0) {
            ptr = strtok(NULL, " \n");
            add_instruction(svm, MEMSET(atoi(ptr)));
        } else if (strcmp(ptr, "memget") == 0) {
            ptr = strtok(NULL, " \n");
            add_instruction(svm, MEMGET(atoi(ptr)));
        } else if (ptr[0] == '#') {
            ptr = strtok(NULL, "\n");
        } else {
            fprintf(stderr, "ERROR: Unexpected instruction: %s\n", ptr);
        }
        ptr = strtok(NULL, " \n");
    }

    free(buf);
}

void lower_str(char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}
