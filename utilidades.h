#ifndef UTILIDADES_H
#define UTILIDADES_H

// ========== RLE ==========
unsigned char* descomprimirRLE(unsigned char* buffer, int size, int& outSize);

// ========== LZ78 ==========
unsigned char* descomprimirLZ78(unsigned char* buffer, int size, int& outSize);

// ========== ROTACIÓN ==========
unsigned char*  rotarArregloDerecha(unsigned char* in, int size, int n);

// ========== XOR ==========
unsigned char* aplicarXOR(unsigned char* buffer, int size, unsigned char clave);

// ========== ARCHIVO ==========
unsigned char* leerArchivo(const char* nombre, int& size);
void guardarResultado(const char* nombreArchivo,
                         const unsigned char* buffer, int size,
                         int n, int clave,int met);
//=========== COMPARACION DE CADENA CON PISTA=========
int esta_contenido(const unsigned char* contenedor, int tam_contenedor,
                   const unsigned char* contenido, int tam_contenido);


#endif
