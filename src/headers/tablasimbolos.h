#pragma once
#include <string>
#include <list>
using namespace std;

/**
 * Estructura para representar símbolos de la tabla de símbolos
 * string id
 * int dir
 * int tipo
 * string var
 * list<int> args
 */
struct simbolo {
  string id;
  int dir;
  int tipo;
  string var;
  list<int> args;

  /**
   * Constructor vacío
   * @return simbolo
   */
  simbolo(){}

  /**
   * Constructor con parámetros
   * @param id
   * @param dir
   * @param tipo
   * @param var
   * @param args
   * @return simbolo
   */
  simbolo(string id, int dir, int tipo, string var, list<int> args) : id(id), dir(dir), tipo(tipo), var(var), args(args){}

  /**
   * Da la representación en cadena del simbolo
   * @return string
   */
  string str() {
    return id
        + "\t" + std::to_string(dir)
        + "\t" + std::to_string(tipo)
        + "\t" + var;
  }

  /**
   * Operador de comparación para símbolos
   * @param simbolo símbolo a comparar
   * @return bool true en caso de ser iguales, false en otro caso
   */
  bool operator==(const struct simbolo& a) const {
    return a.id == this->id;
  }
};


/**
 * Estructura para representar la tabla de símbolos
 * list<simbolo> tabla
 */
struct tablasimbolos {
  list<simbolo> tabla;

  /**
   * Constructor vacío
   * @return tablasimbolos
   */
  tablasimbolos(){}

  /**
   * Constructor con parámetros
   * @param tabla
   * @return tablasimbolos
   */
  tablasimbolos(list<simbolo> tabla) : tabla(tabla){}

  string str() {
    string str = "";
    for (simbolo simbolo : tabla)
        str = str + simbolo.str() + "\n";
    return str;
  }

  /**
   * Agrega un símbolo a la tabla de símbolos
   * @param simbolo el símbolo a agregar
   */
  void agregar(simbolo simbolo) {
    tabla.push_back(simbolo);
  }

  /**
   * Elimina un símbolo de la tabla
   * @param simbolo el símbolo a eliminar
   */
  void eliminar(simbolo simbolo) {
    tabla.remove(simbolo);
  }

  /**
   * Busca un símbolo en la tabla
   * @param string el identificador del símbolo a buscar
   * @return bool true si se encuentra el símbolo, false en otro caso
   */
  bool buscar(string id) {
    for (simbolo simbolo : tabla)
        if (simbolo.id == id)
            return true;
    return false;
  }

  /**
   * Da el tipo de un símbolo dado su identificador
   * @param string el identificador del símbolo a buscar
   * @return int el tipo del símbolo
   */
  int get_tipo(string id) {
    for (simbolo simbolo : tabla)
        if (simbolo.id == id)
            return simbolo.tipo;
    return -1;
  }

  /**
   * Da la variable de un símbolo dado su identificador
   * @param string el identificador del símbolo a buscar
   * @return string la variable del símbolo
   */
  string get_var(string id) {
    for (simbolo simbolo : tabla)
        if (simbolo.id == id)
            return simbolo.var;
    return NULL;
  }
};
