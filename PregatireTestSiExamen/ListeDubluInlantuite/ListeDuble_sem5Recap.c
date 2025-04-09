#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// struct StructuraMasina {
// 	int id;
// 	int nrUsi;
// 	float pret;
// 	char* model;
// 	char* numeSofer;
// 	unsigned char serie;
// };
// typedef struct StructuraMasina Masina;

// struct Nod{
//     Masina info;
//     Nod* urmator;
//     Nod* precedent;
// };

// typedef struct Nod Nod;

// struct Lista{
//     Nod* prim;
//     Nod* ultim;
// };
// typedef struct Lista Lista;

// void adaugareLaInceputInLista(Lista* list, Masina masinaNoua){
//     Nod* p=(Nod*)malloc(sizeof(Nod));
//     p->info=masinaNoua;
//     p->urmator = list->prim;
//     p->precedent = NULL;

//     if(list->prim){
//         list->prim->precedent = p;
//     }
// }

// Lista citireListaMasiniFisier(const char* numeFisier){
//     FILE* file = fopen(numeFisier,"r");
//     Lista list;
//     list.prim = NULL;
//     list.ultim = NULL;

//     while(!feof(file)){

//     }
//     fclose(file);
//     return list;
// }

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
    struct Nod* urmator;
    struct Nod* precedent;
};

typedef struct Nod Nod;

struct Lista{
    Nod* prim;
    Nod* ultim;
};
typedef struct Lista Lista;

Masina citireMasinaDinFisier(FILE* file){
    char buffer[100];
//1,3,5000,Astra,Ionescu,A
    char sep[3]=",\n";
    fgets(buffer,100,file);//!!!!
    char* aux;
    Masina m1;
    aux = strtok(buffer,sep);
    m1.id = atoi(aux);
    m1.nrUsi = atoi(strtok(NULL,sep));
    m1.pret = atof(strtok(NULL,sep));
    
    aux = strtok(NULL,sep);
    m1.model = malloc(strlen(aux)+1);
    strcpy(m1.model, aux);

    aux = strtok(NULL,sep);
    m1.numeSofer = malloc(strlen(aux)+1);
    strcpy(m1.numeSofer, aux);

    m1.serie = *strtok(NULL,sep);

    return m1;
}

void afisareMasina(Masina masina){
    printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void adaugaLaInceputInLista(Lista* list, Masina masinaNoua){
    Nod* nodNou = (Nod*)malloc(sizeof(Nod));
    nodNou->info = masinaNoua;
    nodNou->urmator=list->prim;
    nodNou->precedent = NULL;

    if(list->prim){
        list->prim->precedent = nodNou;
    }
    else{
        list->ultim = nodNou;
    }
    list->prim = nodNou;
}


Lista citireListaMasiniDinFisier(const char* numeFisier){
    FILE* file = fopen(numeFisier, "r");
    Lista list;
    list.prim = NULL;
    list.ultim = NULL;

    while(!feof(file)){
        adaugaLaInceputInLista(&list,citireMasinaDinFisier(file));
    }
    fclose(file);
    return list;
}

void afisareListaMasini(Lista list){
    Nod* nod = list.ultim;
    while(nod){
        afisareMasina(nod->info);
        nod = nod->precedent;
    }
}

int main(){
    Lista list = citireListaMasiniDinFisier("masini.txt");
    afisareListaMasini(list);
}