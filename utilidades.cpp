#include "utilidades.h"

// ==================== RLE ====================
// Descomprime un buffer usando RLE (ternas: [basura][cantidad][caracter])
char* descomprimirRLE(unsigned char* buffer, int size, int& outSize) {
    int total = 0;

    // Paso 1: calcular tamaño del mensaje descomprimido
    for (int i = 0; i < size; i += 3) {
        unsigned char cantidad = buffer[i + 1];  // segundo byte
        total += cantidad;
    }

    // Reservar memoria para salida
    char* salida = new char[total];
    outSize = total;

    // Paso 2: reconstruir
    int pos = 0;
    for (int i = 0; i < size; i += 3) {
        unsigned char cantidad = buffer[i + 1];
        unsigned char simbolo = buffer[i + 2];
        for (int j = 0; j < cantidad; j++) {
            salida[pos++] = (char)simbolo;
        }
    }

    return salida;
}
