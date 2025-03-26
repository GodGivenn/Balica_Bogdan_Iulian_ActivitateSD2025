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


//creare structura pentru un nod dintr-o lista dublu inlantuita
struct Nod{
    Masina info; //informatia utila
    struct Nod* urmator; //adresa pointerului urm
    struct Nod* precedent; // --//-- precedent
};
typedef struct Nod Nod;

//creare structura pentru Lista Dubla 
struct Lista
{
    Nod* prim;
    Nod* ultim;
};
typedef struct Lista Lista;

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
	// strcpy_s(m1.model, strlen(aux) + 1, aux);
    strcpy(m1.model, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	// strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
    strcpy(m1.numeSofer, aux);

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

void afisareListaMasiniInceput(Lista list) {
	//afiseaza toate elemente de tip masina din lista dublu inlantuita
	//prin apelarea functiei afisareMasina()
    Nod* p = list.prim;
    while(p){
        afisareMasina(p->info);
        p=p->urmator;
    }

}

void afisareListaMasiniSf(Lista list){
    Nod* p = list.ultim;
    while(p){
        afisareMasina(p->info);
        p=p->precedent;
    }
}

    ///la orice adaugare, inserare trebuie sa adaugam un nod
    ///lista nu o modificam, modificam doar elementele din lista deci Lista* list nu e nevoie - 31 40 
void adaugaMasinaInLista(Lista* list, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
    Nod* p=(Nod*)malloc(sizeof(Nod));
    p->info = masinaNoua;
    p->precedent = list->ultim;
    p->urmator = NULL;
    if(list->ultim){
        list->ultim->urmator = p;
    }
    else{
    //cand ultim era null
    //cand e goala lista
        list->prim = p;
    }
    list->ultim = p; //noul nod o sa fie ultimul
}

//acea lista are in interior doua adrese, si daca fac prin valoare... 45 50
void adaugaLaInceputInLista(Lista* list, Masina masinaNoua) {
	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
    Nod* p=(Nod*)malloc(sizeof(Nod));
    p->info = masinaNoua;
    p->urmator = list->prim; // nodul nou -> fostul prim element
    p->precedent = NULL; // fiind primul, nu are precedent


    //daca lista e null nu pot sa fac list.prim.precedent
    if (list->prim) {
        list->prim->precedent = p; // Legatura inversa la fostul prim element
    } else {
        list->ultim = p; // Daca lista era goala, noul nod este si ultimul, primul devine ultimul
    }
    list->prim = p;
}

Lista citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

    FILE* f = fopen(numeFisier,"r");
    Lista list;
    //initalizare lista
    list.prim = NULL;
    list.ultim = NULL;

    while(!feof(f)){
       // adaugaMasinaInLista(&list, citireMasinaDinFisier(f));
        adaugaLaInceputInLista(&list, citireMasinaDinFisier(f));
    }
    fclose(f);
    return list;
}

void dezalocareLDMasini(Lista* lista) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
    Nod* p = lista->prim;
    while (p->urmator != NULL) {
        free(p->info.model);
        free(p->info.numeSofer);
        p = p->urmator;
        free(p->precedent);
    }
    free(p->info.model);
    free(p->info.numeSofer);
    free(p);
    lista->prim = NULL;
    lista->ultim = NULL;
}

float calculeazaPretMediu(Lista list) {
    if (list.prim == NULL) {
        return 0;
    }

    float suma = 0;
    int count = 0;
    Nod* aux = list.prim;

    while (aux) {
        suma += aux->info.pret;
        count++;
        aux = aux->urmator;
    }

    return (count > 0) ? (suma / count) : 0;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {
    Lista lista;
    lista = citireLDMasiniDinFisier("masini.txt");
    // afisareListaMasiniInceput(lista);
    afisareListaMasiniSf(lista);
    float pretMediu = calculeazaPretMediu(lista);
    printf("Pret mediu: %.2f", pretMediu);


    dezalocareLDMasini(&lista);

	return 0;
}