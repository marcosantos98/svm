#ifndef PARSER_H
#define PARSER_H

#include "svm.h"

void load_file(const char*, char**);
void parse_string(const char *, char **);
void parse_source(SVM*, const char*);
void lower_str(char*);

#endif