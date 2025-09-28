#ifndef BUSQUEDA_H
#define BUSQUEDA_H
unsigned char rotarDerecha(unsigned char byte, int n);

// --- Desencriptar un byte ---
unsigned char desencriptarByte(unsigned char b, int n, unsigned char K);
// --- Verificar si 3 bytes son RLE válidos ---
bool esRLEValido(unsigned char b1, unsigned char b2, unsigned char b3);

// --- Verificar si 3 bytes son LZ78 válidos ---
bool esLZ78Valido(unsigned char b1, unsigned char b2, unsigned char b3, int entradasActuales);
void encontrarNKM(unsigned char* buffer,unsigned char* pista, int size, int sizePista);
#endif // BUSQUEDA_H
