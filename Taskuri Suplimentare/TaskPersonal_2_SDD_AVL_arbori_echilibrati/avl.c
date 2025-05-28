#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraCarte {
	int id;
	int nrPagini;
	float pret;
	char* titlu;
	char* autor;
	unsigned char gen;
};
typedef struct StructuraCarte Carte;
typedef struct Nod Nod;
//creare structura pentru un nod dintr-un arbore binar de cautare
struct Nod {
	Carte info;
	Nod* st;
	Nod* dr;
};

Carte citireCarteDinFisier(FILE* file) {
	char buffer[200];
	char sep[3] = ",\n";
	fgets(buffer, 200, file);
	char* aux;
	Carte c;
	aux = strtok(buffer, sep);
	c.id = atoi(aux);
	c.nrPagini = atoi(strtok(NULL, sep));
	c.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	c.titlu = malloc(strlen(aux) + 1);
	strcpy(c.titlu, aux);

	aux = strtok(NULL, sep);
	c.autor = malloc(strlen(aux) + 1);
	strcpy(c.autor, aux);

	c.gen = *strtok(NULL, sep);
	return c;
}

void afisareCarte(Carte carte) {
	printf("Id: %d\n", carte.id);
	printf("Nr pagini: %d\n", carte.nrPagini);
	printf("Pret: %.2f\n", carte.pret);
	printf("Titlu: %s\n", carte.titlu);
	printf("Autor: %s\n", carte.autor);
	printf("Gen: %c\n\n", carte.gen);
}

void adaugaCarteInArbore(Nod** radacina, Carte carteNoua) {
	if ((*radacina) != NULL) {
		if (carteNoua.id < (*radacina)->info.id)
			adaugaCarteInArbore(&((*radacina)->st), carteNoua);
		else if (carteNoua.id > (*radacina)->info.id)
			adaugaCarteInArbore(&((*radacina)->dr), carteNoua);
	}
	else
	{
		(*radacina) = (Nod*)malloc(sizeof(Nod));
		(*radacina)->info = carteNoua;
		(*radacina)->st = NULL;
		(*radacina)->dr = NULL;
	}
}

Nod* citireArboreDeCartiDinFisier(char* const numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(file))
	{
		adaugaCarteInArbore(&radacina, citireCarteDinFisier(file));
	}
	fclose(file);
	return radacina;
}

void afisareArborePreOrdine(Nod* radacina) {
	if (radacina != NULL)
	{
		afisareCarte(radacina->info);
		afisareArborePreOrdine(radacina->st);
		afisareArborePreOrdine(radacina->dr);
	}
}

int calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina != NULL) {
		int inaltimeSt = calculeazaInaltimeArbore(radacina->st);
		int inaltimeDr = calculeazaInaltimeArbore(radacina->dr);
		return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
	}
	return 0;
}

int calcGradEchilibru(Nod* radacina) {
	if (radacina != NULL) {
		return(calculeazaInaltimeArbore(radacina->st) - calculeazaInaltimeArbore(radacina->dr));
	}
	else {
		return 0;
	}
}

void rotireStanga(Nod** radacina) {
	Nod* aux = (*radacina)->dr;
	(*radacina)->dr = aux->st;
	aux->st = *radacina;
	*radacina = aux;
}

void rotireDreapta(Nod** radacina) {
	Nod* aux  = (*radacina)->st;
	(*radacina)->st = aux->dr;
	aux->dr = (*radacina);
	*radacina = aux;
}

void adaugaCarteInArboreEEchilibrat(Nod** radacina, Carte carteNoua) {
	if ((*radacina) != NULL) {
		if (carteNoua.id < (*radacina)->info.id)
			adaugaCarteInArboreEEchilibrat(&((*radacina)->st), carteNoua);
		else
			adaugaCarteInArboreEEchilibrat(&((*radacina)->dr), carteNoua);
		int grad = calcGradEchilibru(*radacina);
		if (grad == 2)
		{
			if (calcGradEchilibru((*radacina)->st) == 1) {
				rotireDreapta(radacina);
			}
			else {
				rotireStanga(&((*radacina)->st));
				rotireDreapta(radacina);
			}
		}
		else if (grad == -2)
		{
			if (calcGradEchilibru((*radacina)->dr) == -1) {
				rotireStanga(radacina);
			}
			else
			{
				rotireDreapta(&((*radacina)->dr));
				rotireStanga(radacina);
			}
		}
	}
	else
	{
		(*radacina) = (Nod*)malloc(sizeof(Nod));
		(*radacina)->info = carteNoua;
		(*radacina)->st = NULL;
		(*radacina)->dr = NULL;
	}
}

Nod* cautaCarteDupaId(Nod* radacina, int id) {
	if (radacina == NULL) return NULL;
	if (id == radacina->info.id) return radacina;
	if (id < radacina->info.id) return cautaCarteDupaId(radacina->st, id);
	return cautaCarteDupaId(radacina->dr, id);
}

int totalPagini(Nod* radacina) {
	if (radacina == NULL) return 0;
	return radacina->info.nrPagini + totalPagini(radacina->st) + totalPagini(radacina->dr);
}

int main() {
	Nod* radacina = NULL;
	radacina = citireArboreDeCartiDinFisier("carti.txt");
	afisareArborePreOrdine(radacina);
	printf("Inaltime arbore: %d\n", calculeazaInaltimeArbore(radacina));

	int cautatId = 3;
	Nod* gasit = cautaCarteDupaId(radacina, cautatId);
	if (gasit != NULL) {
		printf("Cartea cu id %d gasita:\n", cautatId);
		afisareCarte(gasit->info);
	} else {
		printf("Cartea cu id %d nu a fost gasita.\n", cautatId);
	}

	printf("Numar total de pagini in arbore: %d\n", totalPagini(radacina));
	return 0;
}