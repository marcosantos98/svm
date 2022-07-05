#ifndef PARSER_H
#define PARSER_H

#include "svm.h"

void load_file(const char*, char**);
void parse_source(struct SVM*, const char*);
void lower_str(char*);

#endif