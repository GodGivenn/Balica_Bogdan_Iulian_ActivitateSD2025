#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//trebuie sa folositi fisierul carti.txt
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
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Carte c1;
	aux = strtok(buffer, sep);
	c1.id = atoi(aux);
	c1.nrPagini = atoi(strtok(NULL, sep));
	c1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	c1.titlu = malloc(strlen(aux) + 1);
	strcpy_s(c1.titlu, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	c1.autor = malloc(strlen(aux) + 1);
	strcpy_s(c1.autor, strlen(aux) + 1, aux);
	c1.gen = *strtok(NULL, sep);
	return c1;
}
void afisareCarte(Carte carte) {
	printf("Id: %d\n", carte.id);
	printf("Nr. pagini: %d\n", carte.nrPagini);
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
Carte getCarteByID(Nod* radacina, int id) {
	Carte c;
	c.id = -1;
	if (radacina != NULL) {
		if (id < radacina->info.id) {
			return getCarteByID(radacina->st, id);
		}
		else if (id > radacina->info.id)
			return getCarteByID(radacina->dr, id);
		else
			return radacina->info;
	}
	return c;
}
Carte getCarteByID1(Nod* radacina, int id) {
	Carte c;
	c.id = -1;
	if (id > radacina->info.id)
	{
		return getCarteByID1(radacina->dr, id);
	}
	else if (id < radacina->info.id) {
		return getCarteByID1(radacina->st, id);
	}
	else {
		c = radacina->info;
		c.autor = (char*)malloc(strlen(radacina->info.autor) + 1);
		strcpy(c.autor, radacina->info.autor);
		c.titlu = (char*)malloc(strlen(radacina->info.titlu) + 1);
		strcpy(c.titlu, radacina->info.titlu);
		return c;
	}
	return c;
}
int determinaNumarNoduri(Nod* radacina) {
	if (radacina != NULL) {
		return  1 + determinaNumarNoduri(radacina->st) + determinaNumarNoduri(radacina->dr);
	}
	else {
		return 0;
	}

}
int main() {
	Nod* radacina = NULL;
	radacina = citireArboreDeCartiDinFisier("carti.txt");
	afisareArborePreOrdine(radacina);
	return 0;
}