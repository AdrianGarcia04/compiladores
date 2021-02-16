#include "tablasimbolos.h"
#include <iostream>
#include <stdlib.h>
#include <stack>
using namespace std;

void tabla_simbolos::imprimir(){
    cout << "ID\ttipo\tdir\tvar\n";
    for (simbolo s : tabla) {
        cout << s.id.c_str() << "\t" << s.tipo << "\t" << s.dir << "\t" << s.var << "\n";
    }
}

bool tabla_simbolos::buscar(string id) {
    for (simbolo s : tabla) {
        if (s.id == id) return true;
    }
    return false;
}

bool tabla_simbolos::insertar(simbolo s) {
    if (!buscar(s.id)) {
        tabla.push_back(s);
        return true;
    }
    return false;
}

int tabla_simbolos::getTipo(string id) {
    for (simbolo s : tabla) {
        if (s.id == id) return s.tipo;
    }
    return -1;
}

void pila_simbolos::push(tabla_simbolos* tabla) {
    pila.push(tabla);
}

void pila_simbolos::pop() {
    pila.pop();
}

tabla_simbolos* pila_simbolos::top() {
    return pila.top();
}

pila_simbolos* crear_pila_simbolos() {
  return (pila_simbolos*)malloc(sizeof(pila_simbolos));
}

tabla_simbolos* crear_tabla_simbolos() {
    return (tabla_simbolos*)malloc(sizeof(tabla_simbolos));
}

void pila_simbolos::insertar_tabla() {
    tabla_simbolos* tabla = crear_tabla_simbolos();
    pila.push(tabla)
}