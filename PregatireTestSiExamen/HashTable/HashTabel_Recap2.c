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
typedef struct Nod Nod;

struct Nod{
    Masina info;
    Nod* urmator;
};

struct HashTable{
    int dim;
    Nod** v;
};


int main(){
    int nrElemente = 3;
    Masina* vector = (Masina*)malloc(sizeof(Masina) * nrElemente);
    
}
