#include <iostream>
#include "utilidades.h"
using namespace std;


// --- Rotación a la derecha n bits ---
unsigned char rotarDerecha(unsigned char byte, int n) {
    return (byte >> n) | (byte << (8 - n));
}

// --- Desencriptar un byte ---
unsigned char desencriptarByte(unsigned char b, int n, unsigned char K) {
    b=b^K;
    return rotarDerecha(b, n);
}

// --- Verificar si 3 bytes son RLE válidos ---
bool esRLEValido(unsigned char b1, unsigned char b2, unsigned char b3) {
    unsigned char cantidad = b2; // segundo byte = cantidad
    if (cantidad == 0) return false; // no puede ser cero
    // b3 es el caracter, aceptamos cualquier valor ASCII visible o al menos imprimible
    if (b3 < 32 || b3 > 126) return false;
    return true;
}

// --- Verificar si 3 bytes son LZ78 válidos ---
bool esLZ78Valido(unsigned char b1, unsigned char b2, unsigned char b3, int entradasActuales) {
    int prefijo = (b1 << 8) | b2;
    if (prefijo > entradasActuales) return false; // no puede referenciar más allá del diccionario
    if (b3 < 32 || b3 > 126) return false;       // caracter legible
    return true;
}

int main() {
    int size=0;
    int cont1=0;
    int cont2=0;
    int clave=90;
    int n=3;
    int outSize=0;
    unsigned char* buffer = leerArchivo("C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/datasetDesarrollo/datasetDesarrollo/Encriptado4.txt", size);

    if (buffer != nullptr) {
        std::cout << "Archivo leído correctamente. Tamaño: " << size << " bytes." << std::endl;
    }
    // XOR
    unsigned char* xorResult = aplicarXOR(buffer, size, clave);

    // Rotación
    unsigned char* rotResult = rotarArregloDerecha(xorResult, size, n);
    delete[] xorResult;
    // Descompresión

    unsigned char* finalText = descomprimirRLE(rotResult, size, outSize);
    delete[] rotResult;
    cout<<"Mensaje descomprimido"<<endl;
    for (int n = 0; n <= outSize; n++){
        cout<<finalText[n];
    }
    cout<<endl;

    delete[] buffer;
    delete[] finalText;
    /*
    // Probar todas las combinaciones de n y K
    for (int n = 1; n <= 7; n++) {
        for (int K = 0; K < 256; K++) {
            unsigned char d0 = desencriptarByte(buffer[0], n, K);
            unsigned char d1 = desencriptarByte(buffer[1], n, K);
            unsigned char d2 = desencriptarByte(buffer[2], n, K);
            unsigned char d3 = desencriptarByte(buffer[3], n, K);
            unsigned char d4 = desencriptarByte(buffer[4], n, K);
            unsigned char d5 = desencriptarByte(buffer[5], n, K);

            // Verificar como RLE
            if (esRLEValido(d0, d1, d2) && esRLEValido(d3, d4, d5)) {
               // std::cout << "Posible RLE con n=" << n << ", K=" << K << std::endl;
                cont1=cont1+1;

            }

            // Verificar como LZ78
            // Entradas actuales al inicio = 0
            if (esLZ78Valido(d0, d1, d2, 0) && esLZ78Valido(d3, d4, d5, 1)) {
                std::cout << "Posible LZ78 con n=" << n << ", K=" << K << std::endl;
                cont2=cont2+1;

            }
        }
    }
    cout<<"posibles RLE: "<<cont1<<endl;
    cout<<"posibles LZ78: "<<cont2<<endl;
*/
    return 0;
}
