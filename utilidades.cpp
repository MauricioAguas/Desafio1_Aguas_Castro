#include "utilidades.h"
#include <iostream>
#include <fstream>
using namespace std;

// ==================== RLE ====================
// Descomprime un buffer usando RLE (ternas: [basura][cantidad][caracter])
unsigned char* descomprimirRLE(unsigned char* buffer, int size, int& outSize) {
    int total = 0;
    // Paso 1: calcular tamaño del mensaje descomprimido
    for (int i = 0; i < size; i += 3) {
        unsigned char cantidad = buffer[i + 1]; // segundo byte
        total += cantidad;
    }
    // Reservar memoria para salida
    unsigned char* salida = new unsigned char[total-1];
    outSize = total-1;
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

// ==================== LZ78 ITERATIVO SIMPLE ====================
unsigned char* descomprimirLZ78(unsigned char* buffer, int size, int& outSize) {
    // Validar que el tamaño sea múltiplo de 3
    if (size % 3 != 0) {
        cout << "Error: LZ78 data debe ser múltiplo de 3 bytes" << endl;
        outSize = 0;
        return nullptr;
    }
    
    // Buffer de salida (estimación conservadora)
    unsigned char* salida = new unsigned char[size * 3];
    outSize = 0;
    
    // Procesar cada entrada de 3 bytes
    for (int i = 0; i < size; i += 3) {
        unsigned char separador = buffer[i];     // Primer byte (basura)
        unsigned char indice = buffer[i + 1];   // Segundo byte (índice)
        unsigned char caracter = buffer[i + 2]; // Tercer byte (carácter)
        
        // Array temporal para la secuencia
        unsigned char secuencia[500];
        int secuenciaLen = 0;
        
        // Recorrer hacia atrás siguiendo los índices
        unsigned char indiceActual = indice;
        while (indiceActual != 0) {
            // Calcular la posición en el buffer
            int posicion = (indiceActual * 3) - 3;
            
            // Validar posición
            if (posicion < 0 || posicion + 2 >= size) {
                delete[] salida;
                return nullptr;
            }
            
            // Obtener carácter y índice anterior
            unsigned char caracterAnterior = buffer[posicion + 2];
            unsigned char indiceAnterior = buffer[posicion + 1];
            
            // Guardar en secuencia
            secuencia[secuenciaLen++] = caracterAnterior;
            indiceActual = indiceAnterior;
        }
        
        // Copiar en orden correcto (reverso)
        for (int j = secuenciaLen - 1; j >= 0; j--) {
            salida[outSize++] = secuencia[j];
        }
        
        // Agregar carácter actual
        salida[outSize++] = caracter;
    }
    
    salida[outSize] = '\0';
    return salida;
}

// ==================== ROTACIÓN ====================
unsigned char*  rotarArregloDerecha(unsigned char* in, int size, int n) {
    unsigned char* out = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        unsigned char b = in[i];
        out[i] = (b >> n) | (b << (8 - n)); // rotación circular en el byte
    }
    return out;
}

// ==================== XOR ====================
unsigned char* aplicarXOR(unsigned char* buffer, int size, unsigned char clave) {
    unsigned char* out = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        unsigned char b = buffer[i];
        b=b^clave;
        out[i] = b;
    }
    return out;
}

// ==================== ARCHIVO ====================
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
