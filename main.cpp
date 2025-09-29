#include <iostream>
#include <fstream>
#include <iostream>
#include "utilidades.h"
#include "busqueda.h"
#include <sstream>   // para ostringstream
#include <string>    // para std::string
#include <cstring>
using namespace std;

bool sonIguales(const unsigned char* buffer, int size, const char* cadena) {
    int len = strlen(cadena);
    if (size != len) return false;   // si no tienen mismo tamaño, no son iguales
    return memcmp(buffer, cadena, len) == 0;
}
int main() {
    int size=0;
    int sizePista=0;
    int outSize=0;
    int N;
    cout << "Anote la cantidad de archivos a desencriptar: ";
    cin >> N;

    for (int i = 1; i <= N; i++) {
        // Construir nombre de archivo dinámicamente
        std::ostringstream encriptadoPath;
        encriptadoPath << "C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/datasetDesarrollo/datasetDesarrollo/Encriptado" << i << ".txt";

        std::ostringstream pistaPath;
        pistaPath << "C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/datasetDesarrollo/datasetDesarrollo/pista" << i << ".txt";

        int size = 0, sizePista = 0;
        unsigned char* buffer = leerArchivo(encriptadoPath.str().c_str(), size);
        unsigned char* pista = leerArchivo(pistaPath.str().c_str(), sizePista);

        if (buffer != nullptr) {
            std::cout << "Archivo " << i << " leído correctamente. Tamaño: " << size << " bytes." << std::endl;
        }

        encontrarNKM(buffer, pista, size, sizePista);
    }
    return 0;
}

