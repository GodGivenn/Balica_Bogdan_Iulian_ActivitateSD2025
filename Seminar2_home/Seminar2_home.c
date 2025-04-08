#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc/malloc.h>

struct Masina {
	int id; //4
	int nrLocuri; //4
	char* marca; //8
	float capacitateC; //4
	char normaPoluare; //1
};

struct Masina initializare(int id, int nrLocuri, const char* marca, float capacitateC, char normaPoluare) // nu trebuie const la norma pentru ca e prin valoare transm
{
	struct Masina m;
	m.id = id;
	m.nrLocuri = nrLocuri;

	m.marca = (char*)malloc(strlen(marca) + 1);//daca nu e char, cu sizeof
	//strcpy_s(m.marca, strlen(marca)+1 ,marca);
	strcpy(m.marca, marca);

	m.capacitateC = capacitateC;
	m.normaPoluare = normaPoluare;
	return m;
}

void afisare(struct Masina m) {
	printf("id: %d\nnrLocuri: %d\ncapacitate: %f\nmarca: %s\nnorma: %c\n\n" ,m.id, m.nrLocuri, m.capacitateC, m.marca, m.normaPoluare);
}

void afisareVector(struct Masina* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}

// struct Sablon* copiazaPrimeleNElemente(struct Sablon* vector, int nrElemente, int nrElementeCopiate) {
// 	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
// 	struct Sablon *vectorNou=NULL;
//
// 	return vectorNou;
// }

void dezalocare(struct Masina** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++)
		free((*vector)[i].marca);
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

// void copiazaAnumiteElemente(struct Sablon* vector, char nrElemente, float prag, struct Sablon** vectorNou, int* dimensiune) {
// 	//parametrul prag poate fi modificat in functie de
// 	// tipul atributului ales pentru a indeplini o conditie
// 	//este creat un nou vector cu elementele care indeplinesc acea conditie
// }
//
// struct Sablon getPrimulElementConditionat(struct Sablon* vector, int nrElemente, const char* conditie) {
// 	//trebuie cautat elementul care indeplineste o conditie
// 	//dupa atributul de tip char*. Acesta este returnat.
// 	struct Sablon s;
// 	s.id = 1;
//
// 	return s;
// }



int main() {
	struct Masina masini[3];
	masini[0] = initializare(1, 5, "Dacia", 1.5, '4');
	masini[1] = initializare(2, 4, "BMW", 2.8, '5');
	masini[2] = initializare(3, 2, "Audi", 2.2, '4');
	afisareVector(masini, 3);
	int nrElem = 3;
	dezalocare(masini, &nrElem);
	afisareVector(masini, 3);
	return 0;
}