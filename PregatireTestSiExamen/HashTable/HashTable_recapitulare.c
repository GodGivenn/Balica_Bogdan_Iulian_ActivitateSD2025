#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
struct Nod {
    Masina info;
    Nod* urm;
};

struct HashTable{
    int dim;
    Nod** vectorNod;
};

typedef struct HashTable HashTable;

Masina citireMasinaDinFisier(FILE* file){
    Masina masina;
    char buffer[100];
    char sep[3]=",\n";
    char* aux;
    fgets(buffer,100,file);
//buffer = 1,3,5000,Astra,Ionescu,A
    aux = strtok(buffer,sep);
    masina.id = atoi(aux);
    masina.nrUsi = atoi(strtok(NULL,sep));
    masina.pret = atof(strtok(NULL,sep));
    
    aux = strtok(NULL,sep);
    masina.model = malloc(sizeof(strlen(aux) + 1));
    strcpy(masina.model, aux);
    
    aux = strtok(NULL,sep);
    masina.numeSofer = malloc(sizeof(strlen(aux) + 1));
    strcpy(masina.numeSofer, aux);

    masina.serie = *strtok(NULL,sep);
    return masina;
}

void adaugaMasinaInLista(Nod* lista, Masina masinaNoua) { //Nod** lista -> pointerul care retine adresa pointerului care retine adresa de inceput
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
    //daca lista nu e nula nu apelam functia ca sa nu mai transmitem nod**
    if(lista==NULL)
        return;
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = masinaNoua;//shallow copy
    nou->urm = NULL;
    
    while(lista->urm != NULL)
    {
        lista = lista->urm;
    }
    lista->urm = nou;
}

HashTable intializeazaHashTable(int dimensiune){
    HashTable ht;
    ht.dim = dimensiune;
    ht.vectorNod = (Nod**)malloc(sizeof(Nod*) * dimensiune);
    for(int i=0; i< dimensiune; i++){
        ht.vectorNod[i] = NULL;
    }
    return ht;
}

int calculeazaHash(const char* nume, int dimensiune){
    if(dimensiune == 0)
        return dimensiune;
    
    int suma = 0;
    for(int i = 0; i< strlen(nume); i++)
        suma+=nume[i];
    
    return suma%dimensiune;
}

void inserareMasinaInTabela(HashTable hash, Masina masina){
    int poz = calculeazaHash(masina.numeSofer, hash.dim);

    if(hash.vectorNod[poz] == NULL){
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->info = masina;
        nou->urm = NULL;
        hash.vectorNod[poz] = nou;
    }
    else{
        adaugaMasinaInLista(hash.vectorNod[poz], masina);
    }
}

HashTable citireMasinaDinFisier(const char* numeFisier, int dimensiune){
    FILE* file = fopen(numeFisier, "r");
    HashTable ht = intializeazaHashTable(dimensiune);

    while(!feof(file)){
        inserareMasinaInTabela(ht,citireMasinaDinFisier(file));
    }
    fclose(file);
    return ht;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* lista) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
    while(lista != NULL){
        afisareMasina(lista->info);
        lista = lista->urm;
    }
}


int main(){
    HashTable ht;
}