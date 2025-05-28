#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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

struct Heap {
	int lungime;//lungime vector
	Masina* vector;
	int nrMasini;//nr elemente din vector
};
typedef struct Heap Heap;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);//5,3,11000,Logan,Ionescu,C
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);//5,3,11000,Logan,Ionescu,C
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL,sep));
	m1.pret = atoi(strtok(NULL,sep));

	aux = strtok(NULL, sep);//Logan
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

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrMasini = 0;
	heap.vector = (Masina*)malloc(sizeof(Masina) * lungime);
	return heap;
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
	if (pozMax != pozitieNod)//am gasit un maxim din fiul st/dr
	{
		/*Masina aux = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = heap.vector[pozMax];
		heap.vector[pozMax] = aux;*/
		Masina aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;


		//!!!!daca nodul e un parinte apelam iar!
		//!!  daca fiulSt <= nrmasini - 1 ca incepe de la 0
		//if(2*pozMax + 1 <= heap.nrMasini - 1)
		if(pozMax <= (heap.nrMasini - 2) / 2)
			filtreazaHeap(heap, pozMax);
	}
}

Heap citireHeapMasiniDinFisier(const char* numeFisier) {
	FILE* file;
	file = fopen(numeFisier, "r");
	Heap heap = initializareHeap(10);
	while (!feof(file)) {
		Masina aux = citireMasinaDinFisier(file);
		heap.vector[heap.nrMasini++] = aux;
	}
	fclose(file);
	//!!! de la ultimul parinte la primul
	for (int i = (heap.nrMasini - 2) / 2; i >= 0; i--)
		filtreazaHeap(heap, i);
	return heap;
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrMasini; i++) {
		afisareMasina(heap.vector[i]);
	}
}

Masina extrageMasina(Heap* heap) {
	if (heap->nrMasini>0) {
		Masina aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrMasini - 1];
		heap->vector[heap->nrMasini - 1] = aux;
		heap->nrMasini--;
		//!!!!!
		for (int i = (heap->nrMasini - 2) / 2; i >= 0; i--)
			filtreazaHeap(*heap, i);

		return aux;//shallow copty
		//return heap->vector[heap->nrMasini];
	}
}

void afiseazaHeapAscuns(Heap heap) {
	for (int i = heap.nrMasini; i < heap.lungime; i++)
		afisareMasina(heap.vector[i]);
}

void dezalocareHeap(Heap* heap) {
	for(int i = 0; i < heap->lungime; i++) {
		free(heap->vector[i].model);
		free(heap->vector[i].numeSofer);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->lungime = 0;
	heap->nrMasini = 0;
}

int main() {
	Heap heap = initializareHeap(10);
	heap = citireHeapMasiniDinFisier("masini.txt");
	afisareHeap(heap);

	printf("==============Masini extrase==============\n");
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));
	afisareMasina(extrageMasina(&heap));
	printf("==============Heap ascuns==============\n");
	afiseazaHeapAscuns(heap);
	dezalocareHeap(&heap);
}