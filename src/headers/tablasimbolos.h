#pragma once
#include <string>
#include <list>
using namespace std;

struct simbolo {
  string id;
  int dir;
  int tipo;
  string var;
  list<int> args;

  simbolo(){}
  simbolo(string id, int dir, int tipo, string var, list<int> args) : id(id), dir(dir), tipo(tipo), var(var), args(args){}

  string str() {
    return id
        + "\t" + std::to_string(dir)
        + "\t" + std::to_string(tipo)
        + "\t" + var;
  }

  bool operator==(const struct simbolo& a) const {
    return a.id == this->id;
  }
};

struct tablasimbolos {
  list<simbolo> tabla;

  tablasimbolos(){}
  tablasimbolos(list<simbolo> tabla) : tabla(tabla){}

  string str() {
    string str = "";
    for (simbolo simbolo : tabla)
        str = str + simbolo.str() + "\n";
    return str;
  }

  void agregar(simbolo simbolo) {
    tabla.push_back(simbolo);
  }

  void eliminar(simbolo simbolo) {
    tabla.remove(simbolo);
  }

  bool buscar(string id) {
    for (simbolo simbolo : tabla)
        if (simbolo.id == id)
            return true;
    return false;
  }

  int get_tipo(string id) {
    for (simbolo simbolo : tabla)
        if (simbolo.id == id)
            return simbolo.tipo;
    return -1;
  }

  string get_var(string id) {
    for (simbolo simbolo : tabla)
        if (simbolo.id == id)
            return simbolo.var;
    return NULL;
  }
};
