#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define MAXZOMBIES 10000

struct zombie {
	int idZombie;
	char *nombreHumano;
	float indiceLetalidad;
};

struct ciudad {
	char *nombre;
	int codigo;
	char *nombreAlcalde;
	struct zombie **zombies;
};

struct nodoCiudad {
	struct ciudad *datoCiudad;
	struct nodoCiudad *siguiente;
};

struct pais {
	char *nombre;
	char *presidente;
	struct nodoCiudad *nodo;
};

int crearPais();
struct ciudad *crearCiudad();
struct zombie *crearZombie();
struct nodoCiudad *crearNodo(struct ciudad *nuevaCiudad);
int agregarCiudad (struct nodoCiudad **head, struct nodoCiudad *nuevo);
int buscarCiudad(struct nodoCiudad *head, int cidudad);
int agregarZombie(struct zombie **arreglo,struct zombie *nuevo);
float promedioPeligrosidadCiudad(struct zombie **arreglo);
float promedioPeligrosidadCiudadesLista(struct nodoCiudad *head);
void mostrarDatos(struct pais *Pais);
void mostrarLista(struct nodoCiudad *lista);
void mostrarArreglo(struct zombie **arreglo);
void menuOperaciones(struct pais *Pais);
int eliminarZombie(struct zombie **arreglo, int idEliminar);
int eliminaMenorPromedioGeneral(struct nodoCiudad **head);
int eliminarCiudad(struct nodoCiudad **head, int codigoCiudad);

int main() {
	struct pais *Pais;
	
	if (crearPais(&Pais)) {
		printf("El pais se ha creado satisfactoriamente.\n");
	} else {
		printf("El pais no se ha podido crear.\n"); 
		return EXIT_FAILURE;
	}
	
	mostrarDatos(Pais);
	menuOperaciones(Pais);
	
	return EXIT_SUCCESS;
}

int crearPais(struct pais **neww) {
	struct pais *nuevo;
	char buffer[MAX];
	
	nuevo = (struct pais *) malloc (sizeof(struct pais));
	if (nuevo == NULL)
		return 0;
	
	printf("Ingrese el nombre del pais: \n");
	scanf("%s", buffer);
	
	nuevo->nombre = (char *) malloc (strlen(buffer) * sizeof(char ));	
	strcpy(nuevo->nombre, buffer);
	
	printf("Ingrese el nombre del presidente:\n");
	scanf("%s", buffer);
	
	nuevo->presidente = (char *) malloc (strlen(buffer) * sizeof(char));
	strcpy(nuevo->presidente, buffer);
	
	nuevo->nodo = NULL;
	
	int opcion;
	printf("Desea ingresear una ciudad?\n (SI: 1 / NO: 0):\n");
	scanf("%i", &opcion);
	
	while (opcion != 0) {
		if (opcion == 0) 
			break;
			
		if (agregarCiudad(&(nuevo)->nodo, crearNodo(crearCiudad())) == 1) {
			printf("La ciudad se ha creado satisfactoriamente.\n");
		} else {
			printf("La ciudad no se ha creado.\n");
		}
		printf("Desea ingresear una ciudad?\n (SI: 1 / NO: 0):\n");
		scanf("%i", &opcion);
	} 
	
	*neww = nuevo;
	
	return 1;
}

void menuOperaciones(struct pais *Pais) {
	struct nodoCiudad *rec;
	int opcion, codigo, id, cont;
	printf("\n");
	while (1) {
		printf("Seleccione la operacion que desea ejecutar:\n\n");
		printf("0. Salir del programa.\n");
		printf("1. Agregar Zombie.\n");
		printf("2. Agregar Ciudad.\n");
		printf("3. Eliminar Zombie.\n");
		printf("4. Eliminar Ciudad.\n");
		printf("5. Obtener promedio general.\n");
		printf("6. Eliminar ciudad menor al promedio general.\n");
		
		scanf("%i", &opcion);
		
		switch (opcion) {
			case 1: 
				printf("Ingrese el codigo de la ciudad donde quiere agregar al zombie: \n");
				scanf("%i", &codigo);
				
				rec = Pais->nodo;
				
				while (rec->siguiente != NULL) {
					if (rec->datoCiudad->codigo == codigo)
						break;
					rec = rec->siguiente;
				}
				
				if (agregarZombie(rec->datoCiudad->zombies, crearZombie())) {
					printf("El zombie se ha agregado.\n");
				} else {
					printf("El zombie no se ha agregado.\n");
				}
				break;
			
			case 2:
				if (agregarCiudad(&Pais->nodo, crearNodo(crearCiudad()))) {
					printf("La ciudad se ha creado satisfactoriamente.\n");
				} else {
					printf("La ciudad no se ha creado.\n");
				}
				break;
			
			case 3:
				printf("Ingrese el codigo de la ciudad:\n");
				scanf("%i", &codigo);
				printf("Ingrese la id del zombie: \n");
				scanf("%i", &id);
				
				rec = Pais->nodo;
				
				while (rec->siguiente != NULL) {
					if (rec->datoCiudad->codigo == codigo)
						break;
					rec = rec->siguiente;
				}
				
				if (eliminarZombie(rec->datoCiudad->zombies, id)) {
					printf("El zombie se ha eliminado sastisfactoriamente.\n");
				} else {
					printf("El zombie no se pudo eliminar.\n");
				}
				break;
			case 4:
				printf("Ingrese el codigo de la ciudad que desea eliminar: \n");
				scanf("%i", &codigo);
				
				if (eliminarCiudad(&Pais->nodo, codigo)) {
					printf("La ciudad se ha eliminado satisfactoriamente.\n");
				} else {
					printf("La ciudad no se ha eliminado.\n");
				}
				break;
			case 5:
				printf("El promedio general es: %.2f\n", promedioPeligrosidadCiudadesLista(Pais->nodo));
				break;
			case 6:
				cont = eliminaMenorPromedioGeneral(&Pais->nodo);
				if (cont > 0) {
					printf("Se han eliminado %i ciudades.\n", cont);
				} else {
					printf("No se ha eliminado ninguna ciudad.\n");
				}
				break;
			case 7:
				mostrarDatos(Pais);
				break;
			default:
				exit(0);
		}
	}
}

struct ciudad *crearCiudad() {
	int i;
	struct ciudad *nuevo;
	char buffer[MAX];
	
	nuevo = (struct ciudad *) malloc (sizeof(struct ciudad));
	
	printf("Ingrese el nombre de la ciudad:\n");
	scanf("%s", buffer);
	
	nuevo->nombre = (char *) malloc (strlen(buffer) * sizeof(char ));
	strcpy(nuevo->nombre, buffer);
	
	printf("Ingrese el codigo de la ciudad:\n");
	scanf("%i", &nuevo->codigo);
	
	printf("Ingrese el nombre del alcande:\n");
	scanf("%s", buffer);
	
	nuevo->nombreAlcalde = (char *) malloc (strlen(buffer) * sizeof(char ));
	strcpy(nuevo->nombreAlcalde, buffer);
	
	nuevo->zombies = (struct zombie **) malloc (MAXZOMBIES * sizeof(struct zombie *));
		for (i = 0; i < MAXZOMBIES; i++)
			nuevo->zombies[i] = NULL;
	
	int opcion;
	printf("Desea ingresar un zombie?\n(SI: 1 / NO: 0):\n");
	scanf("%i", &opcion);
	
	while (opcion != 0) {
		
		if (agregarZombie(nuevo->zombies, crearZombie())) {
			printf("El zombie se ha agregado.\n");
		} else {
			printf("El zombie no se ha agregado.\n");
		}
		
		printf("Desea ingresar un zombie?\n(SI: 1 / NO: 0):\n");
		scanf("%i", &opcion);
	}
	
	return nuevo;
}

struct nodoCiudad *crearNodo(struct ciudad *nuevaCiudad) {
	struct nodoCiudad *nuevo;
	
	nuevo = (struct nodoCiudad *) malloc (sizeof(struct nodoCiudad));
	
	nuevo->datoCiudad = nuevaCiudad;
	nuevo->siguiente = NULL;
	
	return nuevo;
}

int agregarCiudad (struct nodoCiudad **head, struct nodoCiudad *nuevo) {
	struct nodoCiudad *recorrido;
	
	if (buscarCiudad(*head, nuevo->datoCiudad->codigo) == 0) {
		if (*head == NULL) {
			*head = nuevo;
			return 1;
		} 
		
		recorrido = *head;
		
		while (recorrido->siguiente != NULL) {
			recorrido = recorrido->siguiente;
		}
		recorrido->siguiente = nuevo;
		return 1;
	}
	
	return 0;
}

int buscarCiudad(struct nodoCiudad *head, int cidudad) {
	while (head != NULL) {
		if (head->datoCiudad->codigo == cidudad) {
			return 1;
		}
		head = head->siguiente;
	}
	
	return 0;
}

struct zombie *crearZombie() {
	struct zombie *nuevo;
	char buffer[MAX];
	
	nuevo = (struct zombie *) malloc (sizeof(struct zombie));
	
	printf("Ingrese el id del zombie:\n");
	scanf("%i", &nuevo->idZombie);
	
	printf("Ingrese el nombre humano del zombie:\n");
	scanf("%s", &buffer);
	
	nuevo->nombreHumano = (char * ) malloc (strlen(buffer) * sizeof(char ));
	strcpy(nuevo->nombreHumano, buffer);
	
	printf("Ingrese el indice de letalidad:\n");
	scanf("%f", &nuevo->indiceLetalidad);
	
	return nuevo;
}

int agregarZombie(struct zombie **arreglo, struct zombie *nuevo) {
	int i;
	
	if (arreglo != NULL && !buscarZombie(arreglo, nuevo->idZombie)) {
		for (i = 0; i < MAXZOMBIES; i++) {
			if (arreglo[i] == NULL) {
				arreglo[i] = nuevo;
				return 1;
			}
		}
	}
	
	return 0;
}

int buscarZombie(struct zombie **arreglo, int idZombie) {
	int i;
	
	for (i = 0; i < MAXZOMBIES && arreglo[i] != NULL; i++) {
		if (arreglo[i]->idZombie == idZombie) {
			return 1;
		}
	} 
	return 0;
}

float promedioPeligrosidadCiudad(struct zombie **arreglo) {
	float promedio = 0;
	int i, contador = 0; 
	
	for (i = 0; i < MAXZOMBIES; i++) {
		if (arreglo[i] != NULL) {
			promedio += arreglo[i]->indiceLetalidad;
			contador++;
		}
	}
	
	return (contador > 0) ? promedio / contador : promedio;
}

float promedioPeligrosidadCiudadesLista(struct nodoCiudad *head) {
	float promedio = 0;
	int contador = 0;
	
	while (head != NULL) { 	
		promedio += promedioPeligrosidadCiudad(head->datoCiudad->zombies);
		contador++;
		head = head->siguiente;
	}
	
	return (contador > 0) ? promedio / contador : promedio;
}

void mostrarDatos(struct pais *Pais) {
	system("cls");
	printf("=======================================================================================\n\n");
	printf("Pais: %s\tPresidente: %s\n\n", Pais->nombre, Pais->presidente);
	printf("=======================================================================================\n\n");
	
	mostrarLista(Pais->nodo);
	
}

void mostrarLista(struct nodoCiudad *lista) {
	while (lista != NULL) {
		printf("Codigo ciudad: %i\tNombre: %s\tAlcalde: %s \n\n", lista->datoCiudad->codigo, lista->datoCiudad->nombre, lista->datoCiudad->nombreAlcalde);
		mostrarArreglo(lista->datoCiudad->zombies);
		printf("Promedio Letalidad: %.2f\n\n", promedioPeligrosidadCiudad(lista->datoCiudad->zombies));
		printf("=======================================================================================\n\n");
		lista = lista->siguiente;
	}
	
	printf("=======================================================================================\n\n");
}

void mostrarArreglo(struct zombie **arreglo) {
	int i;
	
	for (i = 0; arreglo[i] != NULL; i++)
		printf("\tIdentificador: %i  Nombre humano: %s  Indice Letalidad: %.2f\n\n", arreglo[i]->idZombie, arreglo[i]->nombreHumano, arreglo[i]->indiceLetalidad);
	
}

int eliminarZombie(struct zombie **arreglo, int idEliminar) {
	int i, j;
	
	for (i = 0; arreglo[i] != NULL; i++) {
		if (arreglo[i]->idZombie == idEliminar) {
			arreglo[i] = NULL;
			for (j = i; arreglo[j - 1] != NULL; j++)
				arreglo[j] = arreglo[j + 1];
			return 1;
		}
	}
	return 0;
}

int eliminarCiudad(struct nodoCiudad **head, int codigoCiudad) {
	struct nodoCiudad *rec;
	
	if ((*head)->datoCiudad->codigo == codigoCiudad) {
		(*head) = (*head)->siguiente;
		return 1;
	}
	
	rec = *head;
	
	while (rec->siguiente != NULL) {
		if (rec->siguiente->datoCiudad->codigo == codigoCiudad) {
			rec->siguiente = rec->siguiente->siguiente;
			return 1;
		}
		rec = rec->siguiente;
	}
	return 0;
}

int eliminaMenorPromedioGeneral(struct nodoCiudad **head) {
	struct nodoCiudad *rec;
	int contador = 0;
	float promedio = promedioPeligrosidadCiudadesLista(*head);
	
	if (*head) {
		while (*head != NULL && promedioPeligrosidadCiudad((*head)->datoCiudad->zombies) < promedio) {
			(*head) = (*head)->siguiente;
			contador++;
		}
		
		rec = *head;
		
		if (*head != NULL) {
			while (rec->siguiente != NULL) {
				if (promedioPeligrosidadCiudad(rec->datoCiudad->zombies) < promedio) {
					rec->siguiente = rec->siguiente->siguiente;
					contador++;
				}
			rec = rec->siguiente;
			}
		}
	}
	
	return contador;
}
