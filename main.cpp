#include <iostream>
#include "utilidades.h"
using namespace std;


int main() {
    // Ejemplo: [X][4][A] [Y][3][B] [Z][2][C]
    unsigned char ejemplo[] = {0, 4, 'A', 0, 3, 'B', 0, 2, 'C'};
    int size = 9;

    int outSize;
    char* resultado = descomprimirRLE(ejemplo, size, outSize);

    for (int i = 0; i < outSize; i++) {
        cout << resultado[i];
    }
    cout << endl;

    delete[] resultado;
    return 0;
}
