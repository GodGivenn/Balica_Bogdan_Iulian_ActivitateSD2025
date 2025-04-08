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

    for(int i = 0; i < nrBiblioteci; i++)
    {
        afisareBiblioteca(vectorBiblioteci[i]);
    }
    int nrNouBib=0;
    printf("\n\n\n");
    
    Biblioteca* bNou = creazaVectorCopieNouCuPretPesteMedie(vectorBiblioteci, nrBiblioteci, &nrNouBib);
    for(int i = 0; i < nrNouBib; i++)
    {
        afisareBiblioteca(bNou[i]);
    }

}