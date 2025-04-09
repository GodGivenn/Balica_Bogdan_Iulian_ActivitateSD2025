#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};

typedef struct StructMasina Masina;
typedef struct Nod Nod;

struct Nod{
    Masina info;
    Nod* urm;
};

void adaugareMasinaLaFinalInLista(Nod** cap, Masina masinaNoua){
    Nod* nou = NULL;
    nou = (Nod*)malloc(sizeof(Nod));

    nou->info = masinaNoua;
    nou->urm = NULL;

    if((*cap)==NULL){
        *cap = nou;
    }
    else{
        Nod* temp = *cap;
        while(temp->urm){
            temp = temp->urm;
        }
        temp->urm = nou;
    }
}

Masina citireMasinaFisier(FILE* file){
    char buffer[100];
    char sep[3]=",\n";
    fgets(buffer,100,file);
    char* aux;
    Masina m1;
    aux=strtok(buffer, sep);
    m1.id = atoi(aux);
    m1.nrUsi = atoi(strtok(NULL,sep));
    m1.pret = atof(strtok(NULL,sep));
    aux = strtok(NULL, sep);
    m1.model = malloc(strlen(aux) + 1);
    strcpy(m1.model, aux);

    aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy(m1.numeSofer,  aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void* citireListaDeMasiniFisier(const char* numeFisier){
    FILE* file = fopen(numeFisier, "r");

    if(!file){
        printf("error");
        return NULL;
    }
    Nod* lista=NULL;
    while(!feof(file)){
        adaugareMasinaLaFinalInLista(&lista, citireMasinaFisier(file));
    }
    fclose(file);
    return lista;
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
int main()
{
    Nod* cap = NULL;
    cap=citireListaDeMasiniFisier("masini.txt");
    afisareListaMasini(cap);
}