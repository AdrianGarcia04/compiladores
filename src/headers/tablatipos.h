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
};

struct tablatipos {
  list<tipo_s> tabla;
};
