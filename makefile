CFLAGS=-Wextra -Werror -Wall

SRCS=./src/inst.c ./src/svm.c ./src/parser.c ./src/main.c

all:
	cc -o svm $(SRCS) $(CFLAGS) -I./cutils
