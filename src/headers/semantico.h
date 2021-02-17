#pragma once

#include <string>
#include "codigoint.h"
using namespace std;


struct semantico{
    CodigoInt codigo;
    int numEtq = 0;

    semantico(){}
    semantico(CodigoInt codigo, int numEtq) : codigo(codigo), numEtq(numEtq){}

    void genCod(cuadrupla cuadrupla) {
      codigo.genCod(cuadrupla);
    }

    void imprimir(string nombre) {
      codigo.imprimir(nombre);
    }

    int maximo(int tipo1, int tipo2) {
        if (tipo1 == tipo2)
            return tipo1;
        if (tipo1 == 0 && tipo2 == 1 || tipo1 == 1 && tipo2 == 0)
            return 1;
        return -1;
    }

    string ampliar(string dir, int menor, int mayor) {
        if (menor == mayor)
            return dir;
        string temp = nuevaTemporal();
        if (menor == 0 && mayor == 1) {
            codigo.genCod(cuadrupla("=", "(float)" + dir, "", temp));
            return temp;
        }
    }

    string reducir(string dir, int mayor, int menor) {
        if (menor == mayor)
            return dir;
        string temp = nuevaTemporal();
        if (menor == 0 && mayor == 1) {
            codigo.genCod(cuadrupla("=", "(int)" + dir, "", temp));
            return temp;
        }
    }

    string nuevaTemporal() {
        static int numTemp = 0;
        string etq = "t" + numTemp++;
        return etq;
    }

    string nuevaEtiqueta() {
        string etq = "l" + numEtq++;
        return etq;
    }

    void actualizaEtqt(int nueva) {
        numEtq = nueva;
        std::cout << to_string(numEtq);
    }

    string nuevoIndice(){
        static int numIndice = 0;
        string ind = "i" + numIndice++;
        return ind;
    }

    bool equivalentes(int tipo1, int tipo2) {
        if (tipo1 == tipo2)
            return true;
        if (tipo1 == 0 && tipo2 == 1 || tipo1 == 1 && tipo2 == 0)
            return true;
        return false;
    }
};
