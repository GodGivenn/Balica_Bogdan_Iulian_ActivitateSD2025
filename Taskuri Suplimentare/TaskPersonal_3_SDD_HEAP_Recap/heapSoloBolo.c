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

typedef struct Heap Heap;
struct Heap {
	int lungime;
	int nrMasini;
	Masina* vector;
};

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);//5,3,11000,Logan,Ionescu,C
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);//5,3,11000,Logan,Ionescu,C
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atoi(strtok(NULL, sep));

	aux = strtok(NULL, sep);//Logan
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);


	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrMasini = 0;
	heap.vector = malloc(sizeof(Masina));
}

void filtreazaHeap(Heap heap, int pozitieNod) {
	int pozFiuSt = 2 * pozitieNod + 1;
	int pozFiuDr = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;
	if (pozFiuSt < heap.nrMasini && heap.vector[pozMax].id < heap.vector[pozFiuSt].id)
	{
		pozMax = pozFiuSt;
	}
	if (pozFiuDr < heap.nrMasini && heap.vector[pozMax].id < heap.vector[pozFiuDr].id)
	{
		pozMax = pozFiuDr;
	}
	if (pozMax != pozitieNod) {
		Masina aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;

		//verific daca e parinte
		if (pozMax <= (heap.nrMasini - 2) / 2)
			filtreazaHeap(heap, pozMax);
	}
}

Heap citireHeapMasiniDinFisier(char* const numeFisier) {
	FILE* file;
	file = fopen(numeFisier, "r");
	Heap heap = initializareHeap(10);
	while (!feof(file)) {
		Masina aux = citireMasinaDinFisier(file);
		heap.vector[heap.nrMasini++] = aux;
	}
	fclose(file);
	for (int parinte = (heap.nrMasini - 2) / 2; parinte >= 0; parinte--) {
		filtreazaHeap(heap, parinte);
	}

}

void main() {
	Heap heap = initializareHeap(10);
}