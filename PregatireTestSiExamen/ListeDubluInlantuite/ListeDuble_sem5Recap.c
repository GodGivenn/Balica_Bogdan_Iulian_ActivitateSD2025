#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod{
    Masina info;
    Nod* urmator;
    Nod* precedent;
};

typedef struct Nod Nod;

struct Lista{
    Nod* prim;
    Nod* ultim;
};
typedef struct Lista Lista;

void adaugareLaInceputInLista(Lista* list, Masina masinaNoua){
    Nod* p=(Nod*)malloc(sizeof(Nod));
    p->info=masinaNoua;
    p->urmator = list->prim;
    p->precedent = NULL;

    if(list->prim){
        list->prim->precedent = p;
    }
}

Lista citireListaMasiniFisier(const char* numeFisier){
    FILE* file = fopen(numeFisier,"r");
    Lista list;
    list.prim = NULL;
    list.ultim = NULL;

    while(!feof(file)){

    }
    fclose(file);
    return list;
}