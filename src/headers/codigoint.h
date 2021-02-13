#pragma once

#include <vector>
#include <string>
using namespace std;

struct cuadrupla{
    string op;
    string arg1;
    string arg2;
    string res;

    cuadrupla(string op, string arg1, string arg2, string res){
        this->op = op;
        this->arg1 = arg1;
        this->arg2 = arg2;
        this->res = res;
    }
};

struct CodigoInt{
    vector<cuadrupla> codigo;
    void genCod(cuadrupla c);
    void mostrar();
    void imprimir(string fileName);
};
