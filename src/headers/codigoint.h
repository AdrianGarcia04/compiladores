#pragma once

#include <list>
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
    list<cuadrupla> codigo;

    CodigoInt(){}
    CodigoInt(list<cuadrupla> codigo) : codigo(codigo){}

    void genCod(cuadrupla cuadrupla) {
      codigo.push_back(cuadrupla);
    }

    int reemplazarIndices(list<string> lista, int numEtiqueta) {
      int nueva = numEtiqueta;
      for(string currEtqt : lista) {
        nueva = nueva + 1;
        list<cuadrupla>::iterator i;
        for (i = codigo.begin(); i != codigo.end(); i++)
          if (i->res==currEtqt)
          i->res = "l" + to_string(nueva);
      }
      list<cuadrupla>::iterator i;
      i = codigo.end();
      i--;
      i->res = "l" + to_string(numEtiqueta);
      return nueva;
    }

    string str() {
      string str = "";
      for (cuadrupla cuadrupla : codigo)
          str = str + cuadrupla.str() + "\n";
      return str;
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
