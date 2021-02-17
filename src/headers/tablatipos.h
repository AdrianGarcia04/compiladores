#pragma once
#include <string>
#include <list>
using namespace std;

/**
 * Estructura para representar tipos de la tabla de tipos
 * int id
 * string tipo
 * int tam
 * int elem
 * int tipoBase
 */
struct tipo_s {
  int id;
  string tipo;
  int tam;
  int elem;
  int tipoBase;

  /**
   * Constructor vacío
   * @return tipo_s
   */
  tipo_s(){}

  /**
   * Constructor con parámetros
   * @param id
   * @param tipo
   * @param tam
   * @param elem
   * @param tipoBase
   * @return tipo_s
   */
  tipo_s(int id, string tipo, int tam, int elem, int tipoBase) : id(id), tipo(tipo), tam(tam), elem(elem), tipoBase(tipoBase){}

  /**
   * Da la representación en cadena del tipo
   * @return string
   */
  string str() {
    return to_string(id)
        + "\t" + tipo
        + "\t" + to_string(tam)
        + "\t" + to_string(elem)
        + "\t" + to_string(tipoBase);
  }

  /**
   * Operador de comparación para tipos
   * @param tipo tipo a comparar
   * @return bool true en caso de ser iguales, false en otro caso
   */
  bool operator==(const struct tipo_s& a) const {
    return a.id == this->id;
  }
};

/**
 * Estructura para representar la tabla de tipos
 * list<tipo_s> tabla
 */
struct tablatipos {
  list<tipo_s> tabla;

  /**
   * Constructor vacío
   * @return tablatipos
   */
  tablatipos(){}

  /**
   * Constructor con parámetros
   * @param tabla
   * @return tablatipos
   */
  tablatipos(list<tipo_s> tabla) : tabla(tabla){}

  /**
   * Da la representación en cadena de la tabla
   * @return string
   */
  string str() {
    string str = "";
    for (tipo_s tipo : tabla)
        str = str + tipo.str() + "\n";
    return str;
  }

  /**
   * Agrega un tipo a la tabla de tipos
   * @param tipo_s el tipo a agregar
   */
  void agregar(tipo_s tipo) {
    tabla.push_back(tipo);
  }

  /**
   * Elimina un tipo de la tabla
   * @param tipo_s el tipo a eliminar
   */
  void eliminar(tipo_s tipo) {
    tabla.remove(tipo);
  }

  /**
   * Busca un tipo en la tabla
   * @param int el identificador del tipo a buscar
   * @return bool true si se encuentra el tipo, false en otro caso
   */
  bool buscar(int id) {
    for (tipo_s tipo : tabla)
        if (tipo.id == id)
            return true;
    return false;
  }

  /**
   * Da el nombre de un tipo dado su identificador
   * @param int el identificador del tipo a buscar
   * @return string el nombre del tipo
   */
  string get_nom(int id) {
    for (tipo_s tipo : tabla)
        if (tipo.id == id)
            return tipo.tipo;
    return NULL;
  }

  /**
   * Da el tamaño de un tipo dado su identificador
   * @param int el identificador del tipo a buscar
   * @return int el tamaño del tipo
   */
  int get_tam(int id) {
    for (tipo_s tipo : tabla)
        if (tipo.id == id)
            return tipo.tam;
    return -1;
  }

  /**
   * Da el elemento de un tipo dado su identificador
   * @param int el identificador del tipo a buscar
   * @return int el elemento del tipo
   */
  int get_elem(int id) {
    for (tipo_s tipo : tabla)
        if (tipo.id == id)
            return tipo.elem;
    return -1;
  }

  /**
   * Da la base de un tipo dado su identificador
   * @param int el identificador del tipo a buscar
   * @return int la base del tipo
   */
  int get_base(int id) {
    for (tipo_s tipo : tabla)
        if (tipo.id == id)
            return tipo.tipoBase;
    return -1;
  }
};
