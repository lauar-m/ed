#include <stdlib.h>

void f(void) {
    int* x = malloc(10 * sizeof(int));
    if (x == NULL) {
        return;
    }
    x[9] = 0; 
    free(x); 
}

int main(void) {
    f();
    return 0;
}