#include <iostream>
#include "utilidades.h"
using namespace std;


int main() {
    int size;
    unsigned char* buffer = leerArchivo("C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/Desafio1_Aguas_Castro/Desafio1/Encriptado1.txt", size);

    if (buffer != nullptr) {
        cout << "Archivo leido correctamente. Tamano: " << size << " bytes." << std::endl;

        delete[] buffer;
    }
    return 0;
}

