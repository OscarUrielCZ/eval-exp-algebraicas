#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "tree.h"

int esParentesisIzq(char c) {
	return c == '(';
}

int esParentesisDer(char c) {
	return c == ')';
}

int esNumero(char *c) {
	return c[0] >= '0' && c[0] <= '9';
}

int esOperador(char *c) {
	return c[0] == '*' || c[0] == '+' || c[0] == '/' || c[0] == '-';
}

char* concat(char *c1, char *c2) {
	char *cad;
	int i;

	cad = (char*)malloc(sizeof(char)*(strlen(c1) + strlen(c2)));
	
	for (i = 0; i < strlen(c1); i++)
		cad[i] = c1[i];

	for(i = 0; i < strlen(c2); i++)
		cad[strlen(c1) + i] = c2[i];

	return cad;
}

char* aCadena(char c) {
	char *cad;

	cad = (char*)malloc(sizeof(char));

	cad[0] = c;

	return cad;
}

char* sufijo(char *c, int pos) {
	char *cad;
	int i;

	cad = (char*)malloc(sizeof(char)*(strlen(c) - pos));
	
	for(i = 0; i < strlen(c) - pos; i++)
		cad[i] = c[pos + i];

	return cad;
}

int jerarquia(char *c) {
	if(strcmp(c, "+") == 0 || strcmp(c, "-") == 0)
		return 1;
	else if(strcmp(c, "*") == 0 || strcmp(c, "/") == 0)
		return 2;
	else
		return 3;
}

Tree agregarNumero(Tree t, DataT d) { // agrega el numero lo más a la derecha posible
	if(isEmptyT(t))
		return create(emptyT(), d, emptyT());
	return create(leftBranch(t), root(t), agregarNumero(rightBranch(t), d));
}

Tree agregarFinDer(Tree t1, Tree t2) {
	if(isEmptyT(t1))
		return t2;
	return create(leftBranch(t1), root(t1), agregarFinDer(rightBranch(t1), t2));
}

Tree cargarArbol(char *cadena) {
	int i = 0, op = 0;
	char *sd;
	Stack s = empty();
	Tree t = emptyT();

	while(cadena[i] != '\0') {
		if(esNumero(aCadena(cadena[i]))) {
			sd = aCadena(cadena[i]);
			while(esNumero(aCadena(cadena[i+1]))) { // obtener todos los digitos
				sd = concat(sd, aCadena(cadena[++i]));
			}
			t = agregarNumero(t, sd);

		} else if(esOperador(aCadena(cadena[i]))) {
			if(op == 1 && jerarquia(aCadena(cadena[i])) > jerarquia(root(t))) {
				t = create(leftBranch(t), root(t), create(rightBranch(t), aCadena(cadena[i]), emptyT()));
			} else {
				t = create(t, aCadena(cadena[i]), emptyT());
			}
			op = 1;
		} else if(esParentesisIzq(cadena[i])) {
			if(isEmpty(s)) {
				s = push(aCadena(cadena[i]), s);
				t = agregarFinDer(t, cargarArbol(sufijo(cadena, i+1)));
				while(!isEmpty(s)) {
					i++;
					if(esParentesisIzq(cadena[i]))
						s = push(aCadena(cadena[i]), s);
					else if(esParentesisDer(cadena[i]))
						s = pop(s);
				}
				op = 0;
			} else {
				s = push(aCadena(cadena[i]), s);
			}

		} else { // es parentesis derecho
			return t;
		}

		i++;
	}

	return t;
}

int resolverArbol(Tree t) {
	if(isEmptyT(leftBranch(t)) || isEmptyT(rightBranch(t)))
		return atoi(root(t));

	if(strcmp(root(t), "+") == 0) return resolverArbol(leftBranch(t)) + resolverArbol(rightBranch(t));
	else if(strcmp(root(t), "-") == 0) return resolverArbol(leftBranch(t)) - resolverArbol(rightBranch(t));
	else if(strcmp(root(t), "*") == 0) return resolverArbol(leftBranch(t)) * resolverArbol(rightBranch(t));
	else if(strcmp(root(t), "/") == 0) {
		int den = resolverArbol(rightBranch(t));

		if(den == 0) {
			printf("ERROR: división por 0.\n");
			exit(0);
		}
		return resolverArbol(leftBranch(t)) / den;
	}
}

int main(int argc, char **argv) {
	Tree t = emptyT();
	char *cadena = *++argv;

	t = cargarArbol(cadena);
	printf("%d\n", resolverArbol(t));

	return 0;
}