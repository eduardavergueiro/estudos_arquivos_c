#include <stdio.h>

typedef struct {
    char cpf[12];
    char nome[80];
    int mes;
    int ano;
    float valor;
} Pagamento;

int main(){

    FILE *bPtr, *nPtr;

    bPtr = fopen("beneficios.dat", "a+"); //acho que deberia ser ab
    nPtr = fopen("novos.dat", "r"); //acho que deveria ser rb

    Pagamento p;
    while(fread(&p, sizeof(Pagamento), 1, nPtr) == 1){
        fwrite(&p, sizeof(Pagamento), 1, bPtr); 
    }

    fclose(bPtr);
    fclose(nPtr);

    return 0;
}