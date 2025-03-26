// #define _CRT_SECURE_NO_WARNINGS
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
//creare structura pentru un nod dintr-o lista simplu inlantuita
struct Nod {
	Masina info;
	Nod* urm;
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
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy(m1.model,  aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer,  aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	//afiseaza toate elemente de tip masina din lista simplu inlantuita
	//prin apelarea functiei afisareMasina()

	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap) {
	while(cap) {
		afisareMasina(cap->info);
		cap = cap->urm;
	}

}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua; //lasam shallow copy pentru ca; daca aceasta masina parametru in functia unde apelam adaugam masina in lista o sa o dezalocam sau nu, daca o dezolcam trebuie deep copy
	nou->urm = NULL; //daca nu dezaolcam, ramane shallow, si nu o sa dezaolcam deci ramane asa

	if((*cap) == NULL) {
		*cap = nou;
	} else {
		Nod* temp = *cap;
		while(temp -> urm) {
			temp = temp -> urm;
			//daca facem inserarea aici, legatura catre nod urmator, o sa pierdem restul elementelor
		}
		temp -> urm = nou;
	}
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->urm = *cap;
	*cap = nou;
}

void* citireListaMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* file = fopen(numeFisier, "r");

	if(!file) {
		printf("Eroare, nu s a putut deschide file");
		return NULL;
	}
	Nod* lista = NULL;//daca nu initializam, acea variabila o sa aiba o valoare implicita diferita de null, si in functia de inserare verificam daca e null si nu o sa mai mearga
	while(!feof(file)) {
		adaugaMasinaInLista(&lista, citireMasinaDinFisier(file));
		//daca faceam deepcopy anterior trebuia sa dezaolcam aici masina
	}
	fclose(file);
	return lista;
}

void dezalocareListaMasini(/*lista de masini*/) {
	//sunt dezalocate toate masinile si lista de elemente
}

float calculeazaPretMediu(/*lista de masini*/) {
	//calculeaza pretul mediu al masinilor din lista.
	return 0;
}

void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {
	Nod* cap = NULL;
	cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);


	return 0;
}