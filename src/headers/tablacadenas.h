#pragma once
#include <string>
#include <list>
using namespace std;

/**
 * Estructura para representar símbolos de la tabla de cadenas
 * list<string> tabla
 */
struct tablacadenas {
  list<string> tabla;

  /**
   * Constructor vacío
   * @return tablacadenas
   */
  tablacadenas(){}

  /**
   * Constructor con parámetros
   * @param tabla
   * @return tablacadenas
   */
  tablacadenas(list<string> tabla) : tabla(tabla){}

  /**
   * Da la representación en cadena de la tabla de cadenas
   * @return string
   */
  string str() {
    string str = "";
    for (string cadena : tabla)
        str = str + cadena + "\n";
    return str;
  }

  /**
   * Agrega una cadena a la tabla de cadenas
   * @param string la cadena a agregar
   */
  void agregar(string cadena) {
    tabla.push_back(cadena);
  }

  /**
   * Elimina una cadena de la tabla
   * @param string la cadena a eliminar
   */
  void eliminar(string cadena) {
    tabla.remove(cadena);
  }
};
