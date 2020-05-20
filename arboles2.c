#include <stdio.h>
#include <stdlib.h>

struct nodo {
	int numero;
	struct nodo *der, *izq;
};

void insertar (struct nodo **arbol, int numero);
void mostar(struct nodo *arbol);
void reemplazar (struct nodo **arbol);
void eliminarPersonalizado(struct nodo **arbol, int numero);

int main () {
	struct nodo *arbol = NULL;
	
	insertar(&arbol, 4);
	insertar(&arbol, 2);
	insertar(&arbol, 1);
	insertar(&arbol, 3);
	insertar(&arbol, 6);
	insertar(&arbol, 5);
	insertar(&arbol, 7);
	
	mostar(arbol);
	
	eliminarPersonalizado(&arbol, 1);
	printf("\n");
	mostar(arbol);
	
	return 0;
}

void insertar (struct nodo **arbol, int numero) {
	if (!(*arbol)) {
		(*arbol) = (struct nodo *) malloc (sizeof(struct nodo));
		(*arbol)->numero = numero;
		(*arbol)->izq=(*arbol)->der=NULL;
	} else {
		if ((*arbol)->numero != numero) {
			if ((*arbol)->numero < numero) {
				insertar(&((*arbol)->der), numero);
			} else {
				insertar(&((*arbol)->izq), numero);
			}
		}
	}
}

void mostar(struct nodo *arbol) {
	if (arbol) {
		mostar(arbol->izq);
		printf("%i -", arbol->numero);
		mostar(arbol->der);
	}
	return ;
}

void reemplazar (struct nodo **arbol) {
	if (!(*arbol)->izq) {
		*arbol = (*arbol)->der;
	} else if ((!(*arbol)->der)){
		*arbol = (*arbol)->izq;
	} else 
	reemplazar(&(*arbol)->der);
}

void eliminarPersonalizado(struct nodo **arbol, int numero) {
	
	if ((*arbol)->numero == numero) {
		reemplazar(&(*arbol));
	} else {
		if ((*arbol)->numero < numero) {
			eliminarPersonalizado(&(*arbol)->der, numero);
		} else {
			eliminarPersonalizado(&(*arbol)->izq, numero);
		}
	}
}
