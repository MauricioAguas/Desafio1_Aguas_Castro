#include <iostream>
#include "utilidades.h"
using namespace std;


int main() {
    unsigned char datos[] = {0b10110001, 0b11001010}; // 2 bytes de ejemplo
    int size = 2;

    unsigned char* salida = new unsigned char[size];
    rotarArregloDerecha(datos, salida, size, 3); // rotar cada byte 3 bits

    for (int i = 0; i < size; i++) {
        cout << "Byte " << i << " rotado: " << (int)salida[i] << endl;
    }

    delete[] salida;
    return 0;
}

