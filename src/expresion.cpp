#include "expresion.h"
#include <stdlib.h>

exp *crea_exp() {
    exp *expresion = (exp *)malloc(sizeof(exp));
    return expresion;
}