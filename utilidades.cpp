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
    unsigned char* salida = new unsigned char[total];
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

// ==================== LZ78 Indice 16 bits ====================
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
        unsigned char byteAlto = buffer[i];      // Primer byte (parte alta)
        unsigned char byteBajo = buffer[i + 1];  // Segundo byte (parte baja)
        unsigned char caracter = buffer[i + 2];  // Tercer byte (carácter)
        unsigned int indice = (unsigned int)byteAlto * 256 + (unsigned int)byteBajo;
        unsigned char secuencia[500];
        int secuenciaLen = 0;

        // Recorrer hacia atrás siguiendo los índices 
        unsigned int indiceActual = indice; 
        while (indiceActual != 0) {
            if (indiceActual > (unsigned int)(i / 3) || (indiceActual * 3) > (unsigned int)size) {
                delete[] salida;
                outSize = 0;
                return nullptr;
            }
            int posicion = (indiceActual * 3) - 3;
            unsigned char caracterAnterior = buffer[posicion + 2];     
            unsigned char byteAltoAnterior = buffer[posicion];
            unsigned char byteBajoAnterior = buffer[posicion + 1];
            unsigned int indiceAnterior = (unsigned int)byteAltoAnterior * 256 + (unsigned int)byteBajoAnterior;

            // Guardar en secuencia 
            secuencia[secuenciaLen++] = caracterAnterior;
            indiceActual = indiceAnterior;
        }
        // Copiar en orden correcto - reverso 
        for (int j = secuenciaLen - 1; j >= 0; j--) {
            salida[outSize++] = secuencia[j];
        }
        // Agregar carácter actual (
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
//=========COMPARAR PISTA===========
int esta_contenido(const unsigned char* contenedor, int tam_contenedor,
                   const unsigned char* contenido, int tam_contenido) {

    // Si el contenido es más grande que el contenedor, no puede estar contenido.
    if (tam_contenido > tam_contenedor) {
        return -1; // -1 indica que no se encontró.
    }
    // Si el contenido está vacío, se considera que está "contenido" al inicio.
    if (tam_contenido == 0) {
        return 0; // 0 indica que se encontró en el índice 0.
    }

    // El bucle externo recorre el 'contenedor' hasta la última posición
    // donde aún cabe el 'contenido'.
    for (int i = 0; i <= tam_contenedor - tam_contenido; ++i) {
        int j = 0; // Índice para el arreglo 'contenido'.

        // El bucle interno compara la sub-secuencia.
        // Comienza a comparar desde 'contenedor[i]' con 'contenido[0]'.
        for (j = 0; j < tam_contenido; ++j) {
            if (contenedor[i + j] != contenido[j]) {
                break; // Si no coinciden, salta del bucle interno.
            }
        }

        // Si el bucle interno terminó porque j llegó hasta tam_contenido,
        // significa que todos los caracteres coincidieron.
        if (j == tam_contenido) {
            return i; // Se encontró la sub-secuencia, devuelve el índice inicial.
        }
    }

    return -1; // Si el bucle externo termina, no se encontró la sub-secuencia.
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
void guardarResultado(const char* nombreArchivo,
                         const unsigned char* buffer, int size,
                         int n, int clave, int met) {
    if (buffer == nullptr || size <= 0) {
        std::cerr << "Error: no hay datos para guardar." << std::endl;
        return;
    }

    // Abrir en modo append para no sobrescribir
    std::ofstream file(nombreArchivo, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }
    if(met==0){
        file << "Rotacion: " << n << " | Clave: " << "0x" << std::hex << std::uppercase << clave<<" | Metodo usado: RLE" <<"\n";}
    else
        {file << "Rotacion: " << n << " | Clave: " << "0x" << std::hex << std::uppercase << clave <<" | Metodo usado: LZ78" <<"\n";}
        file.write(reinterpret_cast<const char*>(buffer), size);
        file << "\n----------------------------------------\n";

        file.close();

        std::cout << "Resultado agregado a " << nombreArchivo << std::endl;


}
