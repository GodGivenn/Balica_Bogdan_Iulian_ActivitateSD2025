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
typedef struct Nod Nod;
//creare structura pentru un nod dintr-un arbore binar de cautare
struct Nod {
	Masina info;
	Nod* st;
	Nod* dr;
};

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

void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	if ((*radacina) != NULL) {
		if (masinaNoua.id < (*radacina)->info.id)
			adaugaMasinaInArbore(&((*radacina)->st), masinaNoua);
		else if (masinaNoua.id > (*radacina)->info.id)
			adaugaMasinaInArbore(&((*radacina)->dr), masinaNoua);
	}
	else
	{
		(*radacina) = (Nod*)malloc(sizeof(Nod));
		(*radacina)->info = masinaNoua;
		(*radacina)->st = NULL;
		(*radacina)->dr = NULL;
	}
}

Nod* citireArboreDeMasiniDinFisier(char* const numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(file))
	{
		adaugaMasinaInArbore(&radacina, citireMasinaDinFisier(file));
	}
	fclose(file);
	return radacina;
}

void afisareArborePreOrdine(Nod* radacina) {
	if (radacina != NULL)
	{
		afisareMasina(radacina->info);
		afisareArborePreOrdine(radacina->st);
		afisareArborePreOrdine(radacina->dr);
	}
}

int calculeazaInaltime(Nod** radacina) {
	if ((*radacina) != NULL) {
		int inaltimeSt = calculeazaInaltime((*radacina)->st);
		int inaltimeDr = calculeazaInaltime((*radacina)->dr);
		return 1 + ((inaltimeSt > inaltimeDr) ? inaltimeSt : inaltimeDr);
	}
	return 0;
}

int calcGradEchilibru(Nod** radacina) {
	if ((*radacina) != NULL)
		return calculeazaInaltime((*radacina)->st) - calculeazaInaltime((*radacina)->dr);
	return 0;
}
void rotireDreapta(Nod** radacina) {
	Nod* aux = (*radacina)->st;
	(*radacina)->st = aux->dr;
	aux->dr = (*radacina);
	(*radacina) = aux;
}
void rotireStanga(Nod** radacina) {
	Nod* aux = (*radacina)->dr;
	(*radacina)->dr = aux->st;
	aux->st = *radacina;
	*radacina = aux;
}
void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	if ((*radacina) != NULL) {
		if (masinaNoua.id < (*radacina)->info.id)
			adaugaMasinaInArbore(&((*radacina)->st), masinaNoua);
		else if (masinaNoua.id > (*radacina)->info.id)
			adaugaMasinaInArbore(&((*radacina)->dr), masinaNoua);
		int grad = calcGradEchilibru(radacina);
		if (grad == 2) {
			if(calcGradEchilibru((*radacina)->st) == 1)
				rotireDreapta(radacina);
			else {
				rotireStanga(&(*radacina)->st);
				rotireDreapta(radacina);
			}
		}
		if (grad == -2) {
			if (calcGradEchilibru((*radacina)->dr) == -1)
				rotireStanga(radacina);
			else {
				rotireDreapta(&(*radacina)->dr);
				rotireStanga(radacina);
			}
		}
	}
	else
	{
		(*radacina) = (Nod*)malloc(sizeof(Nod));
		(*radacina)->info = masinaNoua;
		(*radacina)->st = NULL;
		(*radacina)->dr = NULL;
	}
}