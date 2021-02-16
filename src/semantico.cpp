#include "semantico.h"

bool semantico::equivalentes(int tipo1, int tipo2) {
    if (tipo1 == tipo2)
        return true;
    if (tipo1 == 0 && tipo2 == 1 || tipo1 = 1 && tipo2 == 0)
        return true;
    return false;
}

int semantico::maximo(int tipo1, int tipo2) {
    if (tipo1 == tipo2)
        return tipo1;
    if (tipo1 == 0 && tipo2 == 1 || tipo1 = 1 && tipo2 == 0)
        return 1;
    return -1;
}

string semantico::ampliar(string dir, int menor, int mayor) {
    if (menor == mayor)
        return dir;
    string temp = nuevaTemporal();
    if (menor == 0 && mayor == 1) {
        codigo.genCod(cuadrupla("=", "(float)" + dir, "", temp));
        return temp;
    }
}

string semantico::reducir(string dir, int mayor, int menor) {
    if (menor == mayor)
        return dir;
    string temp = nuevaTemporal();
    if (menor == 0 && mayor == 1) {
        codigo.genCod(cuadrupla("=", "(int)" + dir, "", temp));
        return temp;
    }
}

string semantico::nuevaTemporal() {
    static int numTemp = 0;
    string etq = "t" + numTemp++;
    return etq;
}