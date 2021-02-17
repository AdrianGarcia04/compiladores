#pragma once

#include <vector>
#include <string>
using namespace std;

struct cuadrupla{
    string op;
    string arg1;
    string arg2;
    string res;

    cuadrupla(){}
    cuadrupla(string op, string arg1, string arg2, string res) : op(op), arg1(arg1), arg2(arg2), res(res){}
};

struct CodigoInt{
    vector<cuadrupla> codigo;

    CodigoInt(){}
    CodigoInt(vector<cuadrupla> codigo) : codigo(codigo){}

    void genCod(cuadrupla cuadrupla) {
      codigo.push_back(cuadrupla);
    }

    void mostrar() {
      // TODO
    }

    void imprimir(string fileName) {
      // TODO
    }
};
