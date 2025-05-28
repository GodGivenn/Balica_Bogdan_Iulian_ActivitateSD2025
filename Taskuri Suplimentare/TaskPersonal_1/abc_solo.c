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

void dezalocaMemorie(Nod* radacina) {
	if (radacina != NULL) {
		dezalocaMemorie(radacina->st);
		dezalocaMemorie(radacina->dr);
		free(radacina->info.titlu);
		free(radacina->info.autor);
		free(radacina);
	}
}

void afisareArboreInOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisareArboreInOrdine(radacina->st);
		afisareCarte(radacina->info);
		afisareArboreInOrdine(radacina->dr);
	}
}

void afisareArborePostOrdine(Nod* radacina) {
	if (radacina != NULL) {
		afisareArborePostOrdine(radacina->st);
		afisareArborePostOrdine(radacina->dr);
		afisareCarte(radacina->info);
	}
}

Carte getCarteaCuPretMinim(Nod* radacina) {
	Carte c;
	c.id = -1;
	if (radacina == NULL) return c;

	Carte minCurent = radacina->info;

	if (radacina->st != NULL) {
		Carte minSt = getCarteaCuPretMinim(radacina->st);
		if (minSt.id != -1 && minSt.pret < minCurent.pret) {
			minCurent = minSt;
		}
	}

	if (radacina->dr != NULL) {
		Carte minDr = getCarteaCuPretMinim(radacina->dr);
		if (minDr.id != -1 && minDr.pret < minCurent.pret) {
			minCurent = minDr;
		}
	}

	return minCurent;
}

Carte getCarteaCuPretMaxim(Nod* radacina) {
	Carte c;
	c.id = -1;
	if (radacina == NULL) return c;

	Carte maxCurent = radacina->info;

	if (radacina->st != NULL) {
		Carte maxSt = getCarteaCuPretMaxim(radacina->st);
		if (maxSt.id != -1 && maxSt.pret > maxCurent.pret) {
			maxCurent = maxSt;
		}
	}

	if (radacina->dr != NULL) {
		Carte maxDr = getCarteaCuPretMaxim(radacina->dr);
		if (maxDr.id != -1 && maxDr.pret > maxCurent.pret) {
			maxCurent = maxDr;
		}
	}

	return maxCurent;
}

float calculeazaPretMediu(Nod* radacina) {
	if (radacina == NULL) return 0;

	int numarCarti = determinaNumarNoduri(radacina);
	float sumaPreturi = calculeazaSumaPreturi(radacina);

	return sumaPreturi / numarCarti;
}

float calculeazaSumaPreturi(Nod* radacina) {
	if (radacina == NULL) return 0;

	return radacina->info.pret + calculeazaSumaPreturi(radacina->st) + calculeazaSumaPreturi(radacina->dr);
}

void cautaCartiDupaAutor(Nod* radacina, char* autor) {
	if (radacina != NULL) {
		if (strcmp(radacina->info.autor, autor) == 0) {
			printf("Gasita carte de %s:\n", autor);
			afisareCarte(radacina->info);
		}
		cautaCartiDupaAutor(radacina->st, autor);
		cautaCartiDupaAutor(radacina->dr, autor);
	}
}

void cautaCartiDupaGen(Nod* radacina, char gen) {
	if (radacina != NULL) {
		if (radacina->info.gen == gen) {
			printf("Gasita carte din genul '%c':\n", gen);
			afisareCarte(radacina->info);
		}
		cautaCartiDupaGen(radacina->st, gen);
		cautaCartiDupaGen(radacina->dr, gen);
	}
}

void cautaCartiDupaPret(Nod* radacina, float pretMin, float pretMax) {
	if (radacina != NULL) {
		if (radacina->info.pret >= pretMin && radacina->info.pret <= pretMax) {
			printf("Carte cu pretul in intervalul [%.2f, %.2f]:\n", pretMin, pretMax);
			afisareCarte(radacina->info);
		}
		cautaCartiDupaPret(radacina->st, pretMin, pretMax);
		cautaCartiDupaPret(radacina->dr, pretMin, pretMax);
	}
}

int determinaInaltimeaArborelui(Nod* radacina) {
	if (radacina == NULL) return -1;

	int inaltimeSt = determinaInaltimeaArborelui(radacina->st);
	int inaltimeDr = determinaInaltimeaArborelui(radacina->dr);

	return 1 + (inaltimeSt > inaltimeDr ? inaltimeSt : inaltimeDr);
}

int numaraCartiCuMultePagini(Nod* radacina, int pragPagini) {
	if (radacina == NULL) return 0;

	int count = (radacina->info.nrPagini > pragPagini) ? 1 : 0;
	return count + numaraCartiCuMultePagini(radacina->st, pragPagini) + numaraCartiCuMultePagini(radacina->dr, pragPagini);
}

int main() {
	Nod* radacina = citireArboreDeCartiDinFisier("carti.txt");

	printf("\n--- Preordine ---\n");
	afisareArborePreOrdine(radacina);

	printf("\n--- Inordine ---\n");
	afisareArboreInOrdine(radacina);

	int id;
	printf("\nid carte cautata: ");
	scanf("%d", &id);
	Carte c = getCarteByID(radacina, id);
	if (c.id != -1)
		afisareCarte(c);
	else
		printf("Nu exista carte cu id ul %d.\n", id);

	/*char autor[100];
	printf("\nAutor cautat: ");
	scanf("%s", autor);
	printf("\nCarti scrise de %s:\n", autor);
	cautaCartiDupaAutor(radacina, autor);*/

	char gen;
	printf("\nGen cautat (litera): ");
	scanf(" %c", &gen);
	printf("\nCarti din genul '%c':\n", gen);
	cautaCartiDupaGen(radacina, gen);

	float pretMin, pretMax;
	printf("\nInterval de pret (min max): ");
	scanf("%f %f", &pretMin, &pretMax);
	printf("\nCarti intre %.2f si %.2f lei:\n", pretMin, pretMax);
	cautaCartiDupaPret(radacina, pretMin, pretMax);

	Carte minCarte = getCarteaCuPretMinim(radacina);
	if (minCarte.id != -1) {
		printf("\nCarte cu pret minim:\n");
		afisareCarte(minCarte);
	}

	Carte maxCarte = getCarteaCuPretMaxim(radacina);
	if (maxCarte.id != -1) {
		printf("\nCarte cu pret maxim:\n");
		afisareCarte(maxCarte);
	}

	printf("\nPret mediu: %.2f lei\n", calculeazaPretMediu(radacina));
	printf("Numar total carti: %d\n", determinaNumarNoduri(radacina));
	printf("Inaltime arbore: %d\n", determinaInaltimeaArborelui(radacina));

	int pragPagini;
	printf("\nPrag pagini (min): ");
	scanf("%d", &pragPagini);
	printf("Carti cu peste %d pagini: %d\n", pragPagini, numaraCartiCuMultePagini(radacina, pragPagini));

	dezalocaMemorie(radacina);

	return 0;
}
