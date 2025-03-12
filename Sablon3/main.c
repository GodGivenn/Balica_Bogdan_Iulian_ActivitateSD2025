#define _CRT_SECURE_NO_WARNINGS
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
typedef struct StructuraMasina Masina;//alias sa scriu doar Masina

void afisareMasina(Masina masina) {
    //afiseaza toate atributele unei masini
    printf("ID: %d\n", masina.id);
    printf("Numar Usi: %d\n", masina.nrUsi);
    printf("Pret: %.2f\n", masina.pret);
    printf("Model: %s\n", masina.model);
    printf("Nume sofer: %s\n", masina.numeSofer);
    printf("Serie: %c\n\n", masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
    //afiseaza toate elemente de tip masina din vector
    //prin apelarea functiei afisareMasina()
    for (int i=0;i<nrMasini; i++) {
        afisareMasina(masini[i]);
    }
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
    //**; * ca sa putem modifica
    //adauga in vectorul primit o noua masina pe care o primim ca parametru
    //ATENTIE - se modifica numarul de masini din vector;

    Masina* copie = (Masina*)malloc(sizeof(Masina) * ( (*nrMasini) + 1));
    //+1 pentru masina noua si dereferentiere ca e prin adresa si sa iau valoarea
    for(int i=0; i < *nrMasini; i++) {
        copie[i] = (*masini)[i];
    }
    //deepcopy -> fac alocari noi, dupa care trb sa sterg vechiul vector
    //shallow -> pointerii nu i modific, sterg doar vectorul
    //permite shallow pentru ca eu o sa am doi pointeri care pointeaza la aceeasi valoare si scap de unul din ei

    copie[(*nrMasini)] = masinaNoua;
    (*nrMasini)++;
    //merge si shallow si deep copy, conteaza ce fac in main
    //daca dezaloc -> deep
    //daca nu dezaloc -> shallow
    free(*masini);
    (*masini) = copie;
}

Masina citireMasinaFisier(FILE* file) {
    //functia citeste o masina dintr-un strceam deja deschis
    //masina citita este returnata;
    char buffer[100];
    char sep[3] =",\n";//sunt separate si prin endline
    char *aux;
    fgets(buffer, 100, file);
    Masina m1;
    // aux = strtok(buffer, sep);
    m1.id = atoi(strtok(buffer, sep));
    m1.nrUsi = atoi(strtok(NULL, sep)); // ca sa continue
    m1.pret = atof(strtok(NULL, sep));

    aux = strtok(NULL, sep);
    m1.model = malloc(strlen(aux) + 1);
    // strcpy(m1.model, strlen(aux) + 1, aux);
    strcpy(m1.model, aux);

    m1.serie = *strtok(NULL, sep);
    //sau indexare cu 0

    return m1;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
    //functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
    //prin apelul repetat al functiei citireMasinaFisier()
    //numarul de masini este determinat prin numarul de citiri din fisier
    //ATENTIE - la final inchidem fisierul/stream-ul

    FILE* file = fopen(numeFisier, "r");
    Masina* masini = NULL;
    do {
        adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
    }while(!feof(file));//cat timp nu am ajuns la sf fisierului

    fclose(file);
    return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
    //este dezalocat intreg vectorul de masini
    for(int i=0; i<*nrMasini; i++) {
        free((*vector)[i].model);
        free((*vector)[i].numeSofer);
    }
    free(*vector);
    *vector = NULL;
}

float pretMediuDupaNrUsi(Masina* vector, int nrMasini, int nrUsi) {
    float suma = 0;
    int k = 0;
    for (int i = 0; i < nrMasini; ++i) {
        if(vector[i].nrUsi == nrUsi) {
            suma += vector[i].pret;
            k++;
        }
    }
    if(k>0)
        return suma / k;
    return 0;
}

int main() {
    Masina* masini = NULL;
    int nrMasini = 0;

    masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
    afisareVectorMasini(masini,nrMasini);

    float medie = pretMediuDupaNrUsi(masini, nrMasini, 4);
    printf("Media masinilor este: %.2f", medie);
    dezalocareVectorMasini(&masini, &nrMasini);

    return 0;
}