#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void modifica_nrLocuri(struct Masina *m, int nrNou) {
    if(nrNou>0)
        m->nrLocuri = nrNou;
}

void dezalocare(struct Masina *m) {
    if (m && m->marca) {
        free(m->marca);
        (*m).marca = NULL; //echivalent cu m->marca
    }}

int main() {
    struct Masina masina; //in C trebuie precizat ca e structura
    masina = initializare(1,5,"Dacia", 1.5, '4');
    afisare(masina);
    modifica_nrLocuri(&masina, 2);
    afisare(masina);
    dezalocare(&masina);
    afisare(masina);
    printf("%d",sizeof(struct Masina*));
    printf("%d",sizeof(masina));
    return 0;
}