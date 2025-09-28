#include "utilidades.h"
#include <iostream>
#include <fstream>
using namespace std;

// ==================== RLE ====================
// Descomprime un buffer usando RLE (ternas: [basura][cantidad][caracter])
char* descomprimirRLE(unsigned char* buffer, int size, int& outSize) {
    int total = 0;
    // Paso 1: calcular tamaño del mensaje descomprimido
    for (int i = 0; i < size; i += 3) {
        unsigned char cantidad = buffer[i + 1]; // segundo byte
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

// ==================== LZ78 ====================
// Descomprime un buffer usando LZ78 (ternas: [indice_bajo][indice_alto][caracter])
char* descomprimirLZ78(unsigned char* buffer, int size, int& outSize) {
    if (size % 3 != 0) {
        cout << "Error: LZ78 data debe ser multiplo de 3 bytes" << endl;
        outSize = 0;
        return nullptr;
    }

    // Diccionario implementado con dos arrays paralelos
    char** diccionarioCadenas = new char*[1000];        // Array de punteros a cadenas
    int* diccionarioLongitudes = new int[1000];         // Array de longitudes correspondientes
    int numEntradas = 0;

    // Inicializar arrays
    for (int i = 0; i < 1000; i++) {
        diccionarioCadenas[i] = nullptr;
        diccionarioLongitudes[i] = 0;
    }

    // Buffer resultado (estimacion conservadora: 4x el tamaño)
    char* salida = new char[size * 4];
    int pos = 0;

    // Procesar cada entrada LZ78
    for (int i = 0; i < size; i += 3) {
        // Leer indice (little endian) y caracter
        int indice = buffer[i] | (buffer[i + 1] << 8);
        unsigned char caracter = buffer[i + 2];

        // Si hay prefijo en diccionario
        if (indice > 0 && indice <= numEntradas) {
            char* cadenaPrevia = diccionarioCadenas[indice - 1];
            int longitudPrevia = diccionarioLongitudes[indice - 1];

            // Copiar cadena previa al resultado
            for (int j = 0; j < longitudPrevia; j++) {
                salida[pos++] = cadenaPrevia[j];
            }
        }

        // Agregar nuevo caracter
        if (caracter != 0) {
            salida[pos++] = (char)caracter;
        }

        // Crear nueva entrada en diccionario (si hay caracter valido)
        if (numEntradas < 1000 && caracter != 0) {
            int longitudPrefijo = 0;
            if (indice > 0 && indice <= numEntradas) {
                longitudPrefijo = diccionarioLongitudes[indice - 1];
            }

            // Nueva longitud = longitud prefijo + 1 caracter
            int nuevaLongitud = longitudPrefijo + 1;
            diccionarioLongitudes[numEntradas] = nuevaLongitud;

            // Reservar memoria para nueva cadena
            diccionarioCadenas[numEntradas] = new char[nuevaLongitud];

            // Copiar prefijo si existe
            if (indice > 0 && indice <= numEntradas) {
                char* cadenaPrevia = diccionarioCadenas[indice - 1];
                for (int j = 0; j < longitudPrefijo; j++) {
                    diccionarioCadenas[numEntradas][j] = cadenaPrevia[j];
                }
            }

            // Agregar caracter al final
            diccionarioCadenas[numEntradas][longitudPrefijo] = (char)caracter;

            numEntradas++;
        }
    }

    outSize = pos;

    // Limpiar memoria del diccionario
    for (int i = 0; i < numEntradas; i++) {
        if (diccionarioCadenas[i] != nullptr) {
            delete[] diccionarioCadenas[i];
        }
    }
    delete[] diccionarioCadenas;
    delete[] diccionarioLongitudes;

    return salida;
}

// ==================== ROTACIÓN ====================
void rotarArregloDerecha(unsigned char* in, unsigned char* out, int size, int n) {
    for (int i = 0; i < size; i++) {
        unsigned char b = in[i];
        out[i] = (b >> n) | (b << (8 - n)); // rotación circular en el byte
    }
}

// ==================== XOR ====================
void aplicarXOR(unsigned char* buffer, int size, unsigned char clave) {
    for (int i = 0; i < size; i++) {
        buffer[i] ^= clave;
    }
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