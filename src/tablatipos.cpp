#include "tablatipos.h"
#include <iostream>
#include <stack>
using namespace std;

void tabla_tipos::imprimir(){
    cout << "ID\ttipo\tdir\tvar\n";
    for (tipo t : tabla) {
        cout << t.id << "\t" << t.tipo << "\t" << t.tam << "\t" << t.elem << t.tipoBase << "\n";
    }
}

bool tabla_tipos::buscar(int id) {
    for (tipo t : tabla)
        if (t.id == id) return true;
    return false;
}

bool tabla_tipos::insertar(tipo t) {
    if (!buscar(t.id)) {
        tabla.push_back(t);
        return true;
    }
    return false;
}

void pila_tipos::push(tabla_tipos* tabla) {
    pila.push(tabla);
}

void pila_tipos::pop() {
    pila.pop();
}

tabla_tipos* pila_tipos::top() {
    return pila.top();
}


pila_tipos* crear_pila_tipos() {
  return (pila_tipos*)malloc(sizeof(pila_tipos));
}

tabla_tipos* crear_tabla_tipos() {
    return (tabla_tipos*)malloc(sizeof(tabla_tipos));
}

void pila_tipos::insertar_tabla() {
    tabla_tipos* tabla = crear_tabla_tipos();
    pila.push(tabla);
}
