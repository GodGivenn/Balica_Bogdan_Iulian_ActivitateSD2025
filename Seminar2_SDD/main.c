#include<stdio.h>
// #include<malloc.h> nu am malloc.h pe macos, in schimb este inclus in stdlib.h
#include <stdlib.h>
#include <string.h>

struct Masina {
    int id; // 4
    int nrLocuri; // 4
    char* marca; // 8
    float capacitateC; // 4
    char normaPoluare; // 1
};

struct Masina initializare(int id, int nrLocuri, const char* marca, float capacitateC, char normaPoluare)
{
    struct Masina m;
    m.id = id;
    m.nrLocuri = nrLocuri;

    if(marca == NULL) {
        m.marca = NULL;
    }
    else {
        m.marca = (char*)malloc(strlen(marca) + 1);
        //strcpy_s(m.marca, strlen(marca)+1 ,marca);
        strcpy(m.marca, marca);
    }

    m.capacitateC = capacitateC;
    m.normaPoluare = normaPoluare;
    return m;
}

void afisare(struct Masina m) {
    printf("ID masina: %d\nNr Locuri: %d\nCapacitate: %f\nMarca: %s\nNorma Poluare: Euro %c\n", m.id, m.nrLocuri, m.capacitateC, m.marca, m.normaPoluare);
    printf("\n");
}

void afisareVector(struct Masina* vector, int nrElemente) {
    for (int i = 0; i < nrElemente; i++)
    {
        afisare(vector[i]);
    }

}

struct Masina* copiazaPrimeleMasini(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate

    if (nrElementeCopiate > nrElemente) {
        nrElementeCopiate = nrElemente;
    }

	struct Masina *vectorNou=NULL;
    vectorNou = (struct Masina*)malloc(nrElementeCopiate * sizeof(struct Masina));

    for (int i = 0; i < nrElementeCopiate; i++)
    {
        vectorNou[i] = initializare(vector[i].id, vector[i].nrLocuri, vector[i].marca, vector[i].capacitateC, vector[i].normaPoluare);
    }

	return vectorNou;
}

void dezalocare(struct Masina** vector, int* nrElemente) {
        for (int i = 0; i < *nrElemente; i++)
            free((*vector)[i].marca);
        free(*vector);
        *vector = NULL;
        *nrElemente = 0;
}

void copiazaMasiniCuCCMaiMare(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie

    *dimensiune = 0;
    for (char i = 0; i < nrElemente; i++)
    {
        if(vector[i].capacitateC > prag)
            (*dimensiune)++;
    }

    if((*dimensiune) > 0) *vectorNou = (struct Masina*)malloc((*dimensiune) * sizeof(struct Masina));
    else *vectorNou = NULL;

    int j = 0;
    for(int i=0; i < nrElemente; i++) {
        if(vector[i].capacitateC > prag) {
            (*vectorNou)[j] = vector[i];
            (*vectorNou)[j].marca = malloc(sizeof(char)* (strlen(vector[i].marca) + 1));
            strcpy((*vectorNou)[j].marca, vector[i].marca);
            j++;
        }
    }
}

struct Masina getPrimaMasinaDupaMarca(struct Masina* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
    for (int i = 0; i < nrElemente; i++)
    {
        if (strcmp(vector[i].marca, conditie) == 0) {
            return vector[i];
        }
        return initializare(1,0,NULL,0,'0');
    }
}

int main() {
    int nrElemente = 3;
    struct Masina *vector = (struct Masina *) malloc(nrElemente * sizeof(struct Masina));

    vector[0] = initializare(1, 3, "Dacia", 40, '5');
    vector[1] = initializare(2, 4, "Honda", 30, '6');
    vector[2] = initializare(3, 5, "Dacia", 50, '4');
    afisareVector(vector, nrElemente);

    int nrElemCopiate = 2;
    struct Masina *vectorMasiniCopiate = copiazaPrimeleMasini(vector, 3, 2);
    afisareVector(vectorMasiniCopiate, nrElemCopiate);

    dezalocare(&vectorMasiniCopiate, &nrElemCopiate);

    printf("\nafisare masini cu capacitate mai mare\n");
    copiazaMasiniCuCCMaiMare(vector, nrElemente, 35, &vectorMasiniCopiate, &nrElemCopiate);

    afisareVector(vectorMasiniCopiate, nrElemCopiate);

    dezalocare(&vectorMasiniCopiate, &nrElemCopiate);

    struct Masina m1 = getPrimaMasinaDupaMarca(vector, nrElemente, "Opel");

    printf("\nafisare prima masina\n");

    afisare(m1);

    dezalocare(&vector, &nrElemente);
    return 0;
}