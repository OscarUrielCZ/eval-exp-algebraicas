# Evaluador de expresiones aritmeticas

Es una aplicación para la terminal de comandos hecha en lenguaje C, para saber el valor de una expresión aritmetica. Hace uso de una pila y de un árbol binario.

## Requisitos

Compilador para lenguaje C, GCC (se recomienda tener como mínimo la versión 7.5.0).

## Compilar

En la terminal de comandos, dentro del directorio del proyecto ejecutar:
```
gcc evaluacion.c -o eval
```

## Ejecutar

Dentro del mismo directorio usar el comando
```
./eval "(1+2*(5+6))"
```
La cadena entre comillas dobles es tu expresión algebraica

![Imagen de evaluación de expresiones aritméticas](https://raw.githubusercontent.com/OscarUrielCZ/eval-exp-algebraicas/master/assets/evaluaciones.png)