#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;


Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//STIVA

typedef struct Nod Nod;
struct Nod {
	Nod* next;
	Masina info;
};

void pushStack(Nod** stiva, Masina masina) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masina;
	nou->next = (*stiva);
	(*stiva) = nou;
}

Masina popStack(Nod** stiva) {
	if ((*stiva) != NULL)
	{
		Masina m = (*stiva)->info;
		Nod* aux = (*stiva);
		(*stiva) = (*stiva)->next;
		free(aux);
		return m;
	}
	Masina m;
	m.id = -1;
	return m;
}

int sizeStack(Nod* stiva) {
	int nr = 0;
	while (stiva) {
		stiva = stiva->next;
		nr++;
	}
	return nr;
}

void dezalocaStiva(Nod** stiva) {
	while ((*stiva)!=NULL)
	{
		Masina m = popStack(stiva);
		free(m.model);
		free(m.numeSofer);
	}
}

//QUEUE

typedef struct NodDublu NodDublu;
struct NodDublu {
	NodDublu* prev;
	NodDublu* next;
	Masina info;
};
typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	NodDublu* primul;
	NodDublu* ultimul;
};

void adaugaMasinaInCoada(ListaDubla** coada, Masina masina) {
		NodDublu* nou = malloc(sizeof(NodDublu));
		nou->info = masina;
		nou->next = NULL;
		nou->prev = (*coada)->ultimul;
	if ((*coada)->ultimul != NULL) {
		(*coada)->ultimul->next = nou;
	}
	else {
		(*coada)->primul = nou;
	}
	(*coada)->ultimul = nou;
}

Masina dequeue(ListaDubla** coada) {
	Masina m;
	m.id = -1;
	if ((*coada)->primul != NULL)//lista nu e goala
	{
		m = (*coada)->primul->info;
		NodDublu* aux = (*coada)->primul;
		if ((*coada)->primul->next != NULL)//daca mai am ceva dupa nodul extras 
		{
			(*coada)->primul = (*coada)->primul->next;
			(*coada)->primul->prev = NULL;
		}
		else  //daca nu, lista nula
		{
			(*coada)->primul = NULL;
			(*coada)->ultimul = NULL;
		}
		free(aux);
	}
	return m;
}

ListaDubla citireCoadaDinFisier(const char* numeFisier) {
	ListaDubla coada;
	coada.primul = NULL;
	coada.ultimul = NULL;

	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		Masina m = citireMasinaDinFisier(file);
		adaugaMasinaInCoada(&coada, m);
	}
	fclose(file);
	return coada;
}

void dezalocCoada(ListaDubla* coada) {
	NodDublu* aux = coada->ultimul;
	while (aux) {
		NodDublu* temp = aux;
		aux = aux->prev;
		free(temp);//...
	}
	coada->primul = NULL;
}