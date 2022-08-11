#include <stdlib.h>
#include <stdio.h>

int main(){
    void *ptr = malloc(21);
    free(ptr);
    printf("%d\n", *((int *)ptr - 16));
    ptr = malloc(500);
    free(ptr);
    printf("%d\n", *((int *)ptr - 16));
}
