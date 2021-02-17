#pragma once
#include <string>
#include <list>
using namespace std;

struct tablacadenas {
  list<string> tabla;

  tablacadenas(){}
  tablacadenas(list<string> tabla) : tabla(tabla){}

  string str() {
    string str = "";
    for (string cadena : tabla)
        str = str + cadena + "\n";
    return str;
  }

  void agregar(string cadena) {
    tabla.push_back(cadena);
  }

  void eliminar(string cadena) {
    tabla.remove(cadena);
  }
};
