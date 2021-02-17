#pragma once
#include <string>
#include <list>
using namespace std;

struct tipo_s {
  int id;
  string tipo;
  int tam;
  int elem;
  int tipoBase;

  tipo_s(){}
  tipo_s(int id, string tipo, int tam, int elem, int tipoBase) : id(id), tipo(tipo), tam(tam), elem(elem), tipoBase(tipoBase){}

  string str() {
    return std::to_string(id)
        + "\t" + tipo
        + "\t" + std::to_string(tam)
        + "\t" + std::to_string(elem)
        + "\t" + std::to_string(tipoBase);
  }

  bool operator==(const struct tipo_s& a) const {
    return a.id == this->id;
  }
};

struct tablatipos {
  list<tipo_s> tabla;

  tablatipos(){}
  tablatipos(list<tipo_s> tabla) : tabla(tabla){}

  string str() {
    string str = "";
    for (tipo_s tipo : tabla)
        str = str + tipo.str() + "\n";
    return str;
  }

  void agregar(tipo_s tipo) {
    tabla.push_back(tipo);
  }

  void eliminar(tipo_s tipo) {
    tabla.remove(tipo);
  }

  bool buscar(int id) {
    for (tipo_s tipo : tabla)
        if (tipo.id == id)
            return true;
    return false;
  }

  int get_tam(int id) {
    for (tipo_s tipo : tabla)
        if (tipo.id == id)
            return tipo.tam;
    return -1;
  }

  string get_nom(int id) {
    for (tipo_s tipo : tabla)
        if (tipo.id == id)
            return tipo.tipo;
    return NULL;
  }

  int get_base(int id) {
    for (tipo_s tipo : tabla)
        if (tipo.id == id)
            return tipo.tipoBase;
    return -1;
  }
};
