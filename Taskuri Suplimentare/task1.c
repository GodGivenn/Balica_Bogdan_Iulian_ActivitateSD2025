#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Se consideră prima literă din numele vostru, și prima literă
din prenumele vostru.
Sa se construiască un articol care să conțină cele două litere.

Balica Bogdan -> B B
*/

struct StructuraBrutarie{
    char* denumire;
    int cod;
    int nrProduse;
    float* preturi;
}b1;
typedef struct StructuraBrutarie Brutarie;//alias

Brutarie citireBrutarieDeLaTastatura(){
    Brutarie b;

    char buffer[100];
    printf("Denumire brutarie: ");
    //fgets(buffer, 100, stdin);
    scanf("%s", buffer);
    b.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(b.denumire, buffer);

    printf("Cod brutarie: ");
    scanf("%d", &b.cod);

    printf("Numar produse: ");
    scanf("%d", &b.nrProduse);

    b.preturi=(float*)malloc(b.nrProduse * sizeof(float));
    for(int i=0;i<b.nrProduse;i++){
        printf("Pretul produsului %d: ", i+1);
        scanf("%f", &b.preturi[i]);
    }
    printf("\n");
    return b;
}

void afisareBrutarie(Brutarie b) {
    printf("Denumire brutarie: %s\n", b.denumire);
    printf("Cod : %d\n", b.cod);
    printf("Numar produse: %d\n", b.nrProduse);
    for (int i = 0; i < b.nrProduse; i++){
        printf("Pretul produsului %d: %.2f\n", i + 1, b.preturi[i]);
    }
    printf("\n");
}

float calcPretMediu(Brutarie b){
    float suma=0;
    for (int i = 0; i < b.nrProduse; i++){
        suma += b.preturi[i];
    }

    return b.nrProduse > 0 ? suma/b.nrProduse : 0;
}

void setDenumire(Brutarie* b, const char* denNou){
    free(b->denumire);
    b->denumire = (char*)malloc((strlen(denNou) + 1) * sizeof(char));
    strcpy(b->denumire, denNou);
}

void dezaloc(Brutarie* b){
    free(b->denumire);
    free(b->preturi);
}

int main(){
    b1=citireBrutarieDeLaTastatura();
    afisareBrutarie(b1);
    printf("Media produselor este: %f\n", calcPretMediu(b1));
    setDenumire(&b1,"ceva");
    afisareBrutarie(b1);
    dezaloc(&b1);
}