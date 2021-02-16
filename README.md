# Compiladores 2021-1 | Proyecto Final

## Instrucciones para compilación y ejecución
1. Hacer `make` desde el directorio src/
2. Ejecutar: ./bin/parser prueba.in

## Gramática:

+ programa = A
+ declaraciones = B
+ tipo = C
+ basico = D
+ compuesto = E
+ lista_var = F
+ funciones = G
+ argumentos = H
+ lista_args = I
+ bloque = J
+ instrucciones = K
+ sentencia = L
+ casos = M
+ caso = N
+ predeterminado = O
+ parte_izquierda = P
+ bool = Q
+ comb = R
+ igualdad = S
+ rel = T
+ exp = U
+ term = V
+ unario = W
+ factor = X
+ parametros = Y
+ lista_param = Z
+ localizacion = AA

## Gramática traducida y LL1

+ A -> B G
+ B -> C F;B | epsilon
+ C -> D E
+ D- > **int** | **float** | **char** | **double** | **void**
+ E -> **[numero]** E | epsilon
+ F -> **id** F'
+ F' -> **,id** F' | epsilon
+ G -> **func** C **id(** H **)** J G | epsilon
+ H -> I | epsilon
+ I -> C **id** I'
+ I' -> **,** C **id** I' | epsilon
+ J -> **{** B K **}**
+ K -> L K'
+ K' -> L K' | epsilon
+ L -> P **=** Q; | **if(** Q **)** L L' | **while(** Q **)** L | **do** L **while(** Q **)**
   | **break;**| J | **return** L'' | **switch(** Q **){** M **}**| **print** U **;** | **scan** P
+ L' -> **else** L | epsilon
+ L'' -> U **;** | **;**
+ M -> N M | O | epsilon
+ N -> **case numero:** K
+ O -> **default:** K
+ P -> **id** P'
+  P' -> AA | epsilon
+ Q -> R Q'
+ Q' -> **||** R Q' | epsilon
+ R -> S R'
+ R' -> **&&** S R' | epsilon
+ S -> T S'
+ S' -> **==** T S' | **!=** T S' | epsilon
+ T -> U T'
+ T' -> **<** U | **<=** U | **>=** U | **>** U | epsilon
+ U -> V U'
+ U' -> **+** V U' | **-** V U' | epsilon
+ V -> W V'
+ V' -> * W V' | **/** W V' | **%** W V' | epsilon
+ W -> **!** W | **-** W | X
+ X -> **(** Q **)** | **id** X' | **numero** | **cadena** | **true** | **false**
+ X' -> AA | **(** Y **)** | epsilon
+ Y -> Z | epsilon
+ Z -> Q Z'
+ Z' -> ,Q Z' | epsilon
+ AA -> **[Q]** AA'
+ AA' -> **[Q]** AA' | epsilon
