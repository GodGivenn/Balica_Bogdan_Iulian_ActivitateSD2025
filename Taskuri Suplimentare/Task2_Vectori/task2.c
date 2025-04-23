#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Creati in functia main un vector alocat dinamic cu cel putin 5 obiecte de tipul structurii voastre. 
Realizati o functie care va creea un nou vector în care va copia dintr-un vector primit ca parametru 
obiectele care indeplinesc o anumita conditie. Stabiliti voi conditia in functie de un atribut sau 
doua atribute. Realizati o functie care muta intr-un nou vector obiectele care indeplinesc o alta 
conditie fata de cerinta precedenta. Realizati o functie care concateneaza doi vectori.
Realizati o functie care afiseaza un vector cu obiecte. Apelati toate aceste functii in main().
*/

struct StructuraBiblioteca{
    int id;
    char* denumire;
    int nrCarti;
    float* preturiCarti;
};
typedef struct StructuraBiblioteca Biblioteca;//alias

Biblioteca citireBibliotecaDeLaTastatura(){
    Biblioteca b;

    char buffer[100];
    printf("Denumire Biblioteca: ");
    //fgets(buffer, 100, stdin);
    scanf("%s", buffer);
    b.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(b.denumire, buffer);

    printf("id Biblioteca: ");
    scanf("%d", &b.id);

    printf("Numar carti: ");
    scanf("%d", &b.nrCarti);

    b.preturiCarti=(float*)malloc(b.nrCarti * sizeof(float));
    for(int i=0;i<b.nrCarti;i++){
        printf("Pretul cartii %d: ", i+1);
        scanf("%f", &b.preturiCarti[i]);
    }
    printf("\n");
    return b;
}

float calcPretMediu(Biblioteca b){
    float suma=0;
    for (int i = 0; i < b.nrCarti; i++){
        suma += b.preturiCarti[i];
    }

    return b.nrCarti > 0 ? suma/b.nrCarti : 0;
}

void afisareVectorDeBiblioteci(Biblioteca *b, int nrBiblioteci){
    for(int i = 0; i < nrBiblioteci; i++){
        printf("Denumire Biblioteca: %s\n", b[i].denumire);
        printf("Id Carte : %d\n", b[i].id);
        printf("Numar carti: %d\n", b[i].nrCarti);
        for (int i = 0; i < b[i].nrCarti; i++){
            printf("Pretul cartii %d: %.2f lei.\n", i + 1, b[i].preturiCarti[i]);
        }
        printf("Media preturilor este: %f\n", calcPretMediu(b[i]));
        printf("\n");
    }

}

void afisareBiblioteca(Biblioteca b) {
    printf("Denumire Biblioteca: %s\n", b.denumire);
    printf("Id Carte : %d\n", b.id);
    printf("Numar carti: %d\n", b.nrCarti);
    for (int i = 0; i < b.nrCarti; i++){
        printf("Pretul cartii %d: %.2f lei.\n", i + 1, b.preturiCarti[i]);
    }
    printf("Media preturilor este: %f\n", calcPretMediu(b));
    printf("\n");
}

void setDenumire(Biblioteca* b, const char* denNou){
    free(b->denumire);
    b->denumire = (char*)malloc((strlen(denNou) + 1) * sizeof(char));
    strcpy(b->denumire, denNou);
}

void dezaloc(Biblioteca* b){
    free(b->denumire);
    free(b->preturiCarti);
}

//--------------------------------Task2

Biblioteca* creazaVectorCopieNouCuPretPesteMedie(Biblioteca* vectorBiblioteci, int nrBiblioteci, int* nrBiblioteciNou){
    float sumaPreturiMedii = 0;
    for(int i=0;i<nrBiblioteci; i++)
        sumaPreturiMedii += calcPretMediu(vectorBiblioteci[i]);
    float pretMediu = sumaPreturiMedii / nrBiblioteci;

    printf("\nPretul mediu al cartilor este: %f\n", pretMediu);
    *nrBiblioteciNou = 0;

    for(int i=0; i<nrBiblioteci; i++){
        if(calcPretMediu(vectorBiblioteci[i]) > pretMediu){
            (*nrBiblioteciNou)++;
        }
    }

    Biblioteca* vectorNou = (Biblioteca*)malloc((*nrBiblioteciNou) * sizeof(Biblioteca));

    int i_nou = 0;
    for(int i=0;i<nrBiblioteci;i++)
    if(calcPretMediu(vectorBiblioteci[i]) > pretMediu){
        vectorNou[i_nou++] = vectorBiblioteci[i];
    }

    return vectorNou;
}

Biblioteca copieBiblioteca(Biblioteca b) {
    Biblioteca copie;
    copie.id = b.id;

    copie.denumire = (char*)malloc((strlen(b.denumire) + 1) * sizeof(char));
    strcpy(copie.denumire, b.denumire);

    copie.nrCarti = b.nrCarti;
    copie.preturiCarti = (float*)malloc(b.nrCarti * sizeof(float));
    for (int i = 0; i < b.nrCarti; i++) {
        copie.preturiCarti[i] = b.preturiCarti[i];
    }

    return copie;
}

Biblioteca* creazaVectorCopieNouCuAnumitNrCartie(Biblioteca* vectorBiblioteci, int nrBiblioteci, int nrCartiDeCautat,int* nrBiblioteciNou){


    for(int i=0; i<nrBiblioteci; i++){
        if(vectorBiblioteci[i].nrCarti == nrCartiDeCautat){
            (*nrBiblioteciNou)++;
        }
    }

    Biblioteca* vectorNou = (Biblioteca*)malloc((*nrBiblioteciNou) * sizeof(Biblioteca));

    int i_nou = 0;
    for(int i=0;i<nrBiblioteci;i++)
    if(vectorBiblioteci[i].nrCarti == nrCartiDeCautat){
        vectorNou[i_nou++] = copieBiblioteca(vectorBiblioteci[i]);
    }

    return vectorNou;
}


Biblioteca* concateneazaVectori(Biblioteca* biblioteca1, int nrBiblioteci1, Biblioteca* biblioteca2, int nrBiblioteci2, int* dimConcatenare) {
    *dimConcatenare = nrBiblioteci1 + nrBiblioteci2;
    Biblioteca* vectorNou = (Biblioteca*)malloc(*dimConcatenare * sizeof(Biblioteca));

    for (int i = 0; i < nrBiblioteci1; i++) {
        vectorNou[i] = copieBiblioteca(biblioteca1[i]);
    }

    for (int i = 0; i < nrBiblioteci2; i++) {
        vectorNou[nrBiblioteci1 + i] = copieBiblioteca(biblioteca2[i]);
    }
    return vectorNou;
}

void dezalocVectorBiblioteci(Biblioteca* vector, int nrBiblioteci) {
    for (int i = 0; i < nrBiblioteci; i++) {
        dezaloc(&vector[i]);
    }
    free(vector);
}

int main(){
    printf("Cate biblioteci vrei sa introduci?\nNumar Biblioteci: ");
    int nrBiblioteci = 1;
    scanf("%d", &nrBiblioteci);
    Biblioteca* vectorBiblioteci = (Biblioteca*)malloc(nrBiblioteci * sizeof(Biblioteca));

    for(int i = 0; i < nrBiblioteci; i++)
    {
        printf("Citire date pentru biblioteca nr.%d:\n",i+1);
        vectorBiblioteci[i] = citireBibliotecaDeLaTastatura();
    }
    printf("\n------------Cartile:------------\n");

    for(int i = 0; i < nrBiblioteci; i++)
    {
        afisareBiblioteca(vectorBiblioteci[i]);
    }
    int nrNouBibPret=0;
    
    printf("\n------------Peste pretul mediu------------\n");
    
    Biblioteca* bNouPret = creazaVectorCopieNouCuPretPesteMedie(vectorBiblioteci, nrBiblioteci, &nrNouBibPret);
    for(int i = 0; i < nrNouBibPret; i++)
    {
        afisareBiblioteca(bNouPret[i]);
    }
    printf("\n------------Dupa nr de carti------------\n");
    int nrNouBibNrCarti=0;


    Biblioteca* bNouCarti = creazaVectorCopieNouCuAnumitNrCartie(vectorBiblioteci, nrBiblioteci, 2 ,&nrNouBibNrCarti);
    afisareVectorDeBiblioteci(bNouCarti, nrNouBibNrCarti);


    printf("\n------------Concatenare Pret si NrCarti------------\n");
    int nrNouConcat=0;


    Biblioteca* bNouConcat = concateneazaVectori(bNouPret, nrNouBibPret, bNouCarti, nrNouBibNrCarti, &nrNouConcat);
    afisareVectorDeBiblioteci(bNouConcat, nrNouConcat);

    dezalocVectorBiblioteci(vectorBiblioteci, nrBiblioteci);
    dezalocVectorBiblioteci(bNouPret, nrNouBibPret);
    dezalocVectorBiblioteci(bNouCarti, nrNouBibNrCarti);
    dezalocVectorBiblioteci(bNouConcat, nrNouConcat);
}