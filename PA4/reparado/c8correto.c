#include <stdlib.h>
#include <stdint.h>

int main() {
    char* destination = calloc(27, sizeof(char));
    char* source = malloc(26 * sizeof(char));

    for(uint8_t i = 0; i < 26; i++) { // Ajusta o loop para não exceder os limites de source
        *(destination + i) = *(source + i);
    }
    *(destination + 26) = '\0'; // Adiciona o caractere nulo ao final de destination

    free(destination);
    free(source);
    return 0;
}