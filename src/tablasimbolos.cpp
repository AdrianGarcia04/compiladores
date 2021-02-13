#include "tablasimbolos.h"

void tabla_simbolos::imprimir(){
    printf("ID\ttipo\tdir\tvar\n");
    for (simbolo s : tabla) {
        printf("%s\t%d\t%d\t%d\n", s.id.c_str(), s.tipo, s.dir,s.var);
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
/*
void pila_simbolos::push( ) {
    pila.push(tabla_simbolos());
}

void pila_simbolos::pop() {
    pila.pop();
}

tabla_simbolos pila_simbolos::top() {
    return pila.top();
}


*/
