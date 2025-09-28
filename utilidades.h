#ifndef UTILIDADES_H
#define UTILIDADES_H

// ========== RLE ==========
char* descomprimirRLE(unsigned char* buffer, int size, int& outSize);

// ========== LZ78 ==========
char* descomprimirLZ78(unsigned char* buffer, int size, int& outSize);

// ========== ROTACIÓN ==========
void rotarArregloDerecha(unsigned char* in, unsigned char* out, int size, int n);

// ========== XOR ==========
void aplicarXOR(unsigned char* buffer, int size, unsigned char clave);

// ========== ARCHIVO ==========
unsigned char* leerArchivo(const char* nombre, int& size);

#endif