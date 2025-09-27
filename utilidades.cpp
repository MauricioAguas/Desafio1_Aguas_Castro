#include "utilidades.h"
#include <fstream>
#include <iostream>
using namespace std;
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
void rotarArregloDerecha(unsigned char* in, unsigned char* out, int size, int n) {
    for (int i = 0; i < size; i++) {
        unsigned char b = in[i];
        out[i] = (b >> n) | (b << (8 - n)); // rotación circular en el byte
    }
}
#include "utilidades.h"
#include <fstream>
#include <iostream>

unsigned char* leerArchivo(const char* nombre, int& size) {
    std::ifstream file(nombre, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error abriendo archivo: " << nombre << std::endl;
        size = 0;
        return nullptr;
    }

    size = file.tellg();
    file.seekg(0, std::ios::beg);

    unsigned char* buffer = new unsigned char[size];
    file.read(reinterpret_cast<char*>(buffer), size);
    file.close();

    return buffer;
}

