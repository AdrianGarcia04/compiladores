#pragma once

#include <vector>
#include <string>
#include <fstream> 
using namespace std;

struct cuadrupla{
    string op;
    string arg1;
    string arg2;
    string res;

    cuadrupla(){}
    cuadrupla(string op, string arg1, string arg2, string res) : op(op), arg1(arg1), arg2(arg2), res(res){}

    string str() {
      return op + ' ' + arg1 + ' ' + arg2 + ' ' + res;
    }
};

struct CodigoInt{
    vector<cuadrupla> codigo;

    CodigoInt(){}
    CodigoInt(vector<cuadrupla> codigo) : codigo(codigo){}

    void genCod(cuadrupla cuadrupla) {
      codigo.push_back(cuadrupla);
    }

    void imprimir(string nombre) {
      ofstream archivo;
      archivo.open(nombre);

      if(archivo.fail())
        std::cout << "Error al escribir en el archivo" << '\n';

      for(cuadrupla cuadrupla : codigo)
        archivo << cuadrupla.str() << '\n';
      archivo.close();
    }
};
