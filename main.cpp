#include <iostream>
#include "utilidades.h"
#include "busqueda.h"
#include <cstring>
using namespace std;

#include <iostream>
#include "utilidades.h"
using namespace std;

bool sonIguales(const unsigned char* buffer, int size, const char* cadena) {
    int len = strlen(cadena);
    if (size != len) return false;   // si no tienen mismo tamaño, no son iguales
    return memcmp(buffer, cadena, len) == 0;
}
int main() {
    int size=0;
    int sizePista=0;
    int cont1=0;
    int cont2=0;
    int clave=90;
    int n=3;
    int outSize=0;
    unsigned char* buffer = leerArchivo("C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/datasetDesarrollo/datasetDesarrollo/Encriptado4.txt", size);
    unsigned char* pista = leerArchivo("C:/Users/57312/Desktop/jhacasky/Universidad/2025-2/datasetDesarrollo/datasetDesarrollo/pista4.txt", sizePista);

    if (buffer != nullptr) {
        std::cout << "Archivo leído correctamente. Tamaño: " << size << " bytes." << std::endl;
    }
      encontrarNKM(buffer,pista, size,  sizePista);
/*
    // XOR
    unsigned char* xorResult = aplicarXOR(buffer, size, clave);

    // Rotación
    unsigned char* rotResult = rotarArregloDerecha(xorResult, size, n);
    delete[] xorResult;
    // Descompresión

    unsigned char* finalText = descomprimirRLE(rotResult, size, outSize);
    delete[] rotResult;
    // --- Prueba 1: Contenido encontrado ---
    int resultado1 = esta_contenido(finalText, outSize, pista, sizePista);

    if (resultado1 != -1) {
        std::cout << "Prueba 1: Sub-secuencia encontrada en el indice: " << resultado1 << "\n";
    } else {
        std::cout << "Prueba 1: Sub-secuencia NO encontrada.\n";
    }

    cout<<"Mensaje descomprimido"<<endl;
    for (int n = resultado1; n < sizePista+resultado1; n++){
        cout<<finalText[n];
    }
    cout<<endl;
    const char* textoEsperado = "lamontanaselevacasascuidadasmontesbosquesrioslagosanimalessilvestrespajarosvolandoarbustosfloresherbasiluminapaisajesnaturalesconsolazamientoalrededordelmundoaventurasincreiblesexploradoresviajanporterritoriosremotosdescubriendosorprendentesmisterioshistoricoscivilizacionesantiguastesorosocultosbibliotecasperdidasartefactosantiguoshumanidadeshistoriassorprendentesrelatoslegendasleyendasfantasmasespiritusencantamientosmagicosbrujeriamagianaturalezapoderosasenergiassecretasproteccionguardianesantiguossantuariosritualesmisteriossecretoselementosnaturalescielostaraleslucesestrelladaslunallamadavientoaguafuegohumotierraalientabosquesanimalesavespecesplantassilvestresherbascultivosfrutalesverdurashortalizasolorventosolesplegadolluviasonrisasemocionaventurexploraciondescubrimientoinmensidadpaisajehermosoterrenosdesconocidosnarracionescuentosfantasticosmaravillososincreiblesrealidadimaginacionhistoriasleyendasemocionpasionesentusiasmosabercuriosidadaprendizajeexperienciasviajesmundoaventurasdescubrimientosconocimientosorprendentesinteraccionespersonalesamistadfamiliaresrelacionesafectivasemocionales";

    if (sonIguales(finalText, outSize, textoEsperado)) {
        std::cout << "Las cadenas son IGUALES " << std::endl;
    } else {
        std::cout << "Las cadenas son DIFERENTES " << std::endl;
    }

    delete[] buffer;
    delete[] finalText;
 */
    return 0;
}

