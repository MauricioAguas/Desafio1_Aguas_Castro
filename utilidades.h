#ifndef UTILIDADES_H
#define UTILIDADES_H


// ---------- RLE ----------
char* descomprimirRLE(unsigned char* buffer, int size, int& outSize);
void rotarArregloDerecha(unsigned char* in, unsigned char* out, int size, int n);

#endif
