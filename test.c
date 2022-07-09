#include <stdio.h>

int main(void) {
    int bla = 69;
    int *bla_ptr = &bla;
    printf("Number: %d\n", bla);
    printf("Number: %ld\n", bla_ptr);
    return 0;
}