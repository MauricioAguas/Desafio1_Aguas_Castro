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
//validacion de numero de archivos
int solicitarNumeroArchivos() {
    int numeroArchivos;

    while (true) {
        cout << "¿Cuantos archivos desea desencriptar?: ";
        cin >> numeroArchivos;

        // Verificar si la entrada es válida
        if (cin.fail()) {
            cout << " Error: Debe ingresar un número entero." << endl;
            cin.clear();         // Limpiar el estado de error
            cin.ignore(1000, '\n'); // Ignorar caracteres en buffer
        } else if (numeroArchivos < 1 ) {
            cout << " Error: El número debe ser mayor a 0" << endl;
        } else {
            cout << " Entrada valida: " << numeroArchivos << " archivo(s)" << endl;
            return numeroArchivos;
        }
        cout << endl; // Línea en blanco
    }
}

int main() {
    int size=0;
    int sizePista=0;
    int outSize=0;
    int N=solicitarNumeroArchivos();

    for (int i = 1; i <= N; i++) {
        // Construir nombre de archivo dinámicamente
        ostringstream encriptadoPath;
        encriptadoPath << "C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/datasetDesarrollo/datasetDesarrollo/Encriptado" << i << ".txt";

        ostringstream pistaPath;
        pistaPath << "C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/datasetDesarrollo/datasetDesarrollo/pista" << i << ".txt";

        int size = 0, sizePista = 0;
        unsigned char* buffer = leerArchivo(encriptadoPath.str().c_str(), size);
        unsigned char* pista = leerArchivo(pistaPath.str().c_str(), sizePista);

        if (buffer != nullptr) {
            cout << "Archivo " << i << " leido correctamente. Tamano: " << size << " bytes." << std::endl;
        }

        encontrarNKM(buffer, pista, size, sizePista);
    }
    return 0;
}

