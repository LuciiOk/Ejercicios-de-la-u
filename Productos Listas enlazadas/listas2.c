#include <stdio.h>
#include <stdlib.h>

struct Producto{
	int codigo;
	int precio;
};

struct NodoProducto {
	struct Producto *datosProducto;
	struct NodoProducto *siguiente;
};

struct Producto *crearProducto();
struct NodoProducto *crearNodo (struct Producto *nuevo);
int buscarProducto(struct NodoProducto *head, int codigoProducto);
int agregarNuevoProducto (struct NodoProducto **head, struct NodoProducto *nuevo);
int eliminarProducto(struct NodoProducto **head, int codigo);
void mostrarLista(struct NodoProducto *lista);

int main() {
	int opcion = 1;
	struct NodoProducto *head = NULL;
	
	while (opcion != 4) {
		printf("Seleccione una opcion:\n");
		printf("1. Agregar Producto\n");
		printf("2. Eliminar Producto\n");
		printf("3. Mostrar lista\n");
		printf("4. Salir\n");
		scanf("%i", &opcion);
		
		if (opcion == 1)
			if (agregarNuevoProducto(&head, crearNodo(crearProducto())))
				printf("El Producto se ha agregado.\n");
			else 
				printf("El Producto no se ha podido agregar.\n");
		if (opcion == 2) {
			int eliminar;
			printf("Ingrese el codigo del producto que desea eliminar: \n");
			scanf("%i", &eliminar);
			if (eliminarProducto(&head, eliminar))
				printf("El producto se ha eliminado satisfactoriamente.\n");
			else 
				printf("El producto no se ha podido eliminar.\n");
		}
		if (opcion == 3)
			mostrarLista(head);
		if (opcion == 4)
			return 0;
	}
}

struct Producto *crearProducto() {
	struct Producto *nuevo;
	
	nuevo = (struct Producto*) malloc (sizeof(struct Producto));
	
	printf("Ingrese codigo del producto: \n");
	scanf("%i", &nuevo->codigo);
	printf("Ingrese el precio: \n");
	scanf("%i", &nuevo->precio);
	
	return nuevo;
}

struct NodoProducto *crearNodo (struct Producto *nuevo) {
	struct NodoProducto *nuevoNodo;
	
	nuevoNodo = (struct NodoProducto *) malloc (sizeof(struct NodoProducto));
	
	nuevoNodo->datosProducto = nuevo;
	nuevoNodo->siguiente = NULL;
	
	return nuevoNodo;
}

int buscarProducto(struct NodoProducto *head, int codigoProducto) {
	
	while (head != NULL) {
		if (head->datosProducto->codigo == codigoProducto) {
			return 1;
		}
		head = head->siguiente;
	}
	return 0;
}

int agregarNuevoProducto (struct NodoProducto **head, struct NodoProducto *nuevo) {
	struct NodoProducto *rec;
	
	if (buscarProducto(*head, nuevo->datosProducto->codigo) == 0) {
		if (*head == NULL) {
			*head = nuevo;
			return 1;
		}
		rec = *head;
		
		while (rec->siguiente!= NULL) {
			rec = rec->siguiente; 
		} 
		rec->siguiente = nuevo;
		return 1;
	}
	return 0;
}

void mostrarLista(struct NodoProducto *lista) {
	while (lista) {
		printf("%i, %i \n", lista->datosProducto->codigo, lista->datosProducto->precio);
		lista= lista->siguiente;
	}	
}

int eliminarProducto (struct NodoProducto **head, int codigo) {
	struct NodoProducto *rec;
	
	if ((*head)->datosProducto->codigo == codigo) {
		(*head) = (*head)->siguiente;
		return 1;
	}
	
	rec = *head;
	
	while (rec->siguiente != NULL) {
		if (rec->siguiente->datosProducto->codigo == codigo) {
			rec->siguiente = rec->siguiente->siguiente;
			return 1;
		}
		rec = rec->siguiente;
	}
	return 0;
}
