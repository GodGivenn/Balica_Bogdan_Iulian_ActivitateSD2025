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
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
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

//1. 
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara
typedef struct NodListaPrincipala NodListaPrincipala;
typedef struct NodListaSecundara NodListaSecundara;

struct NodListaPrincipala{
    NodListaPrincipala* next;
    NodListaSecundara* vecini;
    Masina info;
};

struct NodListaSecundara{
    NodListaPrincipala* info;
    NodListaSecundara* next;
};

//2.
//functii de inserare in liste
//si in principala si in secundara
NodListaPrincipala* inserareListaPrincipala(NodListaPrincipala* cap, Masina info){
    NodListaPrincipala* nou = (NodListaPrincipala*)malloc(sizeof(NodListaPrincipala));
    //masina de inserat, creem nodul, ne punem in nod, am lista? creez nodul intai
    nou->info = info;
    nou->vecini = NULL;
    nou->next = NULL;

    if(!cap)
        return nou;
    NodListaPrincipala* p = cap;
    while(p->next)
        p = p->next;
    p->next = nou;
    return nou;
}
NodListaSecundara* inserareListaSecundara(NodListaSecundara* cap, NodListaPrincipala* info){
    NodListaSecundara* nou = (NodListaPrincipala*)malloc(sizeof(NodListaSecundara));
    nou->info = info;
    nou->next = NULL;
//inserare la inceput
    nou->next = cap;
    // cap = nou;
    return nou;
}

//3.
//functie de cautarea in lista principala dupa ID
NodListaPrincipala* cautaNodDupaID(NodListaPrincipala* listaPrincipala, int id) {
    while(listaPrincipala && listaPrincipala->info.id != id)//exista lista si nu e id ul bun
    {
        listaPrincipala = listaPrincipala->next;
    }
    return listaPrincipala;
}

//4.
//inserare muchie
void inserareMuchie(NodListaPrincipala* listaPrincipala, int idStart, int idStop) {
    NodListaPrincipala* nodStart = cautaNodDupaID(listaPrincipala, idStart);
    NodListaPrincipala* nodStop = cautaNodDupaID(listaPrincipala, idStop);

    //verif daca exista si in vecini punem nod stop

    if(nodStart && nodStop){
        nodStart->vecini = inserareListaSecundara(&nodStart->vecini, nodStop);
        nodStart->vecini = inserareListaSecundara(&nodStop->vecini, nodStart);
    }
}


void* citireNoduriMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
    NodListaPrincipala* listaPrincipala = NULL;
    FILE* f = fopen(numeFisier,"r");
    while(!feof(f)){
        inserareListaPrincipala(listaPrincipala, citireMasinaDinFisier(f));
    }
    fclose(f);
    return listaPrincipala;
}

void citireMuchiiDinFisier(NodListaPrincipala* listaPrincipala, char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste 
	//toate id-urile de start si stop pentru fiecare muchie
	//ATENTIE - la final inchidem fisierul/stream-ul
    FILE* f = fopen(numeFisier, "r");
    while(!feof(f)){
        int idStart;
        int idStop;
        fscanf(f, "%d %d", &idStart, &idStart);
        inserareMuchie(listaPrincipala, idStart, idStart);
    }
    fclose(f);
}

void stergereListaSecundara(NodListaSecundara** cap){
    NodListaSecundara* aux = (*cap)->next;
    while((*cap)){
        aux = (*cap)->next;
        free((*cap));
        (*cap) = aux;
    }
}

void dezalocareNoduriGraf(NodListaPrincipala** listaPrincipala) {
	//sunt dezalocate toate masinile din graf
	//si toate nodurile celor doua liste
    NodListaPrincipala* aux;
    while((*listaPrincipala)){
        aux = (*listaPrincipala)->next;
        stergereListaSecundara((*listaPrincipala)->vecini);
        if((*listaPrincipala)->info.numeSofer){
            free((*listaPrincipala)->info.model);
        }
        if((*listaPrincipala)->info.model){
            free((*listaPrincipala)->info.model);
        }
        free(*listaPrincipala);
        (*listaPrincipala) = aux;
    }
}

//Parcurgere in adancime

//crere structura Stiva
//push si pop pentru stiva
int calculeazaNrNoduriGraf(void* listaPrincipala) {

}

void afisareGrafInAdancime(void* listaPrincipala, int idPlecare) {
	/*
	1. Este luata o STIVA si un vector de vizitate
	2. Marcam nodul de plecare ca fiind vizitat si il adaugam in STIVA noastra
	3. Pornim parcurgerea care va rula cat timp avem noduri in STIVA
	4.1 Extragem un nod din STIVA
	4.2 Procesam nodul extras din STIVA - il afisam
	4.3. identificam toti vecinii nodului extras care nu sunt vizitati si ii marcam ca vizitati, adugandu-i in STIVA
	4.4 reluam procesul
	*/
}


//Parcurgere in [adancime]latime

//crere structura coada
//enqueue si dequeue pentru coada

void afisareGrafInLatime(void* listaPrincipala, int idPlecare) {
	/*
	1. Este luata o COADA si un vector de vizitate
	2. Marcam nodul de plecare ca fiind vizitat si il adaugam in COADA noastra
	3. Pornim parcurgerea care va rula cat timp avem noduri in COADA
	4.1 Extragem un nod din stiva
	4.2 Procesam nodul extras din COADA - il afisam
	4.3. identificam toti vecinii nodului extras care nu sunt vizitati si ii marcam ca vizitati, adugandu-i in COADA
	4.4 reluam procesul
	*/
}


int main() {
    NodListaPrincipala* graf = citireNoduriMasiniDinFisier("masini.txt");
    citireMuchiiDinFisier(graf,"muchii.txt");
    dezalocareNoduriGraf(&graf);

	return 0;
}