#include <stdlib.h>
#include <stdint.h>

struct _List {
    int32_t* data;
    int32_t length;
};
typedef struct _List List;

List* resizeArray(List* array) {
    int32_t* dPtr = realloc(array->data, 15 * sizeof(int32_t));
    if (dPtr == NULL){
        return array;
    }
    array->data = dPtr;
    return array;
}

int main() {
    List* array = calloc(1, sizeof(List));
    if (!array) return -1;

    array->data = calloc(10, sizeof(int32_t));
    if (!array->data) return -1;

    array = resizeArray(array);

    free(array->data);
    free(array);
    return 0;
}